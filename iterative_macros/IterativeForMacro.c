#include <stdio.h>
#include <stdbool.h>

#define ITERATE_OVER_MYSTRING(str, mychar)      \
{                                               \
    int cnt;                                    \
    for(cnt=0;str[cnt] != '\0' ; cnt++){         \
        mychar = str[cnt];                      \

#define ITERATION_COMPLETES       }}

    int
main (int argcnt, char **vargs)
{
    char  mychar;
    char *searchIn = "I Love Random String!";
    ITERATE_OVER_MYSTRING (searchIn, mychar){
        printf ("%c", mychar);
    }ITERATION_COMPLETES;
    printf ("\n\nIteration Completed!\n");
}
