#include<stdio.h>
#include<stdlib.h>


int main(){
    unsigned i , height ;
    char map[2000][20001] ;
    
    for(height=0 ; scanf("%s",map[height])!=EOF ; height++) ;
    
    for(i=0 ; i<height ; i++){
        printf("%s\n",map[i]) ;
    }

}





