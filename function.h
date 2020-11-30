#include <math.h>
#include "def.h"
#include "input.h"

//function prototype
void lineReg(double *inputPT, double *weightPT, double bias, int row, int col, double *sum);
void sigmoid(double *sum, double *sig, int row);
double maeFunc(double *sigPT, double *actPT);
double mmseFunc(double *sigPT, double *actPT, int row);
void weightOErrFunc(double *input, double *sigPT, double *sumPT, int col, double *expAPT, double *wErrSumPT);
void weightHErrFunc(double expA, double weightO, double *sumHPT, int col, double *wHErrPT);
void biasHErrFunc(double expA, double weightO, double *sumHPT, double *biasHErr);

//linear regresion function, return pointer variable of sum (z)
void lineReg(double *inputPT, double *weightPT, double bias, int row, int col, double *sumPT)
{
    //pointer to traverse each row of input data, each row having n column of data, n=col
    //pointer of size double * col
    double (*inputRowPT)[col] = inputPT;
    //pointer to traverse each element of input data
    double *inputColPT;
    
    //pointer to traverse each column of weight data
    double *weightColPT = weightPT;

    double summation = 0;
    double *tempSumPT;
    tempSumPT = sumPT;

    for (int i=0; i<row; i++)
    {
        //let the column pointer point at the first element of current row
        inputColPT = *inputRowPT;
        //reset weight pointer to point at the first element on new loop
        weightColPT = weightPT;
        for (int k=0; k<col; k++)
        {
            summation+=(*inputColPT)*(*weightColPT);
            
            //checking
            //printf("EQ: %f x %f\n", (*inputColPT), (*weightColPT));
            
            //move to next column for both input and weight
            ++inputColPT;
            ++weightColPT;
        }
        summation+=bias;
        *tempSumPT = summation;
        //flush value for summation to calculate next row's sum
        summation = 0;
        
        //increment pointers to point at next element
        ++inputRowPT;
        ++tempSumPT;

        //checking
        //printf("Training row: %d\n", i+1);
        //printf("sum %d: %f\n",i+1, sum[i]);
        //printf("address: %d\n",&sum[i]);
    }
}

//sigmoid activation function using pointer of sum (z), return pointer variable sigPT
void sigmoid(double *sumPT, double *sigPT, int row)
{
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT;
    tempSumPT = sumPT;
    double *tempSigPT;
    tempSigPT = sigPT;

    for (int i=0; i<row ; i++)
    {
        //not using *tempSumPT+i because ++tempSumPT is faster
        *tempSigPT = 1/(1+exp(-*tempSumPT));

        //checking
        //printf("\nSigmoid function at row #%d:     sum = %f     addressSum = %d     sig = %f",i+1,*tempSumPT,tempSumPT,sig[i]);

        //move to next element
        ++tempSumPT;
        ++tempSigPT;
    }
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
        //printf("accumulated total %d: %lf += abs( %lf - %lf )\n", i, total, *tempSigPT, *tempActPT);

        //move to next row for SigPT and ActPT
        ++tempSigPT;
        ++tempActPT;
    }
    //checking
    //printf("total: %f / 90\n", total);
    return total/trainRow;
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
        total += pow(*tempSigPT-*tempActPT,2);
        
        //checking
        //printf("accumulated total: %lf += abs( %lf - %lf )\n", total, *tempSigPT, *tempActPT);

        //move to next row for SigPT and ActPT
        ++tempSigPT;
        ++tempActPT;
    }
    //checking
    //printf("total: %f / 90\n", total);
    return total/row;
}

//error calculation of weight
void weightOErrFunc(double *input, double *sigOPT, double *sumOPT, int col, double *expAPT, double *wOErrPT) 
{
    //utilise tempSigPT to keep sigPT address unchanged
    double *tempSigPT = sigOPT;
    //utilise tempActPT to keep actPT address unchanged
    double *tempActPT = outputTrain;
    //utilise tempSumPT to keep sumPT address unchanged
    double *tempSumPT = sumOPT;
    //variable for first part of the expression for the error of weight
    double expressionA;
    //row and column pointer to traverse the data (array) to retrieve each x (input)
    double (*rowPT)[col];
    rowPT = input;
    double *colPT;
    //array to store sum of weight error accumulated up until iteration I of each x (input)
    //flush all element to be 0 at the begining of each training
    double *tempWErr;
    *expAPT = 0;
    
    //for loop to calculate the accumulated weight error at iteration I before deviding by total row
    for (int i=0; i<trainRow; i++)
    {
        //first part of the expression for the error of weight, with respect to each row of data
        expressionA = (*tempSigPT-*tempActPT) * (exp(*tempSumPT)/pow(1+exp(*tempSumPT),2));
        //acumulate expAPT
        *expAPT += expressionA;
        //checking
        //printf("expression A at row %d: %lf\n", i+1, expressionA);

        //let the column pointer point at the first element of current row
        colPT = rowPT;
        tempWErr = wOErrPT;
        for (int k=0; k<col; k++)
        {
            //checking
            //printf("accumulated wErrSum[%d]: %f , ",k,wErrSum[k]);

            //to complete the whole expression multiply expressionA with the input (x) value, with respect to each row and each col of input (x)
            *tempWErr+=(expressionA*(*colPT));

            //checking
            //printf("wErrSum[%d]: accumulate + %f x %f = %f\n", k, expressionA, *colPT, expressionA*(*colPT));

            ++colPT;
            ++tempWErr;
        }

        //move to next row for inputTraining
        ++rowPT;
        //move to next row for SigPT, ActPT and SumPT
        ++tempSigPT;
        ++tempActPT;
        ++tempSumPT;
    }

    //divide by the number of times it was accumulated
    *expAPT/=trainRow;

    //for loop to calculate the weight error for the iteration at I after deviding by total rows
    //reuse colPT to traverse wErrSum array as pointer
    colPT = wOErrPT;
    for (int k=0; k<col; k++)
    {
        *colPT/=trainRow;

        //checking
        //printf("Error of Weight at [%d]: %f\n",k,wErrReturn[k]);

        //move to next column
        ++colPT;
    }
}

void weightHErrFunc(double expA, double weightO, double *sumHPT, int col, double *wHErrPT) 
{
    //utilise tempSumHPT to keep sumHPT address unchanged
    double *tempSumHPT = sumHPT;
    //utilise tempWHErrPT to keep wHErrPT address unchanged
    double *tempWHErrPT = wHErrPT;
    //row and column pointer to traverse the data (array) to retrieve each x (input)
    double (*rowPT)[col];
    rowPT = inputTrain;
    double *colPT;
    //array to store sum of weight error accumulated up until iteration I of each x (input)
    //flush all element to be 0 at the begining of each training
    double *tempWErr;
    
    //for loop to calculate the accumulated weight error at iteration I before deviding by total row
    for (int i=0; i<trainRow; i++)
    {
        //first part of the expression for the error of weight, with respect to each row of data
        //expressionA = (*tempSigPT-*tempActPT) * (exp(*tempSumPT)/pow(1+exp(*tempSumPT),2));

        //checking
        //printf("expression A at row %d: %lf\n", i+1, expressionA);

        //let the column pointer point at the first element of current row
        colPT = rowPT;
        tempWHErrPT = wHErrPT;
        for (int k=0; k<col; k++)
        {
            //checking
            //printf("accumulated wErrSum[%d]: %f , ",k,wErrSum[k]);

            //to complete the whole expression multiply expressionA with the input (x) value, with respect to each row and each col of input (x)
            *tempWHErrPT+=(expA*weightO*(exp(*tempSumHPT)/pow(1+exp(*tempSumHPT),2))*(*colPT));

            //checking
            //printf("wErrSum[%d]: accumulate + %f x %f = %f\n", k, expressionA, *colPT, expressionA*(*colPT));

            ++colPT;
        }

        //move to next row for inputTraining
        ++rowPT;
        //move to next row for SumHPT
        ++tempSumHPT;
    }

    //for loop to calculate the weight error for the iteration at I after deviding by total rows
    //reuse colPT to traverse wErrSum array as pointer
    colPT = wHErrPT;
    for (int k=0; k<col; k++)
    {
        *colPT/=trainRow;

        //checking
        //printf("Error of Weight at [%d]: %f\n",k,wErrReturn[k]);

        //move to next column
        ++colPT;
    }
}

//error calculation of bias hidden layer
void biasHErrFunc(double expA, double weightO, double *sumHPT, double *biasHErr) 
{
    //utilise tempSumHPT to keep sumHPT address unchanged
    double *tempSumHPT = sumHPT;
    //utilise tempWHErrPT to keep wHErrPT address unchanged
    double *tempBiasHErr = biasHErr;
    //variable to store sum of bias error accumulated up until iteration I
    //flush to be 0 at the beginning of each training
    *biasHErr = 0;

    for (int i=0; i<trainRow; i++)
    {
        *biasHErr += expA * weightO * (exp(*tempSumHPT)/pow(1+exp(*tempSumHPT),2));
        
        //printf("\n biasErrSum: %lf y cap: %lf , actual y: %lf , z: %lf", biasErrSum, *tempSigPT, *tempActPT, *tempSumPT);

        //move to next row for tempSumHPT
        ++tempSumHPT;
    }
    *biasHErr/=trainRow;
}