#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define TRAIN 90
#define TEST 10
#define RATE 0.05
//global declaration
float weight[9]={1,1,1,1,1,1,1,1,1};
float bias=1;
float linearRegtrain[TRAIN];//array to store all values of linear regression for train
float sigmoidtrain[TRAIN];
float linearRegtest[TEST];//array to store all values of linear regression for test
float sigmoidtest[TEST];
float mae=1;
float werr[9],berr;
float mmse=0;
//function prototype
float linearRegression(float inputarray[][9],float linearRegarray[],int number);
float sigmoidActivation(float linearRegarray[],float sigmoidarray[],int number);
float getmae(float sigmoidarray[],float outputarray[],int number);
//float feedforward(FILE *plotfilename,FILE *outputfilename);
void weightErr();
void biasErr();
void feedback();
void getmmse(float sigmoidarray[],float outputarray[],int number);
//function
float linearRegression(float inputarray[][9],float linearRegarray[],int number){
    float total;
    //Linear Regression
    for(int i=0;i<number;i++){
        total=0;//reset total value for each row of input
        for(int j=0;j<9;j++){
            //printf("array[%d][%d] = %f || w[%d] = %f || ",i,j,array[i][j],j,w[j]);
            total+=inputarray[i][j]*weight[j];
            //printf("Total: %f\n",total);
        }
        total+=bias;
        //printf("Total+Bias: %f\n",total);
        linearRegarray[i]=total;
    }
}
float sigmoidActivation(float linearRegarray[],float sigmoidarray[],int number){
    //Sigmoid Activation
    for(int i=0;i<number;i++){
        sigmoidarray[i]=(1/(1+exp(-linearRegarray[i])));
        //printf("Sigmoid %d = %f\n",i+1,sigmoid[i]);
    }
}
float getmae(float sigmoidarray[],float outputarray[],int number){
    //MAE
    mae=0;//reset mae to 0 per iteration
    for(int i=0;i<number;i++){
        mae+=fabs(sigmoidarray[i]-outputarray[i]);
        //printf("sigmoid %d: %f || outputtrain %d: %f\n",i+1,sigmoid[i],i+1,outputtrain[i]);
        //printf("MAE[%d]: %f\n",i+1,mae);
    }
    mae=mae/number;
    //printf("MAE: %f\n",mae);
}
void weightErr(){
    float sum;
    for(int j=0;j<9;j++){
        sum=0;
        for(int i=0;i<TRAIN;i++){
            sum+=((sigmoidtrain[i]-outputtrain[i])*(exp(linearRegtrain[i])/pow((1+exp(linearRegtrain[i])),2))*inputarray[i][j])/TRAIN;
            //printf("sum: %f",sum);
        }
        werr[j]=sum;
        //printf("werr[%d]: %f\n",j,sum);
    }
}
void biasErr(){
    //summation
    float sum=0;
    for(int i=0;i<TRAIN;i++){
        sum+=((sigmoidtrain[i]-outputtrain[i])*(exp(linearRegtrain[i])/pow((1+exp(linearRegtrain[i])),2)))/TRAIN;
    }
    berr=sum;
}
void feedback(){
    weightErr();
    //for(int i=0;i<9;i++){
    //    printf("weight error %d: %f\n",i+1,werr[i]);
    //}
    biasErr();
    //printf("bias error: %f\n",berr);
    //NEW WEIGHT
    for(int i=0;i<9;i++){
        weight[i]=weight[i]-RATE*werr[i];
        //printf("new w%d: %f\n",i+1,weight[i]);
    }
    //NEW BIAS
    bias=bias-RATE*berr;
    //printf("new b: %f\n",bias);
}
void rngwb(){
    bias=rand()/(float)(RAND_MAX)*2-1;
    for(int i=0;i<9;i++){
        weight[i]=rand()/(float)(RAND_MAX)*2-1;
    }
}
void getmmse(float sigmoidarray[],float outputarray[],int number){
    //MMSE
    mmse=0;
    for(int i=0;i<number;i++){
        mmse+=pow((sigmoidarray[i]-outputarray[i]),2);
        //printf("sigmoid %d: %f || outputtrain %d: %f\n",i+1,sigmoid[i],i+1,outputtrain[i]);
        //printf("MSSE[%d]: %f\n",i+1,mmse);
    }
    mmse=mmse/number;
    //printf("MMSE: %f\n",mmse);
}
void confusionMatrix(){
    float accuracy;
    int check,TP=0,TN=0,FP=0,FN=0;
    for(int i=0;i<TRAIN;i++){
        //printf("Sigmoid Train #%d: %f\n",i,sigmoidtrain[i]);
        if(sigmoidtrain[i]<0.5){
            check=0;
            if(check==outputtrain[i]){
                TN++;
            }
            else{
                FN++;
            }
        }
        else{
            check=1;
            if(check==outputtrain[i]){
                TP++;
            }
            else{
                FP++;
            }
        }
    }
    for(int i=0;i<TEST;i++){
       //printf("Sigmoid Test #%d: %f\n",i,sigmoidtest[i]);
       if(sigmoidtest[i]<0.5){
            check=0;
            if(check==outputtest[i]){
                TN++;
            }
            else{
                FN++;
            }
        }
        else{
            check=1;
            if(check==outputtest[i]){
                TP++;
            }
            else{
                FP++;
            }
        }
    }
    printf("TP:%d FP:%d TN:%d FN:%d\n",TP,FP,TN,FN);
    accuracy=(TP+TN)/(TP+TN+FP+FN+0.0);
    printf("Accuracy: %f%\n",accuracy);
}