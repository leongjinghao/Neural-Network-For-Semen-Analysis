#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    int i=0;
    srand(time(NULL));
    while(i<100){
        float x=rand()/(float)(RAND_MAX)*2-1;
        printf("Number: %f\n",x);
        i++;
    }  
}