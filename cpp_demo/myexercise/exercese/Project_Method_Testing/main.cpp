#include <iostream>




int main(){
    uint8_t bkglmpLight = 5;
    auto lightpercentage = bkglmpLight-10;
    uint16_t setvalue = (256 *(lightpercentage/100.0))+0.5;
    std::cout<<(unsigned int)lightpercentage<<std::endl;

    return 0;
}