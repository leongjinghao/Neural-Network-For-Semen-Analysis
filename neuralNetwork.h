#include <stdlib.h>
#include "perceptron.h"

double neuralNetwork(double *inputData, double *weightH, double *biasH, double *weightO, double biasO, int row, int itr, double *sum, double *sig, double *sigHidden, FILE* outputFile);
void training(double *sigHidden, double *sigPT, double *sumPT, double *weightPT, double *biasO, double *weightHPT, double *biasH, double*sumHPT, int itr);

double neuralNetwork(double *inputData, double *weightH, double *biasH, double *weightO, double biasO, int row, int itr, double *sum, double *sig, double *sigHidden, FILE* outputFile)
{
    double (*weightHPT)[9] = weightH;
    double (*sumPT)[trainRow] = sum;
    double (*sigPT)[trainRow] = sig;
    double *sigSinglePT = sig;
    double *sigHPT = sigHidden;
    double mae;

    //Hidden layer
    //perceptron 1
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 2
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 3
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 4
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 5
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 6
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);
    //perceptron 7
    ++weightHPT, ++biasH, ++sumPT, ++sigPT;
    perceptron(inputData,weightHPT,*biasH,row,dataCol,sumPT,sigPT);

    //rearrange sigmoid array of all the hidden layers
    sigPT = sigSinglePT;
    for (int i=0;i<row;i++)
    {
        *sigHPT = **sigPT;
        *(sigHPT+1) = **(sigPT+1);
        *(sigHPT+2) = **(sigPT+2);
        *(sigHPT+3) = **(sigPT+3);
        *(sigHPT+4) = **(sigPT+4);
        *(sigHPT+5) = **(sigPT+5);
        *(sigHPT+6) = **(sigPT+6);

        ++sigSinglePT;
        sigPT=sigSinglePT;
        sigHPT=sigHPT+7;
    }

    //repoint pointer
    sigHPT = sigHidden;
    sigPT = sig;

    /*for (int i=0;i<row;i++)
    {
        printf("Row %d: %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",i+1,*sigHPT,*(sigHPT+1),*(sigHPT+2),*(sigHPT+3),*(sigHPT+4),*(sigHPT+5),*(sigHPT+6));
        sigHPT=sigHPT+7;
    }
    sigHPT = sigHidden;*/

    //Output layer
    //perceptron 8
    ++sumPT;
    sigPT=sigPT+7;

    perceptron(sigHPT,weightO,biasO,row,7,sumPT,sigPT);

    mae = maeFunc(sigPT,outputTrain);
    outputMAE(outputFile,itr,mae);

    return mae;
}

//training function
void training(double *sigHidden, double *sigOPT, double *sumOPT, double *weightOPT, double *biasO, double *weightHPT, double *biasH, double*sum, int itr)
{
    double expA;
    double weightOErr[7];
    double weightHErr[9];
    memset(weightOErr,0.0,sizeof weightOErr);
    memset(weightHErr,0.0,sizeof weightHErr);
    double *weightOErrPT=weightOErr;
    double *weightHErrPT=weightHErr;
    double biasOErr;
    double biasHErr;
    
    //printf("Training perceptron at iteration %d...\n",itr);
    weightOErrFunc(sigHidden,sigOPT,sumOPT,7,&expA,weightOErrPT);
    
    //pointer to the weight array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight pointer while traversing
    double *tempWeightOPT = weightOPT;
    //pointer to the weight error array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight error pointer while traversing
    double *tempWeightOErrPT = weightOErrPT;

    //backwards propagate output layer weight
    //Perceptron 8
    //change the value of weight base on the error fomula
    for (int i=0; i<7; i++)
    {
        *tempWeightOPT-=((*tempWeightOErrPT)*mu);
        
        //checking
        //printf("WeightP1[%d] changed to: %.10f\n",i,*tempWeightOPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightOPT;
        ++tempWeightOErrPT;
    }

    //backwards propagate output layer bias
    //calculate error of bias
    //biasOErrFunc(sigOPT,sumOPT,&biasOErr);
    //calculation of error of bias == expA
    *biasO-=(expA*mu);


    //backwards propagate hidden layer weights & bias
    //retrieve all hidden layer perceptrons' weights & bias
    double *tempWeightHPT = weightHPT;
    double *tempWeightHErrPT;
    double *tempBiasHPT = biasH;
    double (*sumHPT)[trainRow] = sum;
    //perceptron 1
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("WeightP2[%d] changed to: %.10f\n",i,*tempWeightOPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 2
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 3
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 4
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 5
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 6
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //perceptron 7
    memset(weightHErrPT,0.0,sizeof weightHErrPT);
    ++tempWeightOPT;
    ++tempBiasHPT;
    ++sumHPT;
    weightHErrFunc(expA,*tempWeightOPT,sumHPT,dataCol,weightHErrPT);
    biasHErrFunc(expA,*tempWeightOPT,sumHPT,&biasHErr);
    tempWeightHErrPT = weightHErrPT;
    for (int i=0; i<7; i++)
    {
        *tempWeightHPT-=((*tempWeightHErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightHPT;
        ++tempWeightHErrPT;
    }
    *tempBiasHPT-=(biasHErr*mu);

    //checking
    //printf("Bias err: %lf\n", biasErr);
    //printf("bias changed to: %f\n",*bias);
}