#ifndef __CommandPriority_HPP__
#define __CommandPriority_HPP__

#include <unordered_map>
#include <atomic>

using CommandTokenValueType = u_int64_t;
constexpr CommandTokenValueType CommandTokenInvalid = 0;

using PriorityLevels = std::unordered_map<int, int>;
constexpr int PrivilegeLevelUnknown = -1;

constexpr int CommandNoAction = 0;

struct CommandData{
  CommandTokenValueType Token{CommandTokenInvalid};
  /**
   * @brief 使用int类型作为数据类型非常重要，因为这样我们可以使用-1来做无效值，而不是最高级的0。
   * 在一些设定中0是最高优先级，这和初始值、无效值无法明显区分。
   * 
   */
  int Priority{PrivilegeLevelUnknown};
  int Command{CommandNoAction};
};

class CommandPriority {
 public:
  /**
   * @brief 可自行指定优先级数字对应的优先级等级，等级越低的话，优先级越高。
   * 优先级从0开始，小于0认为是无效，所有小于0的优先级都直接返回优先级过低。
   * 
   * @note 仅对指定的转换关系进行转换，未指定的其他值，则保持优先级原值。
   * 
   * @param levels 
   */
  inline void customizePriority(PriorityLevels& levels){
      _levels.swap(levels);
  }

  /**
   * @brief 如果当前有正在指令排队，则返回true，代表目前优先级锁正在锁闭等待；
   * 如果没有任何指令排队，则目返回false，代表当前没有指令排队，也代表目前优先级锁闭处于空状态。
   */
  inline bool isBusy(){
      return _isCommandValid;
  }

  inline CommandTokenValueType currentToken(){
      return _command.Token;
  }

  /**
   * @brief 尝试进行优先级判断，但不等待，用于尝试性检测及试探性判断而不想实际阻塞等待的场景。
   * 在异步情况下，该判断只保证调用时准确性，而不保证任意时刻的准确性。
   *
   * @param priority 优先级从0开始，小于0认为是无效，所有小于0的优先级都直接返回优先级过低。
   */
  inline bool tryAccess(int priority, int command){
      return this->isPriorityHigher(priority, command);
  }

  /**
   * @brief 进行指令可执行判断，阻塞直到判断时间周期结束。在判断周期结束后，选出优先级最高的指令。
   * 该函数无执行状态占用。
   * @param priority 优先级从0开始，小于0认为是无效，所有小于0的优先级都直接返回优先级过低。
   * @param command
   * @param token 如果成功，则返回当前执行者的token。
   *
   * @return true代表当前指令是最高优先级，可执行；
   * false代表当前指令被其他高优先级指令占位，不可继续执行。
   */
  inline bool access(int priority, int command, CommandTokenValueType& token){
      return doAccess(priority, command, false, token);
  }

  /**
   * @brief 进行指令可执行判断，阻塞直到判断时间周期结束。在判断周期结束后，选出优先级最高的指令。
   * 该函数进行执行状态占用，直到leave被调用。
   * 执行状态占用期间，低优先级命令调用access/accessAndOccupy将返回false。
   *
   * @param priority 优先级从0开始，小于0认为是无效，所有小于0的优先级都直接返回优先级过低。
   *
   * @return 返回true代表当前指令是最高优先级，可执行；
   * 返回false代表当前指令被其他高优先级指令占位，不可继续执行。
   */
  inline bool accessAndOccupy(int priority, int command, CommandTokenValueType& token){
      return doAccess(priority, command, true, token);
  }

  /*
   * @brief 释放指定命令的执行状态占用。
   * 如果指定token不是当前命令执行的token，则不会产生任何效果。
   * 
   * @param token 期待释放执行状态的token。
   */
  bool leave(CommandTokenValueType token) {
      if(!_isCommandValid) {
          return true;
      }

      if(token == CommandTokenInvalid || _command.Token != token) {
          return false;
      }

      this->_isCommandValid = false;
      return true;
  }

  /**
   * @brief 取消整个控制的状态占用，重新恢复优先级判断。
   */
  inline bool leave(){
      this->_isCommandValid = false;
      return true;
  }

private:
  bool doAccess(int priority, int command, bool isOccupy, CommandTokenValueType& token) {
    token = CommandTokenInvalid;
      if(!this->isPriorityHigher(priority, command)) {
          return false;
      }

      CommandTokenValueType t;
      if(!this->updateCommand(priority, command, t)) {
          return false;
      }

      // not me
      if(t != this->_command.Token) {
          return false;
      }

      // I am who can do it
      this->_isCommandValid = isOccupy;
      token = t;
      return true;
  }

  inline bool isPriorityHigher(int priority, int command) {
    auto token = _tokenLock.load();

    if(!this->_isCommandValid) {
      return true;
    }
    if(priority <= PrivilegeLevelUnknown) {
      return false;
    }

    auto p = priorityTransform(priority);
    if(p <= PrivilegeLevelUnknown) {
      return false;
    }

    return p < this->_command.Priority 
        || (p == this->_command.Priority && command != this->_command.Command);
  }

  /**
   * @brief 为优先级进行转换，如果存在转换映射则按照映射进行转换，
   * 否则返回原始的优先级数值。
   * 
   * @note 在有转换关系但未提供转换映射的时候，仍然会返回原值。
   * 
   * @param priority 
   * @return int 
   */
  inline int priorityTransform(int priority) {
    auto p = PrivilegeLevelUnknown;

    if(_levels.empty()){
      p = priority;
    }else{
      auto i = _levels.find(priority);
      p = i == _levels.cend() ? priority : i->second;
    }

    if(p < PrivilegeLevelUnknown){
      p = PrivilegeLevelUnknown;
    }

    return p;
  }

  /**
   * @brief 为每一个指令执行创建一个唯一的号牌，只有最后拿到执行号牌的人才准予执行，号牌也是区分不同请求的唯一标识。
   */
  inline CommandTokenValueType createToken() {
    ++_tokenLock;
    auto t = _tokenLock.load();
    auto retryCount = 0;
    while (t <= CommandTokenInvalid && retryCount < 5)
    {
      t = CommandTokenInvalid;
      ++t;
       _tokenLock.store(t);
       t = _tokenLock.load();
       ++retryCount;
    }

    if(t < CommandTokenInvalid){
      t = CommandTokenInvalid;
    }

    return t;
  }

  /**
   * @brief 更新当前指令为最高优先级指令，高优先级仅限于当前类实体对象。
   */
  bool updateCommand(int priority, int command, CommandTokenValueType& token){
      token = this->createToken();
      this->_command.Token = token;

      this->_command.Priority = priority;
      this->_command.Command = command;

      this->_isCommandValid = true;

      return true;
  }

 private:
  /**
  * @brief 命令正在执行的标志，true代表command正在执行中，
  * false则代表当前command是一个无效或者已经执行完毕的command。
  */
  bool _isCommandValid{false};
  CommandData _command{CommandTokenInvalid, PrivilegeLevelUnknown, CommandNoAction};
  
  /**
   * @brief Priority level internal mapping.
   * 
   */
  PriorityLevels _levels;

  /**
   * @brief Lock read/write action for current command。
   * 
   */
  std::atomic<CommandTokenValueType> _tokenLock{0};  
};

#endif
