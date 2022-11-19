// #include <stdio.h>
// #include <string.h>

// #pragma pack(push,1)
// struct a {
//     float b;
//     int   d;
//     char  c;
// };
// #pragma pack(pop)

// struct a temp,test;
// unsigned char buf[sizeof(struct a)];
// int main() {
//     temp.b=0.1f;
//     temp.d=23;
//     temp.c='4';

//     auto lenb = sizeof(temp.b);
//     auto len = sizeof(temp);


//     memcpy((void *)buf,(void *)&temp, len);

//     auto temp2 = (a*)buf;
//     auto b2 = temp2->b;

//     memcpy((void *)&test,(void *)buf,sizeof(struct a));

//     printf("%3.1f %d %c\n",test.b,test.d,test.c);
//     return 0;
// }

#include <iostream>
#include <string>
#include "cstring"
using namespace std;

struct person {
	std::string name;
	int age;
};

int main() {

	person one{"abc", 40};

	string str{""};

    memcpy(&str,&one,sizeof(struct person));

	cout << "字符串:"  << str << endl;

	person three{};

	memcpy(&three,&str, sizeof(struct person));

	cout << three.name << "   " << three.age << endl;

	return 0;
}