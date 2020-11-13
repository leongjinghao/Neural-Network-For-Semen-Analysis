#include "function.h"
#include "input.h"
#include "output.h"

//global pointer to store the address of different sets of data (array)
double *inputArrayPT;
double *inputTrainPT;
double *inputTestPT;
double *outputTrainPT;
double *outputTestPT;

//function prototype
double *perceptron(double *inputArrPT, double *weightPT, double bias, int itr, int inputRow, int inputCol);
void unpackage(double **inputArrPT);
double *weightGenerate(int numRandWeight);
double randFloat(double min, double max);

double *perceptron(double *inputTrainPT, double *weightPT, double bias, int itr, int inputRow, int inputCol)
{
    double *sumPT;
    double *sigPT;
    
    //generate a pointer for array of sum (z) for each row of training data
    sumPT = lineReg(inputTrainPT,weightPT,bias,inputRow,inputCol);
    
    //invoke training function, training function will check if perceptron requires furtuer training
    //variable bias has to be pass by reference in order to capture the changed value
    //training(mae,sigPT,outputTrainPT,sumPT,inputTrainPT,itr,weightPT,&bias,outputFile);

    return sumPT;
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
double *weightGenerate(int numRandWeight)
{
    //initialised weight array to store weight for each input value
    static double weight[col];

    for (int i=0; i<numRandWeight; i++)
    {
        weight[i]=randFloat(-1.0,1.0);
        
        //checking
        //printf("Generated random Weight[%d] value: %f\n",i,weight[i]);
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