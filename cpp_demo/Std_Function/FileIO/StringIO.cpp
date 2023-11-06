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

int main(){
    ostringstream_Test();
    return 0;
}