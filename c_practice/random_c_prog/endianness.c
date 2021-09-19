#include <stdio.h>

int main(){
    int data = 0x01;
    char *p = &data;
    if(p){
        printf("Machine is little ending\n");
    }else{
        printf("Machine is big ending\n");
    }
}
