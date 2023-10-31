/**
 * @file FileIO.cpp
 * @author XuYingBo (you@domain.com)
 * @brief 文件读写练习
 * @version 0.1
 * @date 2023-10-30
 * a
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>
#include <strstream>

/**
 * @brief 参数和返回类型 是一个输入流的引用
 * 
 * @param is 
 * @return std::istream& 
 */
std::istream& input(std::istream& is){
    int a;
    while (is>>a)
    {
        std::cout<<a<<std::endl;
        if (a == 0)
        {
            is.setstate(std::cin.eofbit);
        }
    }
    
    is.clear();//重置流标志位
    return is;
}

void input_Test(){
    auto& in = input(std::cin);

	std::string s1;
	while(in >> s1)
		std::cout << s1 << std::endl;
}
/**
 * @brief 流的绑定与解绑
 * 
 */
void exchangestream(){
    //查看 cin 绑定的输出流
    std::cout<<std::cin.tie()<<std::endl;
    //解绑 cin 绑定的输出流
    std::cin.tie(nullptr);
    //查看 cin 绑定的输出流
    std::cout<<std::cin.tie()<<std::endl;
    //重新绑定
    std::cin.tie(&std::cout);
}

/**
 * @brief 文件输入输出流
 * 
 */
class Sales_data
{
public:
    int bookNo;
    double units_sold;
    double revenue;
public:
    Sales_data(){

    }

    ~Sales_data(){

    }

    std::istream &read(std::istream &is , Sales_data &item){
        double price = 0;
        is >> item.bookNo >> item.units_sold >> price;
        item.revenue = price * item.units_sold;
        return is;
    }

    std::ostream &print(std::ostream &os , const Sales_data &item){
        os << item.units_sold << " " << item.revenue << " " <<item.bookNo;
        return os;
    }


    void TestOne(char* argv[]){
        std::ifstream input (argv[1]);
        std::ofstream output (argv[2]);
        Sales_data total;
        if (read(input,total))
        {
            
        }
        
    }
};



int main(){
    exchangestream();
    return 0;
}