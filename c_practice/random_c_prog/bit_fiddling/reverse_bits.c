#include <stdio.h>

int main(){
    int data = 0x1010; //
    int i;
    printf("data before : ");
    for(i = 15; i >= 0; i--){
        printf("%d", (data>>i) & 0x1);
    }
    printf("\n");
    printf("data after : ");
    data = data ^ 0xffff;
    for(i = 15; i >= 0; i--){
        printf("%d", (data>>i) & 0x1);
    }
    printf("\n");
}
