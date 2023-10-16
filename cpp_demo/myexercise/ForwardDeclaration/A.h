#ifndef A
#define A
/**
 * @file A.h
 * @author your name (you@domain.com)
 * @brief 前向声明。
 *         在A中引B头文件，B中又引用的有A头文件 同时声明了类A对象的内容，因为先进行头文件展开，所以B中先出现了A类的定义，此时A类还没声明出来。
 *         可以在B中 使用 class A;的方式提前声明出A类。这样就可以解决 两个类相互循环调用的情况。
 * @version 0.1
 * @date 2023-03-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

	class BBB;
	class AAA {
    public:
        BBB* b;
        // void print(){
        //     b->foo();//error：无法使用不完全类型B的函数
        // }
        
    };


#endif