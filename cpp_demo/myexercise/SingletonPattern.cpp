/**
 * @file SingletonPattern.cpp
 * @author your name (you@domain.com)
 * @brief  单例类的使用
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
//----------------------------单例类声明-----------------------
using namespace std;
class SingletonPattern
{
private:
	SingletonPattern();
public:
	~SingletonPattern();

private:
	static SingletonPattern* m_Instance;

public:
	static SingletonPattern* GetInstance();

	void display();
};

//-------------------------单例类实现------------------------------
SingletonPattern* SingletonPattern:: m_Instance = nullptr;
SingletonPattern::SingletonPattern()
{
	cout << "创建单例模式对象！" << endl;
}

SingletonPattern::~SingletonPattern()
{
	if (m_Instance != nullptr) {
		delete m_Instance;
		m_Instance = nullptr;
	}
	cout << "销毁单例模式对象！" << endl;
}

SingletonPattern *SingletonPattern::GetInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new SingletonPattern();
	}

	cout << "返回单例模式句柄！" << endl;
	return m_Instance;
}

void SingletonPattern::display()
{
	cout << "使用单例模式！" << endl;
}



int main() {
	// SingletonPattern* m_Test = SingletonPattern::GetInstance();
	// m_Test->display();
    // delete m_Test;
	// cin.ignore();
    int* a;
    cout<<a<<endl;

	return 0;
}