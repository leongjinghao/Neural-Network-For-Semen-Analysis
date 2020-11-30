#include "function.h"
#include "output.h"

//function prototype
void perceptron(double *inputData, double *weightPT, double bias, int row, int col, double *sumPT, double *sigPT);
void arrayGenerate(double *arrayPT, int num);
double randFloat(double min, double max);

void perceptron(double *inputData, double *weightPT, double bias, int row, int col, double *sumPT, double *sigPT)
{
    //printf("\nIteration #%d\n",itr);
    
    //generate a pointer for array of sum (z) for each row of training data
    lineReg(inputData,weightPT,bias,row,col,sumPT);
    //generate a pointer for array of sigmoid value for each row of training data
    sigmoid(sumPT,sigPT,row);
}

//generate a random float for each column of input in array[num]
void arrayGenerate(double *arrayPT, int num)
{
    double *tempArrayPT;
    tempArrayPT = arrayPT;
    for (int i=0; i<num; i++)
    {
        *tempArrayPT = randFloat(-1.0,1.0);
        
        ++tempArrayPT;
        //checking
        //printf("Generated random Weight[%d] value: %f\n",i,weight[i]);
    }
}

//generate random float from min to max
double randFloat(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}