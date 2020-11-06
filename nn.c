#include <stdio.h>
#include <math.h>
#include "def.h"


double weight[col];
//double sum[row];
//double total;

double *line_reg(double [row][col], double [col]);
double *sigmoid(double *sum);
double mae(double guess, double actual, int itr);
double float_abs(double a);


int main()
{
    double input[row][col] = { {5,5,5} , {2,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {1,1,1} };
    double weight[col] = {1,-1,1};
    double bias = 1;
    double actual[row] = {1,1,0,1,0};
    double *sumPT;
    double *sigPT;
    double *tempPT;
    double sigArr[row];
    int itr = 0;

    sumPT = line_reg(input,weight);

    
    sigPT = sigmoid(sumPT);
    /*
    for (int i=0; i<row; i++)
    {
        tempPT=sigPT;
        printf("Sigmoid function for row #%d: %f\n", i+1, *tempPT);
        ++tempPT;
    }*/
    

    return 0;
}

//linear regresion function, return pointer variable of sum (z)
double *line_reg(double input[row][col], double weight[col])
{   
    double bias = 3.2;
    double total;
    static double sum[row];


    for (int i=0; i<row; i++)
    {
        
        for (int k=0; k<col; k++)
        {
            total+=(input[i][k]*weight[k]);
        }
        total+=bias;
        sum[i] = total;
        //flush value for sum to calculate next line's sum
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
    //DISCUSS IF WE NEED TO RETAIN ORIGINAL POINTER OF SUM AT sum[0]!!!!!!!!!
    double *tempSumPT;
    tempSumPT = sumPT;
    static double sig[row];

    for (int i=0; i<row ; i++)
    {
        //not using *tempSumPT+i because ++tempSumPT is faster
        sig[i] = 1/(1+exp(-*tempSumPT));
        ++tempSumPT;

        //checking
        printf("\nSigmoid function at row #%d: addressSum=%d sig=%f",i+1,tempSumPT,sig[i]);
    }
    return sig;
}

//mean abs error
double mae(double guess, double actual, int itr) 
{
    return float_abs(guess-actual)/itr;
}

//absolute function for floating number
double float_abs(double a)
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