#include<stdio.h>
#include<stdlib.h>

void read_map_and_determine_the_size(char(*)[2000][2001],unsigned*,unsigned*) ;
void determine_each_block_size_and_replace_the_wall_symbol(char(*)[2000][2001],const unsigned,const unsigned,unsigned*,unsigned*) ;

void print_the_map(char(*)[2000][2001],const unsigned,const unsigned) ;

int main(){
    unsigned i , width , height , col_num_of_vertical_wall , row_num_of_horizontal_wall ;
    char map[2000][2001] ;
    
    read_map_and_determine_the_size(&map,&width,&height) ;
    
    determine_each_block_size_and_replace_the_wall_symbol(&map,width,height,&col_num_of_vertical_wall,&row_num_of_horizontal_wall) ;
    
    print_the_map(&map,width,height) ;


    //printf("%d,%d\n",col_num_of_vertical_wall,row_num_of_horizontal_wall) ;

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















