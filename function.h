#include <stdio.h>
#include <math.h>
#include "def.h"


double weight[col];
//double sum[row];
//double total;

double *lineReg(double [row][col], double [col]);
double *sigmoid(double *sum);
double maeFunc(double *sigPT, double *actPT, int itr);
double floatAbs(double a);

//linear regresion function, return pointer variable of sum (z)
double *lineReg(double input[row][col], double weight[col])
{
    double bias = 3.2;
    double total;
    //array to store sum (z) for each row, static to make sure the array remain exist after function call
    static double sum[row];


    for (int i=0; i<row; i++)
    {
        
        for (int k=0; k<col; k++)
        {
            total+=(input[i][k]*weight[k]);
        }
        total+=bias;
        sum[i] = total;
        //flush value for total to calculate next row's sum
        total = 0;

        //checking
        printf("sum: %f\n", sum[i]);
        printf("address: %d\n",&sum[i]);
    }
    return sum;
}

//sigmoid activation function using pointer of sum (z), return pointer variable sigPT
double *sigmoid(double *sumPT)
{
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT;
    tempSumPT = sumPT;
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