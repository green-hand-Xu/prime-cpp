#include <iostream>
using namespace std;



int main() {
    int n, k;
    char words[] = {'y','o','u'};
    string str;

    while (cin >> n >> k) { // 注意 while 处理多个 case
        int tailNo = n-(3*k);
        if(tailNo < 0){
            cout<<(-1)<<endl;
            continue;
        }
        if(k>0){
            for(int i = 0; i < k ; ++i){
                str  = str+'y'+'o'+'u';
            }
        }
        for(int l = n-tailNo ; l<n ; ++l){
            str = str + words[0];
        }
        cout<<str<<endl;
        str = "";
    }
}