#include <stdlib.h>
#include "function.h"
#include "input.h"

//global pointer to store the address of different sets of data (array)
double *inputArrayPT;
double *inputTrainPT;
double *inputTestPT;
double *outputTrainPT;
double *outputTestPT;
double mae;
int itr = 0;

//function prototype
void perceptron(double *inputArrPT, double *weightPT, double bias);
void unpackage(double **inputArrPT);
double *weightGenerate();
double randFloat(double min, double max);

void perceptron(double *inputTrainPT, double *weightPT, double bias)
{
    double *sumPT;
    double *sigPT;
    double *weightErrPT;
    
    sumPT = lineReg(inputTrainPT,weightPT,bias);
    sigPT = sigmoid(sumPT);
    mae = maeFunc(sigPT,outputTrainPT);
    ++itr;
    printf("\nMAE at iteration %d: %f",itr,mae); 

    if (mae>targetMAE)
    {
        printf("\nNOOOOOOOOOOOOOOOO");
        weightErrPT=weightErrFunc(sigPT,outputTrainPT,sumPT,inputTrainPT);
        
        double *tempWeightPT;
        tempWeightPT = weightPT;
        double *tempWeightErrPT;
        tempWeightErrPT = weightErrPT;
        for (int i=0; i<col; i++)
        {
            *tempWeightPT-=((*tempWeightErrPT)*mu);
        }
        sumPT = lineReg(inputTrainPT,weightPT,bias);
        sigPT = sigmoid(sumPT);
        mae = maeFunc(sigPT,outputTrainPT);
        ++itr;
        printf("\nMAE at iteration %d: %f",itr,mae); 
        //perceptron(inputTrainPT,weightPT,bias);
    }
    else
    {
        printf("MAE met 0.25 tolarance at %f at iteration %d",mae,itr);
    }
    
}

//function for unpackaging the returnArr (returned pointers)
//inputArrPT is a pointer of pointers, hence will need to use **
void unpackage(double **inputArrPT)
{
    inputArrayPT = *(inputArrPT);
    inputTrainPT = *(inputArrPT+1);
    inputTestPT = *(inputArrPT+2);
    outputTrainPT = *(inputArrPT+3);
    outputTestPT = *(inputArrPT+4);
}

//generate a random weight for each column of input
double *weightGenerate()
{
    //initialised weight array to store weight for each input value
    static double weight[col];

    for (int i=0; i<col; i++)
    {
        weight[i]=randFloat(-1.0,1.0);
        
        //checking
        //printf("weight at %d: %f\n", i+1, weight[i]);
    }

    return weight;
}

//generate random float from min to max
double randFloat(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
