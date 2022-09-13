#include <iostream>
#include <string>
#include <sstream>
using namespace std;
/*
 *    两数相加
 *给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 *请你将两个数相加，并以相同形式返回一个表示和的链表。
 *你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
*/

/*
 * Definition for singly-linked list.
 */

  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

    }
};

ListNode* CreatList(){
    ListNode *head,*p,*tail; //声明 头尾 数据 节点指针
    head=p=tail=new ListNode;
    cout<<"输入要插入的节点数据,输入0结束"<<endl;
    cin>>p->val;
    while ( p->val != 0 )
    {
       tail->next = p;
       tail = p;

       p = new ListNode;
       cin>>p->val;
    }
    return head;  
}

void Show(ListNode *head)              //链表输出函数
{
	ListNode *p;
	p=head;
	while(p)
	{
		cout<<p->val<<" ";
		p=p->next;
	}
	cout<<endl; 
	cout<<"链表输出完毕！！！"<<endl;
}

int main(){

    ListNode *L1;
    ListNode *L2;
    string a;
    string b;
    int c;
    int d;
    int e;
    string f;
    cout<<"创建L1"<<endl;
    L1=CreatList();
    cout<<"创建L2"<<endl;
    L2=CreatList();

    stringstream sstream;

    while (L1 != NULL)
    {
        sstream << L1->val;
        L1 = L1->next;
    }
    sstream >> a; //123

    //清空流
    sstream.str(" ");
    sstream.clear();

    for(int i=a.size()-1;i >= 0; i--){ // a.size()-1 是string最后一个字符
        sstream<<a[i];
    }
    sstream >> c;
    cout <<"L1:"<<c<<endl;

    //清空流
    sstream.str(" ");
    sstream.clear();

    while (L2 != NULL){
        sstream << L2->val;
        L2=L2->next;
    }
    sstream >> b;

    //清空流
    sstream.str(" ");
    sstream.clear();

    for(int i=b.size()-1;i >= 0; i--){ // a.size()-1 是string最后一个字符
        sstream<<b[i];
    }
    sstream>>d;
    cout <<"L2:"+sstream.str()<<endl;

    e = c + d;

    //清空流
    sstream.str(" ");
    sstream.clear();

    sstream << e;
    sstream >> f;

    //清空流
    sstream.str(" ");
    sstream.clear();

    ListNode *L3,*p,*tail; //声明 头尾 数据 节点指针
    L3=p=tail=new ListNode;
    int g;

    for(int i = f.size()-1;i>=0;i--){
        sstream << f[i];
        sstream >> g;
        p->val = g;
        //清空流
        sstream.str(" ");
        sstream.clear();

        tail->next = p;
        tail = p;
        p = new ListNode;
    }

    Show(L3);
    return 0;
}


