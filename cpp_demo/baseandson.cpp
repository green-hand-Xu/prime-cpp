/**
 * @file baseandson.cpp
 * @author xyb
 * @brief 父类构造函数的显式调用 （当父类无默认构造函数时，实例化子类时，必须显式调用父类构造函数）
 *              顺便探究 命名空间（或者理解为在不同文件中），显式调用父类构造函数时，是不是要加上作用域
 *              省事的方法是 把public 后的父类 整个名字 作为子类构造的 初始化列表里使用的构造对象名
 * @version 0.1
 * @date 2022-12-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

namespace Persons{
class Person
{
public:
	Person(string newID,string newname,string newsex,string newbirthday)
	{
		ID=newID;
		name=newname;
		sex=newsex;
		birthday=newbirthday;
	}
	void getID()
	{
	 cout<<ID<<endl;	
	}
	void getName()
	{
	 cout<<name<<endl;
	}
	void getSex()
	{
	 cout<<sex<<endl;	
	}
	void getBirthday()	
	{
	 cout<<birthday<<endl;	
	}
private:
	string ID;
	string name;
	string sex;
	string birthday;
};
}

class Student:public Persons::Person
{
public:
	Student(string newID,string newname,string newsex,string newbirthday,string newclass,float newscore): Persons::Person(newID,newname,newsex,newbirthday) 
	{  
		Class=newclass;
		score=newscore;
	}
	void getClass()
	{
		cout<<Class<<endl;
	}
	void getScore()
	{
		cout<<score<<endl;
	}
private:
	string Class;
	float score;
};

 int main()
 {
 	Student *stu=new Student("5226","李虎","Man","2005-12-25","a班",96.63);
 	stu->getID();
 	stu->getName();
 	stu->getSex();
 	stu->getBirthday();
 	stu->getClass();
 	stu->getScore();
 	delete stu;
 	return 0;
 }
 