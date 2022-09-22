#include <iostream>
#include <string>

int main(){

    std::string word("some string");
    // while (std::cin>>word)
    // {
    //     std::cout<<word<<std::endl;
    // }
    
    for(auto c:word){
        std::cout<<c<<std::endl;
    }

    /*
        ispunct(c) 判断字符是不是标点符号    
    */

    return 0;
}