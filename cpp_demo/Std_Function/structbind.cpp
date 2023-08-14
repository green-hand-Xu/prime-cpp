#include <iostream>
#include <string>
#include <utility>

//结构化绑定用于数组 identifier-list的长度必须与数组长度相等
void shuzu(){
    int arry[3]={1,2,3};

    auto [one,two,three] = arry;

    std::cout<<one<<two<<three<<std::endl;
}

//带初始化列表的 if 语句 从c++17 开始支持
//在 if () 里声明的变量 出了 if 语句块范围 就不可用了
void ifwithinit(){
    if (int a = 1 ; a==1)
    {
        std::cout<<"a = "<< a <<std::endl;
    }
    
}

// 根据SFINAE原则，sizeof(T)不能正确计算就进入此分支,value为false;
template <typename T, typename = void>
struct is_complete_type : std::false_type {

};

// sizeof(T)能正确计算就进入此分支,value为true;
template <typename T>
struct is_complete_type<T, decltype(void(sizeof(T)))> : std::true_type {

};

void fun1(){
std::cout << "int is complete type: " << is_complete_type<int>::value << std::endl;
// output 1(true) for int
// 前向声明类型
struct other;
std::cout << "other is complete type: " << is_complete_type<other>::value << std::endl;
// std::cout<<" complete struct size == "<< sizeof(other)<<std::endl;
// output 0(false) for www forward declaration
}


class Transcript { /* ... */ };

class Student
{
public:
    const char* name;
    Transcript score;

    std::string getName() const { 
        return name; 
        }

    const Transcript& getScore() const 
    { 
        return score; 
    }

    template<std::size_t I>
    decltype(auto) get() const
    {
        if constexpr (I == 0){
            return getName();
        }else if constexpr (I == 1){
            return getScore(); 
        }else{
            static_assert(I < 2);
        }       
    }
};

namespace std
{
template<>
struct tuple_size<Student>
    : std::integral_constant<std::size_t, 2> { };

template<>
struct tuple_element<0, Student> { using type = decltype(std::declval<Student>().getName()); };

template<>
struct tuple_element<1, Student> { using type = decltype(std::declval<Student>().getScore()); };
}

int main()
{
    std::cout << std::boolalpha;
    Student s{ "Jerry", {} };
    const auto& [name, score] = s;
    std::cout << name << std::endl;
    std::cout << (&score == &s.score) << std::endl;

    return 0;
}