/**
 * @file StringIO.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

struct PersonInfo
{
    std::string name;
    std::vector<std::string> phones;

    void printinfo(){
        std::cout<<"name : "<<name<<" phone : ";
        for (auto phone:phones)
        {
            std::cout<<phone<<" ";
        }
        std::cout<<std::endl;
    }
};

/**
 * @brief 使用 istringstream 输入数据
 * 
 */
void readData(){
    std::ifstream fread("../Files/Person.txt");

    std::string line,word;
    std::vector<PersonInfo> people;
    while (getline(fread,line))
    {
        PersonInfo info;
        std::istringstream record(line);
        record >> info.name;
        while (record >> word)
        {
            info.phones.push_back(word);
        }
        info.printinfo();
        people.push_back(info);
        record.clear();
    }
    fread.close();
}

std::istream &iofunction(std::istream &is)
{
	std::string s;
	while(is >> s)
		std::cout << s << std::endl; 
    //输出完毕后 重置流标志位
	is.clear();
	return is;
}

void test(){
    std::istringstream istrs("aa\nbb\ncc dd");
	iofunction(istrs);
}

using namespace std;
/**
 * @brief 校验字符是否为数字
 * 
 * @param s 
 * @return true 都是数字
 * @return false 有字符不是数字
 */
bool valid(const string &s)
{
	for(const auto c : s)
		if(!isdigit(c)) return false;
	return true;
}

/**
 * @brief 格式化输入
 * 
 * @param s 
 * @return string 
 */
string format(const string &s)
{
	return s;
}
/**
 * @brief ostringstream 输出流的使用
 * 
 */
void ostringstream_Test(){
	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifs("../Files/Person.txt");
	ofstream ofs("../Files/Personout.txt");

	while(getline(ifs, line))
	{
		record.str(line);
		PersonInfo info;
		record >> info.name;
		while(record >> word)
			info.phones.push_back(word);
		record.clear();
		people.push_back(info);
	}
	ostringstream formatted, badNums;
	for(const auto &person : people)
	{
		for(const auto &ph : person.phones)
		{
			if(!valid(ph))
			{
				badNums << " " << ph;
			}else{
				formatted << " " << format(ph);
			}
		}
		if(badNums.str().empty()){
			ofs << person.name << " " << formatted.str() << endl;
		}
		else{
			cerr << " input error: " << person.name << " invalid number(s)" << badNums.str() << endl;
		}

	}
	cout<<formatted.str()<<endl;
}

/**
 * @brief 将int 等类型数据转换为string输出
 * 
 */
void Int2String(int a,int b){
    std::stringstream str{" "};
    str << " input range error . input value = " << (int)a << " but date range is [" << (int)b << "," << (int)b << "]";  
    std::string retS;
    retS = str.str();
	cout<<retS<<endl;
}

enum class AAA {
	OK = 1,
	NOK = 2,
	ERROR = 3
};


namespace CCC{
	namespace FFF{
		enum class BBBB {
			OK = 1,
			NOK = 2,
			ERROR = 3
		};
	}

}

using DDD = CCC::FFF::BBBB;
/**
 * @brief 范围值校验 并输出日志
 * 可以将 T 的名字自动输出
 * @tparam T 输入参数类型
 * @param a 
 * @param b 
 */
template<typename T>
void TInt2String(T value,T min,T max){
    std::string FunctionType = __PRETTY_FUNCTION__;
	cout<<FunctionType<<endl;
    auto begin = FunctionType.find("T = ") + 4;
	begin = FunctionType.find_last_of('::');
	begin = FunctionType.find_last_of('::',begin-2)+1;
    auto end = FunctionType.find_last_of(']');

	auto type = FunctionType.substr(begin,end-begin);
    std::stringstream str;
	str.str(" ");
    str << type << " input range error . input value = " << (int)value << " but date range is [" << (int)min << "," << (int)max << "] \n";  
	cout<<str.str();
}

int main(){
	// AAA aaa{44};
    // TInt2String(aaa,AAA::OK,AAA::ERROR);
	DDD bbbb{44};
	TInt2String(bbbb,DDD::OK,DDD::ERROR);
    return 0;
}