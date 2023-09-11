#include <iostream>

#ifdef Macro1
void Mac1(){
    std::cout<<"启用 宏 Macro1"<<std::endl;
}
#endif

int main(){
#ifdef Macro1
    Mac1();
#endif
    return 0;
}