/**
 * @file exception.cpp
 * @author your name (you@domain.com)
 * @brief 异常练习  throw 抛出异常  try catch捕获异常
 *         异常种类 参考 primer c++ 第五版 5.6.3节
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;

int sum(int a,int b){

    throw runtime_error("error");

}

int main(){
    int a,b;
    while(true){
        try{
            cin >> a >> b;
            sum(a,b);
        }catch(exception err){
            cout<<err.what()<<endl;
            cout<<"try again? enter y or n"<<endl;
            char c;
            cin>>c;
            if(!cin || c == 'n'){
                break;
            }
        }
    }

    return 0;
}