#include <iostream>

using namespace std;

long Fun(int N){
    if (N==0)
    {
        return 0;
    }
    if (N==1)
    {
        return 1;
    }
    return Fun(N-1)+Fun(N-2);
}

void Test(){
    for (int i = 0; i <= 100; i++)
    {
        cout<<"Fun "<<i<<" = "<<Fun(i)<<endl;
    }
    
}

int main(){

    Test();
    return 0;
}