#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

void read_map_and_determine_the_size(char(*)[2000][2001],unsigned*,unsigned*) ;
void determine_each_block_size_and_replace_the_wall_symbol(char(*)[2000][2001],const unsigned,const unsigned,unsigned*,unsigned*) ;
void print_the_map(char(*)[2000][2001],const unsigned,const unsigned) ;
void fork_four_miners(char(*)[2000][2001],const unsigned,const unsigned,const unsigned,const unsigned,unsigned(*)[4]) ;
    unsigned miner1(char(*)[2000][2001],const unsigned,const unsigned,const unsigned,const unsigned) ;
    unsigned miner2(char(*)[2000][2001],const unsigned,const unsigned,const unsigned,const unsigned) ;
    unsigned miner3(char(*)[2000][2001],const unsigned,const unsigned,const unsigned,const unsigned) ;
    unsigned miner4(char(*)[2000][2001],const unsigned,const unsigned,const unsigned,const unsigned) ;

int main(){
    unsigned i , width , height , col_num_of_vertical_wall , row_num_of_horizontal_wall ;
    unsigned miners[4] ;
    char map[2000][2001] ;
    
    read_map_and_determine_the_size(&map,&width,&height) ;
    
    determine_each_block_size_and_replace_the_wall_symbol(&map,width,height,&col_num_of_vertical_wall,&row_num_of_horizontal_wall) ;
    
    print_the_map(&map,width,height) ;


    //printf("%d,%d\n",col_num_of_vertical_wall,row_num_of_horizontal_wall) ;

    fork_four_miners(&map,width,height,col_num_of_vertical_wall,row_num_of_horizontal_wall,&miners) ;


}

void read_map_and_determine_the_size(char(* m)[2000][2001], unsigned* _w, unsigned* _h){
    unsigned i , w , h ;
    for(h=0 ; scanf("%s", (*m)[h] )!=EOF ; h++){
    }
    for(w=0 ; (*m)[0][w]=='.' || (*m)[0][w]=='*' ||(*m)[0][w]=='#' ; w++ ){
    }
    
    *_w = w ;
    *_h = h ;
}

void determine_each_block_size_and_replace_the_wall_symbol(char(*m)[2000][2001],const unsigned w,const unsigned h,unsigned* _col,unsigned* _row){
    unsigned i , col , row ;
    for(i=0 ; i<w && ( (*m)[0][i]=='.' || (*m)[0][i]=='*' ) ; i++){
    }
    col = i ;
    for(i=0 ; i<h ; i++){
        (*m)[i][col]='|' ;
    }

    for(i=0 ; i<h && w>=2 && !( (*m)[i][0]=='#' && (*m)[i][0]=='#' ) ; i++ ){
    }
    row = i ;
    for(i=0 ; i<w ; i++){
        (*m)[row][i]='-' ;
    }

    *_col = col ;
    *_row = row ;
}


void print_the_map(char(* m)[2000][2001],const unsigned w,const unsigned h){
    unsigned i ;

    printf(" ") ;
    for(i=0 ; i<w ; i++){
        printf("-") ;
    }
    printf("\n") ;

    for(i=0 ; i<h ; i++){
        printf("|%s|\n", (*m)[i] ) ;
    }

    printf(" ") ;
    for(i=0 ; i<w ; i++){
        printf("-") ;
    }
    printf("\n") ;

    printf("map size: %d*%d\n",w,h) ;

}


void fork_four_miners(char(*m)[2000][2001],const unsigned w,const unsigned h,const unsigned col,const unsigned row,unsigned (*miners)[4]){
    
    pid_t pid ;
    unsigned m1,m2,m3,m4 ;

    int pipe1[2] ;
    int pipe2[2] ;
    int pipe3[2] ;
    int pipe4[2] ;
    pipe(pipe1) ;
    pipe(pipe2) ;
    pipe(pipe3) ;
    pipe(pipe4) ;
    char msgbuffer1[10] ;
    char msgbuffer2[10] ;
    char msgbuffer3[10] ;
    char msgbuffer4[10] ;

    pid=fork();
    if(pid<0){
        printf("fork failed!!\n") ;
        exit(1) ;
    }
    else if(pid==0){
        m1=miner1(m,0,0,row,col) ;
        char str[10] ;
        sprintf(str,"%d",m1) ;
        write(pipe1[1],str,strlen(str)+1) ;
    }
    else{
        pid=fork() ;
        if(pid<0){
            printf("fork failed!!\n") ;
            exit(1) ;
        }
        else if(pid==0){
            m2=miner2(m,0,col+1,row,w) ;
            char str[10] ;
            sprintf(str,"%d",m2) ;
            write(pipe2[1],str,strlen(str)+1) ;
        }
        else{
            pid=fork() ;
            if(pid<0){
                printf("fork failed!!\n") ;
                exit(1) ;
            }
            else if(pid==0){
                m3=miner3(m,row+1,0,h,col) ;
                char str[10] ;
                sprintf(str,"%d",m3) ;
                write(pipe3[1],str,strlen(str)+1) ;
            }
            else{
                pid=fork() ;
                if(pid<0){
                    printf("fork failed!!\n") ;
                    exit(1) ;
                }
                else if(pid==0){
                    m4=miner4(m,row+1,col+1,h,w) ;
                    char str[10] ;
                    sprintf(str,"%d",m4) ;
                    write(pipe4[1],str,strlen(str)+1) ;
                }
                else{
                    wait(NULL) ;
                    wait(NULL) ;
                    wait(NULL) ;
                    wait(NULL) ;
                    //printf("%d %d %d %d\n",m1,m2,m3,m4) ;
                    //printf("all miners are here!\n") ;
                    read(pipe1[0],msgbuffer1,10) ;
                    read(pipe2[0],msgbuffer2,10) ;
                    read(pipe3[0],msgbuffer3,10) ;
                    read(pipe4[0],msgbuffer4,10) ;
                    printf("%s\n",msgbuffer1) ;
                    printf("%s\n",msgbuffer2) ;
                    printf("%s\n",msgbuffer3) ;
                    printf("%s\n",msgbuffer4) ;

                }
            }
        }
    }
    
}


unsigned miner1(char(*m)[2000][2001],const unsigned x1,const unsigned y1,const unsigned x2,const unsigned y2){
    //printf("miner1!\n") ;
    unsigned i , j , count=0 ;
    for(i=y1 ; i<y2 ; i++){
        for(j=x1 ; j<x2 ; j++){
            //printf("miner1 %c\n",(*m)[j][i]) ;
            if((*m)[j][i]=='*') count++ ;
        }
    }
    printf("miner1 %d\n",count) ;
    return count ;
}


unsigned miner2(char(*m)[2000][2001],const unsigned x1,const unsigned y1,const unsigned x2,const unsigned y2){
    //printf("miner2!\n") ;
    unsigned i , j , count=0 ;
    for(i=y1 ; i<y2 ; i++){
        for(j=x1 ; j<x2 ; j++){
            //printf("miner2 %c\n",(*m)[j][i]) ;
            if((*m)[j][i]=='*') count++ ;
        }
    }
    printf("miner2 %d\n",count) ;
    return count ;
}


unsigned miner3(char(*m)[2000][2001],const unsigned x1,const unsigned y1,const unsigned x2,const unsigned y2){
    //printf("miner3!\n") ;
    unsigned i , j , count=0 ;
    for(i=y1 ; i<y2 ; i++){
        for(j=x1 ; j<x2 ; j++){
            //printf("miner3 %c\n",(*m)[j][i]) ;
            if((*m)[j][i]=='*') count++ ;
        }
    }
    printf("miner3 %d\n",count) ;
    return count ;
}



unsigned miner4(char(*m)[2000][2001],const unsigned x1,const unsigned y1,const unsigned x2,const unsigned y2){
    //printf("miner4!\n") ;
    unsigned i , j , count=0 ;
    for(i=y1 ; i<y2 ; i++){
        for(j=x1 ; j<x2 ; j++){
            //printf("miner4 %c\n",(*m)[j][i]) ;
            if((*m)[j][i]=='*') count++ ;
        }
    }
    printf("miner4 %d\n",count) ;
    return count ;
}






