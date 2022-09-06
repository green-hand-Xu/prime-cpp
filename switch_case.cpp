#include <iostream>

using namespace std;

int main(){
    uint32_t option;
    while (true){

        
        cout<<"请选择模式  1 or 2"<<endl;
        cin>>option;
        switch (option)
        {   
        case 1:
            cout<<"case 1"<<endl;
            break;

        case 2:
            cout<<"case 2"<<endl;
            break;

        default:
            cout<<"default"<<endl;
            break;
        }    
    }

    return 0;
}