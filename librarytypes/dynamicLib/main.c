#include <stdio.h>
#include "foo.h"

int main(void){
    printf("inside main!\n");

    //call function belong to static lib
    foo();
}
