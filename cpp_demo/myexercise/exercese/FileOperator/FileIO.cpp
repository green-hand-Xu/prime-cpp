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

    Sales_data(int No,double sold,double re){
        bookNo = No;
        units_sold = sold;
        revenue = re;
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
        os << item.bookNo << " " << item.units_sold << " " <<item.revenue <<" ";
        return os;
    }

    //向文件中写数据
    void WriteData(){
        std::ofstream output;
        output.open("../Files/text.txt");
        Sales_data totalone(1,2,3);
        Sales_data totaltwo(4,5,6);
        print(output,totalone);
        print(output,totaltwo);
        output.close();
    }
    //从文件中读数据并保存到对象中
    void ReadData(){
        std::ifstream input;
        input.open("../Files/text.txt");
        Sales_data totalone;
        Sales_data totaltwo;
        read(input,totalone);
        read(input,totaltwo);
        input.close();
        std::cout<<totalone.bookNo<<" "<<totalone.units_sold<<" "<<totalone.revenue<<"\n";
        std::cout<<totaltwo.bookNo<<" "<<totaltwo.units_sold<<" "<<totaltwo.revenue<<"\n";
    }
}Sales_data;

/**
 * @brief 忽略输入流中的非数字类型
 * 
 */
void ignore_non_numeric_input(){
    // 保存 整形类型的最大数
    auto max_size = std::numeric_limits<std::streamsize>::max();

    std::istringstream input{"1asd2asd3"};

    for(;;){
        int n;
        if(input >> n){
            std::cout<<n<<'\n';
        }else if(input.bad()||input.eof()){
            break;
        }else if(input.fail()){
            input.clear();
            input.ignore();//使用默认参数
        }
    }
}


int main(){
    Sales_data.WriteData();
    Sales_data.ReadData();
    return 0;
}