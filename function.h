#include <stdio.h>
#include <math.h>
#include "def.h"

double weight[col];

double *lineReg(double *inputPT, double *weightPT);
double *sigmoid(double *sum);
double maeFunc(double *sigPT, double *actPT, int itr);
double floatAbs(double a);

//linear regresion function, return pointer variable of sum (z)
double *lineReg(double *inputPT, double *weightPT)
{
    //pointer to traverse each row of input data, each row having n column of data, n=col
    double (*inputRowPT)[col];
    inputRowPT = inputPT;
    //pointer to traverse each element of input data
    double *inputColPT;
    
    //pointer to traverse each column of weight data
    double *weightColPT;
    weightColPT = weightPT;

    double bias = 0;
    double summation;
    //array to store summation (z) for each row, static to make sure the array remain exist after function call
    static double sum[row];


    for (int i=0; i<row; i++)
    {
        //let the column pointer point at the first element of current row
        inputColPT = *inputRowPT;
        for (int k=0; k<col; k++)
        {
            summation+=((*inputColPT)*(*weightColPT));
            
            //checking
            printf("\nEQ: %f x %f\n", (*inputColPT), (*weightColPT));
            
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

        //checking
        printf("row: %d\n", i+1);
        printf("sum: %f\n", sum[i]);
        printf("address: %d\n",&sum[i]);
    }
    
    return sum;
}

//sigmoid activation function using pointer of sum (z), return pointer variable sigPT
double *sigmoid(double *sumPT)
{
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT = sumPT;
    //array to store y bar (sigmoid function output), static to make sure the array remain exist after function call
    static double sig[row];

    for (int i=0; i<row ; i++)
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
double maeFunc(double *sigPT, double *actPT, int itr) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT;
    tempSigPT = sigPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT;
    tempActPT = actPT;
    //variable for output of MAE per iteration
    double mae=0;

    for (int i=0; i<row; i++)
    {
        mae += floatAbs(*(tempSigPT+i)-*(tempActPT+i))/itr;
    }
    return mae;
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