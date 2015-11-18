#include<stdio.h>
#include<stdlib.h>

int main(){

    int aInt = 368;
    char str[15];
    sprintf(str, "%d", aInt+1);

    printf("%s\n",str) ;

    printf("%d\n",atoi(str)+1) ;
}
