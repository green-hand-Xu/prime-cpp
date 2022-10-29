#include <stdio.h>
void swap1(int x, int y) {   
    int tmp;   
    tmp = x; x = y; y = tmp;
}
void swap2(int *x, int *y) { 
    int tmp;  
    tmp = *x; *x = *y; *y = tmp;
}
void caller()
{  
    int a = 10;  
    int b = 20;  
    swap1(a,b);   
    printf("%d %d\n",a,b); 
    // Changed the value pointed by the pointer
    swap2(&a,&b);  
    printf("%d %d\n",a,b);
}
int main()
{ 
    caller();  
    return 0;
}