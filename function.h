#include <math.h>
#include "def.h"

//function prototype
double *lineReg(double *inputPT, double *weightPT, double bias, int row);
double *sigmoid(double *sum, int row);
double maeFunc(double *sigPT, double *actPT);
double mmseFunc(double *sigPT, double *actPT, int row);
double *weightErrFunc(double *sigPT, double *actPT, double *sumPT, double *inputTrainPT, int itr);

//linear regresion function, return pointer variable of sum (z)
double *lineReg(double *inputPT, double *weightPT, double bias, int row)
{
    //pointer to traverse each row of input data, each row having n column of data, n=col
    //pointer of size double * col
    double (*inputRowPT)[col];
    inputRowPT = inputPT;
    //pointer to traverse each element of input data
    double *inputColPT;
    
    //pointer to traverse each column of weight data
    double *weightColPT;
    weightColPT = weightPT;

    double summation = 0;
    //array to store summation (z) for each row, static to make sure the array remain exist after function call
    static double sum[trainRow];

    for (int i=0; i<row; i++)
    {
        //let the column pointer point at the first element of current row
        inputColPT = *inputRowPT;
        for (int k=0; k<col; k++)
        {
            summation+=((*inputColPT)*(*weightColPT));
            
            //checking
            //printf("EQ: %f x %f\n", (*inputColPT), (*weightColPT));
            
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
        //printf("Training row: %d\n", i+1);
        //printf("sum %d: %f\n",i+1, sum[i]);
        //printf("address: %d\n",&sum[i]);
    }
    return sum;
}

//sigmoid activation function using pointer of sum (z), return pointer variable sigPT
double *sigmoid(double *sumPT, int row)
{
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT = sumPT;
    //array to store y bar (sigmoid function output), static to make sure the array remain exist after function call
    static double sig[trainRow];

    for (int i=0; i<row ; i++)
    {
        //not using *tempSumPT+i because ++tempSumPT is faster
        sig[i] = 1/(1+exp(-*tempSumPT));

        //checking
        //printf("\nSigmoid function at row #%d:     sum = %f     addressSum = %d     sig = %f",i+1,*tempSumPT,tempSumPT,sig[i]);

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
        total += fabs(*tempSigPT-*tempActPT);
        
        //checking
        //printf("accumulated total: %lf += abs( %lf - %lf )\n", total, *tempSigPT, *tempActPT);

        //move to next row for SigPT and ActPT
        ++tempSigPT;
        ++tempActPT;
    }
    //checking
    //printf("total: %f / 90\n", total);
    return (total/trainRow);
}

//mmse
double mmseFunc(double *sigPT, double *actPT, int row) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT;
    tempSigPT = sigPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT;
    tempActPT = actPT;
    //variable for output of MAE per iteration
    double total=0;

    for (int i=0; i<row; i++)
    {
        total += pow((*tempSigPT-*tempActPT),2);
        
        //checking
        //printf("accumulated total: %lf += abs( %lf - %lf )\n", total, *tempSigPT, *tempActPT);

        //move to next row for SigPT and ActPT
        ++tempSigPT;
        ++tempActPT;
    }
    //checking
    //printf("total: %f / 90\n", total);
    return (total/row);
}

//error calculation of weight
double *weightErrFunc(double *sigPT, double *actPT, double *sumPT, double *inputTrainPT, int itr) 
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
    //array to store sum of weight error accumulated up until iteration I of each x (input)
    //static array to ensure values from previous iteration is retained
    //initialise all element to be 0 once on first iteration
    static double wErrSum[col];
    memset(wErrSum,0.0,sizeof wErrSum); 
    //array to store the weight error for the interation at I, wErrSum / iteration
    //static array to ensure the array remain exsist after function call
    //initialise all element to be 0 once on first iteration
    static double wErrReturn[col];
    memset(wErrReturn,0.0,sizeof wErrReturn); 
    
    //for loop to calculate the accumulated weight error at iteration I
    for (int i=0; i<trainRow; i++)
    {
        //first part of the expression for the error of weight, with respect to each row of data
        expressionA = (*tempSigPT-*tempActPT) * (exp(*tempSumPT)/pow((1+exp(*tempSumPT)),2));

        //checking
        //printf("expression A at row %d: %lf\n", i+1, expressionA);

        //let the column pointer point at the first element of current row
        colPT = rowPT;

        for (int k=0; k<col; k++)
        {
            //checking
            //printf("accumulated wErrSum[%d]: %f , ",k,wErrSum[k]);

            //to complete the whole expression multiply expressionA with the input (x) value, with respect to each row and each col of input (x)
            wErrSum[k]+=(expressionA*(*colPT));

            //checking
            //printf("wErrSum[%d]: accumulate + %f x %f = %f\n", k, expressionA, *colPT, expressionA*(*colPT));

            ++colPT;
        }

        //move to next row
        ++rowPT;
        //move to next row for SigPT, ActPT and SumPT
        ++tempSigPT;
        ++tempActPT;
        ++tempSumPT;
    }

    //for loop to calculate the weight error for the iteration at I
    //reuse colPT to traverse wErrSum array as pointer
    colPT = wErrSum;
    for (int k=0; k<col; k++)
    {
        wErrReturn[k] = (*colPT)/trainRow;

        //checking
        //printf("Error of Weight at [%d]: %f\n",k,wErrReturn[k]);

        //move to next column
        ++colPT;
    }
    return wErrReturn;
}

//error calculation of bias
double biasErrFunc(double *sigPT, double *actPT, double *sumPT, int inputRow) 
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
    //variable to store sum of bias error accumulated up until iteration I
    //static variable to ensure values from previous iteration is retained
    //initialise variable to be 0 once on first iteration
    static double biasErrSum;
    biasErrSum = 0;

    for (int i=0; i<trainRow; i++)
    {
        biasErrSum += (*tempSigPT-*tempActPT) * (exp(*tempSumPT)/pow((1+exp(*tempSumPT)),2));
        
        //printf("\n biasErrSum: %lf y cap: %lf , actual y: %lf , z: %lf", biasErrSum, *tempSigPT, *tempActPT, *tempSumPT);

        //move to next row for SigPT, ActPT and SumPT
        ++tempSigPT;
        ++tempActPT;
        ++tempSumPT;
    }
    return biasErrSum/trainRow;
}