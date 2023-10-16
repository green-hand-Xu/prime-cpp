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
class Base
{

	public:
		Base();

		void setBase(string a);
		string Bases = "Base";

	 	void operator=(const Base &base){
			cout<<"父类复制构造函数"<<endl;
		}
};

Base::Base(){
	cout<<"Base constructed"<<endl;
}

void Base::setBase(string a){
	this->Bases = a;
}


class inherit:public Base
{
	public:
		inherit(string str){
			this->inherits = str;
		}

		// inherit operator =(const inherit &inher) = delete;

	public:
		string inherits = "inherit";
};


 int main()
 {
	inherit obja{"obja"};
	inherit objb{"objb"};
	
	obja = objb;
	cout<<obja.inherits<<endl;

 	return 0;
 }