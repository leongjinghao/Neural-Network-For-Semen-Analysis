#include <stdio.h>
#include "def.h"
#include "function.h"
#include "input.h"

//keep the pointer variable accessible within the file only
static double *inputArrayPT;
static double *inputTrainPT;
static double *inputTestPT;
static double *outputTrainPT;
static double *outputTestPT;

int main()
{
    /*double input[row][col] = { {5,5,5} , {2,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {1,1,1} };
    double actual[row] = {1,1,0,-1,0};*/
    double weight[col] = {1,1,1,1,1,1,1,1,1};
    double *weightPT = weight;
    char filename[] = FILENAME;
    
    double *inputArrPT;
    double *sumPT;
    double *sigPT;
    double mae;
    int itr = iteration;

    //call function to read in data set input into array and traverse it
    inputArrPT = inputData(filename);

    //Unpackaging the all pointers stored inside inputArr
    /*double *inputArrayPT;
    inputArrayPT = *(inputArrPT);
    printf("\nAddress: test"); 
    double *inputTrainPT;
    inputTrainPT = *(inputArrPT+1);
    double *inputTestPT;
    inputTestPT = *(inputArrPT+2);
    double *outputTrainPT;
    outputTrainPT = *(inputArrPT+3);
    double *outputTestPT;
    outputTestPT = *(inputArrPT+4);*/
    unpackage(inputArrPT);
    printf("\ninputArr 1st element: %f\n", *inputArrayPT);
    printf("inputTrain 1st element: %f\n", *inputTrainPT);

    sumPT = lineReg(inputTrainPT,weightPT);
    sigPT = sigmoid(sumPT);
    mae = maeFunc(sigPT,outputTrainPT,itr);
    printf("\nMAE: %f", mae); 

    

    return 0;
}

//function for unpackaging the returnArr (returned pointer)
void unpackage(double **inputArrPT)
{
    inputArrayPT = *(inputArrPT);
    inputTrainPT = *(inputArrPT+1);
    inputTestPT = *(inputArrPT+2);
    outputTrainPT = *(inputArrPT+3);
    outputTestPT = *(inputArrPT+4);
}