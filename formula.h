#include<stdio.h>
#include<math.h>
//insert calculations for all formulas here
float weight[]={1,1,1,1,1,1,1,1,1};
float bias=0;
float *linearRegression(int m,float array[m][9]);
float sigmoidFunction(float z);
float mae();
float *linearRegression(int m,float array[m][9]){
    float z[m];
    float total;
    for(int i=0;i<m;i++){
        for(int j=0;j<10;j++){
            total+=array[i][j]*weight[j];
            //printf("%f\n",array[i][j])*weight[i];
            //printf("z: %f\n",z);
        }   
        total+=bias;
        z[i]=total;
        printf("z%d = %f\n",i+1,total);
    }
    //z+=bias;
    printf("Total: %f\n",z);
    //traverse z array
    for(int i=0;i<90;i++){
        printf("Element #%d:%f\n",i+1,z[i]);
    }

    return z;
}
float sigmoidFunction(float z){
    float sigmoid=1/(1+exp(-z));
    printf("SIGMABALLS: %f\n",sigmoid);
    return sigmoid;
}
float mae(){

}