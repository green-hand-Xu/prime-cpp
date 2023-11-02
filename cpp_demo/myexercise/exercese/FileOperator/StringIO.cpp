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
	is.clear();
	return is;
}

void test(){
    std::istringstream istrs("aa\nbb\ncc dd");
	iofunction(istrs);
}


int main(){
    test();
    return 0;
}