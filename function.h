#include <math.h>
#include "def.h"

//global variable
double bias;
//iteration by default is 1

//function prototype
double *lineReg(double *inputPT, double *weightPT, double bias);
double *sigmoid(double *sum);
double maeFunc(double *sigPT, double *actPT);
double *weightErrFunc(double *sigPT, double *actPT, double *sumPT, double *inputTrainPT);
double floatAbs(double a);

//linear regresion function, return pointer variable of sum (z)
double *lineReg(double *inputPT, double *weightPT, double bias)
{
    //pointer to traverse each row of input data, each row having n column of data, n=col
    double (*inputRowPT)[col];
    inputRowPT = inputPT;
    //pointer to traverse each element of input data
    double *inputColPT;
    
    //pointer to traverse each column of weight data
    double *weightColPT;
    weightColPT = weightPT;

    double summation;
    //array to store summation (z) for each row, static to make sure the array remain exist after function call
    static double sum[trainRow];

    for (int i=0; i<trainRow; i++)
    {
        //let the column pointer point at the first element of current row
        inputColPT = *inputRowPT;
        for (int k=0; k<col; k++)
        {
            summation+=((*inputColPT)*(*weightColPT));
            
            //checking
            //printf("\nEQ: %f x %f\n", (*inputColPT), (*weightColPT));
            
            //move to next column for both input and weight
            ++inputColPT;
            ++weightColPT;
        }
        summation+=bias;
        sum[i] = summation;
        //flush value for summation to calculate next row's sum
        summation = 0;
        
        //after finished traversing the row, let the row pointer for input to point at next row
        ++inputRowPT;
        //reset weight pointer to point at the first element for next loop
        weightColPT = weightPT;

        /*checking
        printf("Training row: %d\n", i+1);
        printf("sum: %f\n", sum[i]);
        printf("address: %d\n",&sum[i]);*/
    }
    
    return sum;
}

//sigmoid activation function using pointer of sum (z), return pointer variable sigPT
double *sigmoid(double *sumPT)
{
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT = sumPT;
    //array to store y bar (sigmoid function output), static to make sure the array remain exist after function call
    static double sig[trainRow];

    for (int i=0; i<trainRow ; i++)
    {
        //not using *tempSumPT+i because ++tempSumPT is faster
        sig[i] = 1/(1+exp(-*tempSumPT));

        //checking
        printf("\nSigmoid function at row #%d:     sum = %f     addressSum = %d     sig = %f",i+1,*tempSumPT,tempSumPT,sig[i]);

        //move to next element
        ++tempSumPT;
    }
    return sig;
}

//mean abs error
double maeFunc(double *sigPT, double *actPT) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT;
    tempSigPT = sigPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT;
    tempActPT = actPT;
    //variable for output of MAE per iteration
    double total=0;

    for (int i=0; i<trainRow; i++)
    {
        total += floatAbs(*(tempSigPT+i)-*(tempActPT+i));
    }
    return total/trainRow;
}

//error calculation of weight
double *weightErrFunc(double *sigPT, double *actPT, double *sumPT, double *inputTrainPT) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT;
    tempSigPT = sigPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT;
    tempActPT = actPT;
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT;
    tempSumPT = sumPT;
    //variable for first part of the expression for the error of weight
    double expressionA;
    //row and column pointer to traverse the data (array) to retrieve each x (input)
    double (*rowPT)[col];
    rowPT = inputTrainPT;
    double *colPT;
    //array to store error of each x (input)
    static double wErr[col];
    
    for (int i=0; i<trainRow; i++)
    {
        //first part of the expression for the error of weight
        expressionA = (*(tempSigPT+i)-*(tempActPT+i)) * (exp(*(tempSumPT+i))/pow((1+exp(*(tempSumPT+i))),2));
        //let the column pointer point at the first element of current row
        colPT = rowPT;
        for (int k=0; k<col; k++)
        {
            wErr[k]+=expressionA*(*colPT);
            ++colPT;
        }
        //move to next row
        ++rowPT;
    }
    return wErr;
}

//error calculation of bias
double biasErrFunc(double *sigPT, double *actPT) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT;
    tempSigPT = sigPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT;
    tempActPT = actPT;
    //variable for output of MAE per iteration
    double total=0;

    for (int i=0; i<trainRow; i++)
    {
        total += floatAbs(*(tempSigPT+i)-*(tempActPT+i));
    }
    return total/trainRow;
}

//absolute function for floating number
double floatAbs(double a)
{
    if (a<0)
    {
        return -a;
    }
    else
    {
        return a;
    }
}