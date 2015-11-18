#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#include<stdlib.h>
#include<string.h>

char* msg="this is a message!!!" ;

int main(){
    char buf[1024] ;
    int fd[2] ;
    pipe(fd) ; // create pipe
    pid_t pid=fork() ;
    if(pid<0){
        printf("fork failed!!\n") ;
        exit(2) ;
    }
    else if(pid==0){ // child process
        write(fd[1],msg,strlen(msg)+1) ;
        write(fd[1],msg,strlen(msg)+1) ;
        printf("Child: send message: %s*2\n",msg) ;
    }
    else if(pid>0){ // parent process
        wait(NULL) ;
        printf("waiting a message...\n") ;
        read(fd[0],buf,10) ;
        printf("Parent: got message: %s\n",buf) ;
        read(fd[0],buf,100) ;
        printf("Parent: got message: %s\n",buf) ;
        read(fd[0],buf,100) ;
        printf("Parent: got message: %s\n",buf) ;
    }

}
