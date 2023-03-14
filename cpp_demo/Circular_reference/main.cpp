#include "manager.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(){

    manager::getInstacne().start();

    while (true)
    {
        sleep(1);
    }
    
    return 0;
}