#include <stdio.h>
#include <math.h>

struct data{
    unsigned int a : 4;
    unsigned int b : 4;
    unsigned int c : 16;
    unsigned int d : 8;
};

union extract{
    struct data udata;
    unsigned int e;
}num;


int main(){
    num.e = 0x12345678;
    printf("a is : %x\n", num.udata.a);
    printf("b is : %x\n", num.udata.b );
    printf("c is : %x\n", num.udata.c);
    printf("d is : %x\n", num.udata.d);
}

#if  0
int main(){
    unsigned int num=0x12345678, a=0, b=0, c=0, d=0, e=0;
    int a_pos = 3; // at last a should be 0x8
    int b_pos = 7; // at last b should be 0x7
    int c_pos = 15; // at last c should be 0x56
    int d_pos = 27; // at last d should be 0x234; and e should be 0x1
    unsigned int a_div = (unsigned int)(pow(2, a_pos+1));
    unsigned int b_div = (unsigned int)(pow(2, b_pos+1));
    unsigned int c_div = (unsigned int)(pow(2, c_pos+1));
    unsigned int d_div = (unsigned int)(pow(2, d_pos+1));
    int temp;
    printf("\noriginal number is : %x\n\n", num);

    printf("number a : %x\n", a = num % a_div);
    printf("\n");
    printf("number b : %x\n", b = (num % b_div)/a_div);
    printf("\n");
    printf("number c : %x\n", c = (num % c_div)/b_div);
    printf("\n");
    printf("number d : %x\n", d = (num % d_div)/c_div);
    printf("\n");
    printf("number e : %x\n", e = (num / d_div));
    printf("\n");
}
#endif
