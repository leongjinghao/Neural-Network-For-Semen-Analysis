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
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, double *weightPT, double *bias);

void perceptron(double *inputTrainPT, double *weightPT, double bias)
{
    double *sumPT;
    double *sigPT;
    
    
    sumPT = lineReg(inputTrainPT,weightPT,bias);
    sigPT = sigmoid(sumPT);
    mae = maeFunc(sigPT,outputTrainPT);
    ++itr;
    printf("\nMAE at iteration %d: %f\n",itr,mae); 

    //invoke training function, training function will check if perceptron requires furtuer training
    //variable bias has to be pass by reference in order to capture the changed value
    training(sigPT,outputTrainPT,sumPT,inputTrainPT,weightPT,&bias);
    
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

//training function
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, double *weightPT, double *bias)
{
    double *weightErrPT;
    double biasErr;

    //backwards propagate weight and bias if mae did not reach tolerance value
    if (mae>targetMAE)
    {
        printf("Training perceptron at iteration %d...\n",itr);
        weightErrPT=weightErrFunc(sigPT,outputTrainPT,sumPT,inputTrainPT,itr);
        
        //pointer to the weight array, will be used to change the value of the weight directly
        //temporary pointer is used to maintain original pointed address of the weight pointer while traversing
        double *tempWeightPT;
        tempWeightPT = weightPT;
        //pointer to the weight error array, will be used to change the value of the weight directly
        //temporary pointer is used to maintain original pointed address of the weight error pointer while traversing
        double *tempWeightErrPT;
        tempWeightErrPT = weightErrPT;
        //variable to store error of bias
        double biasErr;

        //backwards propagate weight
        //change the value of weight base on the error fomula
        for (int i=0; i<col; i++)
        {
            *tempWeightPT-=((*tempWeightErrPT)*mu);
            
            //checking
            printf("Weight[%d] at iteration %d: %f\n",i,itr,*tempWeightPT);

            //move to next column for both tempWeightPT and tempWeightErrPT
            ++tempWeightPT;
            ++tempWeightErrPT;
        }

        //backwards propagate bias
        //calculate error of bias
        biasErr=biasErrFunc(sigPT,outputTrainPT,sumPT,itr);
        *bias-=(biasErr*mu);

        //checking
        printf("bias at iteration %d: %f\n",itr,*bias);

        //invoke perceptron to move on to next iteration using new weight and bias
        perceptron(inputTrainPT,weightPT,*bias);
    }
    else
    {
        printf("Training completed!\nMAE met %f tolarance at %f at iteration %d\n",targetMAE,mae,itr);
    }
}