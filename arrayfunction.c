#include<stdio.h>
float idk(float dd[5][3],float cc[3]){
    float toto=0;
    float a,b,c;
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            toto+=dd[i][j]*cc[j];
            printf("total is: %f\n",toto);
        }
    }
    return toto;
}
int main(){
    float total;
    float hi[5][3]= { {2,1,2} , {9.9,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {5,5,5}};
    float bye[3]= {1,-1,-1};
    total=idk(hi,bye);
    printf("Total: %f",total);
    return 0;
}
