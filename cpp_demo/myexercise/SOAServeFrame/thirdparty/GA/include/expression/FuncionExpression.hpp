#ifndef __GALogicExpress_HPP__
#define __GALogicExpress_HPP__

#include <functional>

using ExpressionItem = std::function<bool()>;

enum LogicOperator{
    And,
    Or
};

/**
 * @brief Expression to link functions.
 */
class FuncionExpression { 
public:
    FuncionExpression():
        FuncionExpression(nullptr, LogicOperator::Or, nullptr){
    }

    FuncionExpression(ExpressionItem expr)
        : FuncionExpression(expr, LogicOperator::Or, nullptr){
    }

    FuncionExpression(ExpressionItem left, LogicOperator opr, ExpressionItem right)
        : _left(left), _operator(opr), _right(right) {
    }

    operator bool() const{
        return result();
    }

    FuncionExpression operator&&(FuncionExpression expr) {
        FuncionExpression me(*this);

        return FuncionExpression([me]()->bool{ auto e = std::move(me); return e.result(); },
                              LogicOperator::And,
                              [expr]()->bool{ auto e = std::move(expr); return e.result(); });
    }

    FuncionExpression operator&&(ExpressionItem ev){
        FuncionExpression me(*this);
        if (me._right) {
            return FuncionExpression([me]()->bool { return me.result(); }, LogicOperator::And, ev);
        } else {
            me._right = ev;
            me._operator = LogicOperator::And;
            return me;
        }
    }

    bool operator && (bool v){
        return v ? result() : false;
    }

    FuncionExpression operator||(FuncionExpression expr) {
        FuncionExpression me(*this);

        return FuncionExpression([me]()->bool{ auto e = std::move(me); return e.result(); },
                              LogicOperator::Or,
                              [expr]()->bool{ auto e = std::move(expr); return e.result(); });
    }

    FuncionExpression operator||(ExpressionItem ev) {
        FuncionExpression me(*this);
        if (me._right) {
            return FuncionExpression([me]()->bool{ return me.result(); }, LogicOperator::Or, ev);
        } else {
            me._right = ev;
            me._operator = LogicOperator::Or;
            return me;
        }
    }

    bool operator || (bool v){
        return v ? true : result();
    }

    //Result should be true, return true when result is true.
    inline bool result() const{
        switch (_operator) {
            case LogicOperator::And:
                return (_left != nullptr && _left()) && (_right != nullptr && _right());

            case LogicOperator::Or:
                return (_left != nullptr && _left()) || (_right != nullptr && _right());

            default:
                return false;
        }
    }

protected:
    ExpressionItem _left;
    ExpressionItem _right;
    LogicOperator _operator;
};

#endif