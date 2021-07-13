#include <stdio.h>
#include "lib1/headers/foo1.h"
#include "lib2/headers/foo2.h"


int main(void){
    printf("inside main!\n");

    //call function belong to static lib
    foo1();
    foo2();
}
