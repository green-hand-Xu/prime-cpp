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

// #include <iostream>
// #include <string>
// #include "cstring"
// #include <map>
// using namespace std;

// struct person {
// 	std::string name;
// 	int age;
// 	std::map<char,int> src;
// };

// int main() {

// 	person one{"abc", 40};
// 	one.src['a'] = 20;
// 	string str{""};

//     memcpy(&str,&one,sizeof(one));

// 	cout << "字符串:"  << str << endl;

// 	person three{};

// 	memcpy(&three,&str, sizeof(one));

// 	cout << three.name << "   " << three.age << endl;

// 	return 0;
// }

#include <iostream>
#include <string>
#include <map>
#include <cstring>
using namespace std;

#pragma pack(push,1)
struct str{
	map<char, int> mp;
};
#pragma pack(pop)

int main() {
	str str1;
	str1.mp['a'] = 222;
	str1.mp['b'] = 333;
	str1.mp['c'] = 444;
	str1.mp['d'] = 555;
	str1.mp['e'] = 666;
	str1.mp['f'] = 777;
	// for (map<char, int>::iterator it = mp.begin(); it != mp.end(); it++) {
	// 	cout << it->first;
	// 	cout << " ";
	// 	cout << it->second;
	// 	cout << endl;
	// }

	char des[sizeof(str1)]={};
	// memcpy(des, &str1, sizeof(str1));

	str str2;
	memcpy(&str2, &str1, sizeof(str1));
	// memcpy(&str2, des, sizeof(str2));
	// for (map<char, int>::iterator it = mp2.begin(); it != mp2.end(); it++) {
	// 	cout << it->first;
	// 	cout << " ";
	// 	cout << it->second;
	// 	cout << endl;
	// }
	cout << "str2:" << sizeof(str2) << endl;
	return 0;
}
