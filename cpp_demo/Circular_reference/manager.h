#ifndef MANAGERB
#define MANAGERB
#include "A.h"
#include "B.h"
#include <iostream>
#include <memory>

class manager
{
private:
    manager();
    ~manager();    

    std::shared_ptr<A> obja;
    std::shared_ptr<B> objb;

public:
    static manager& getInstacne(){
        static manager instance;
        return instance;
    }

    void start();

};


#endif