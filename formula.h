#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define TRAIN 90
#define RATE 0.05
//global declaration
float weight[9]={1,1,1,1,1,1,1,1,1};
float bias=1;
float linearReg[TRAIN];//array to store all values of linear regression
float sigmoid[TRAIN];
float mae=1;
float werr[9],berr;
float mmse=0;
//function prototype
float feedforward(float array[][9],float w[9],float b,FILE *plotfilename,FILE *outputfilename);
void weightErr();
void biasErr();
void feedback();
//function
float feedforward(float array[][9],float w[9],float b,FILE *plotfilename,FILE *outputfilename){
    static int itrcount=0;
    itrcount++;
    //printf("\nITERATION %d\n",itrcount);
    float total=0;
    //Linear Regression
    for(int i=0;i<TRAIN;i++){
        total=0;//reset total value for each row of input
        for(int j=0;j<9;j++){
            //printf("array[%d][%d] = %f || w[%d] = %f || ",i,j,array[i][j],j,w[j]);
            total+=array[i][j]*w[j];
            //printf("Total: %f\n",total);
        }
        total+=b;
        //printf("Total+Bias: %f\n",total);
        linearReg[i]=total;
    }

    //check linearReg[]
    //traverseArray(TRAIN,linearReg);

    //Sigmoid Activation
    
    for(int i=0;i<TRAIN;i++){
        sigmoid[i]=(1/(1+exp(-linearReg[i])));
        //printf("Sigmoid %d = %f\n",i+1,sigmoid[i]);
    }

    //MMSE (Need to shift somewhere else, only before trained and after trained is required)
    mmse=0;
    for(int i=0;i<TRAIN;i++){
        mmse+=pow((sigmoid[i]-outputtrain[i]),2);
        //printf("sigmoid %d: %f || outputtrain %d: %f\n",i+1,sigmoid[i],i+1,outputtrain[i]);
        //printf("MSSE[%d]: %f\n",i+1,mmse);
    }
    mmse=mmse/TRAIN;
    printf("MMSE: %f\n",mmse);
    fprintf(outputfilename,"%d   %10f\n",itrcount,mmse);

    //MAE
    mae=0;//reset mae to 0 per iteration
    for(int i=0;i<TRAIN;i++){
        mae+=fabs(sigmoid[i]-outputtrain[i]);
        //printf("sigmoid %d: %f || outputtrain %d: %f\n",i+1,sigmoid[i],i+1,outputtrain[i]);
        //printf("MAE[%d]: %f\n",i+1,mae);
    }
    mae=mae/TRAIN;
    //printf("MAE: %f\n",mae);
    fprintf(plotfilename,"%d   %.10f\n",itrcount,mae);
    return mae;
}
void weightErr(){
    float sum,fuck;
    for(int j=0;j<9;j++){
        sum=0;
        for(int i=0;i<TRAIN;i++){
            sum+=((sigmoid[i]-outputtrain[i])*(exp(linearReg[i])/pow((1+exp(linearReg[i])),2))*inputarray[i][j])/TRAIN;
            //printf("sum: %f",sum);
            werr[j]=sum;
            
        }
        //printf("werr[%d]: %f\n",j,sum);
        //printf("fuck %d: %f\n",j+1,fuck);
    }
}
void biasErr(){
    //summation
    float sum=0;
    for(int i=0;i<TRAIN;i++){
        sum+=((sigmoid[i]-outputtrain[i])*(exp(linearReg[i])/pow((1+exp(linearReg[i])),2)))/TRAIN;
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