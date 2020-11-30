#include "function.h"
#include "output.h"

//function prototype
double **perceptron(double *weightPT, double bias, int itr, FILE* outputFile, int row);
double *weightGenerate();
double randFloat(double min, double max);
void training(double mae, double *sigPT, double *sumPT, int itr, double *weightPT, double *bias, FILE* outputFile);

double **perceptron(double *weightPT, double bias, int itr, FILE* outputFile, int row)
{
    double *sumPT;
    double *sigPT;
    double mae;
    static double *returnArr[3];

    //printf("\nIteration #%d\n",itr);
    
    //generate a pointer for array of sum (z) for each row of training data
    sumPT = lineReg(inputTrain,weightPT,bias,row);
    returnArr[0] = sumPT;
    //generate a pointer for array of sigmoid value for each row of training data
    sigPT = sigmoid(sumPT,row);
    returnArr[1] = sigPT;
    //generate a single value for mae on the whole training data set
    mae = maeFunc(sigPT,outputTrain);
    returnArr[2] = &mae;
    //printf("\nmae: %f\n", *(returnArr[2]));
    outputMAE(outputFile,itr,mae);

    //invoke training function, training function will check if perceptron requires furtuer training
    //variable bias has to be pass by reference in order to capture the changed value
    //training(mae,sigPT,outputTrainPT,sumPT,inputTrainPT,itr,weightPT,&bias,outputFile);
    return returnArr;
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

//training function
void training(double mae, double *sigPT, double *sumPT, int itr, double *weightPT, double *bias, FILE* outputFile)
{
    double *weightErrPT;
    double biasErr;
    
    //printf("Training perceptron at iteration %d...\n",itr);
    weightErrPT=weightErrFunc(sigPT,sumPT,itr);
    
    //pointer to the weight array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight pointer while traversing
    double *tempWeightPT;
    tempWeightPT = weightPT;
    //pointer to the weight error array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight error pointer while traversing
    double *tempWeightErrPT;
    tempWeightErrPT = weightErrPT;

    //backwards propagate weight
    //change the value of weight base on the error fomula
    for (int i=0; i<col; i++)
    {
        *tempWeightPT-=((*tempWeightErrPT)*mu);
        
        //checking
        //printf("Weight[%d] changed to: %.10f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightPT;
        ++tempWeightErrPT;
    }

    //backwards propagate bias
    //calculate error of bias
    biasErr=biasErrFunc(sigPT,sumPT);
    *bias-=(biasErr*mu);

    //checking
    //printf("Bias err: %lf\n", biasErr);
    //printf("bias changed to: %f\n",*bias);
}