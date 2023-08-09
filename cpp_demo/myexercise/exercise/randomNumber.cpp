#include <iostream>
#include<ctype.h>
#include<vector>
#include <cstdlib> // Header file needed to use srand and rand
#include <ctime> // Header file needed to use time
using namespace std;

int range35(){
    return rand()%35+1;
}

int range12(){
    return rand()%12+1;
}

int main()
{
    unsigned seed;  // Random generator seed
    // Use the time function to get a "seed” value for srand
    seed = time(0);
    srand(seed);

    vector<int> vec;
    for (int i = 0; i <5 ; i++)
    {
        int j = 0;
        j = range35();
        vec.push_back(j);
    }

    for (int i = 0; i < 2; i++)
    {
        int j = 0;
        j = range12();
        vec.push_back(j);
    }
    
    for (auto i = vec.begin(); i < vec.end(); i++)
    {
        cout<<*i<<" ";
    }
    cout<<endl;


}

