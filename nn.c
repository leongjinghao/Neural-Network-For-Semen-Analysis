#include <stdio.h>
#include <math.h>
#include "def.h"


double weight[col];
double sum[row];

double *line_reg(double [row][col], double [col]);
double *sigmoid(double *sum);
double mae(double guess, double actual, int itr);
double float_abs(double a);


int main()
{
    double input[row][col] = { {1,1,1} , {2,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {5,5,5}};
    double weight[col] = {1,-1,1};
    double bias = 1;
    double actual[row] = {1,1,0,1,0};
    double *sumPT;
    double *sigPT;
    double *tempPT;
    double sigArr[row];
    int itr=0;

    sumPT = line_reg(input,weight);
    printf("\nSummation: %f", *sumPT);
    
    sigPT = sigmoid(sum);
    for (int i=0; i<row; i++)
    {
        tempPT=sigPT;
        printf("Sigmoid function for row #%d: %f\n", i+1, *tempPT);
        ++tempPT;
    }
    
}

//linear regresion function, storing sum of i in pointer
double *line_reg(double input[row][col], double weight[col])
{   
    double bias = 3.2;
    double *sumPT;
    double total = 0;
    sumPT = &total;

    for (int i=0; i<row; i++)
    {
        
        for (int k=0; k<col; k++)
        {
            total+=(input[i][k]*weight[k]);
        }
        total+=bias;
        *sumPT = total;
        printf("sum: %f\n",*sumPT);
        printf("address: %d\n",&sumPT);
        //flush value for sum to calculate next line's sum
        //total = 0;
        ++sumPT;

    }
    return (sumPT-row);
}

//sigmoid activation function using pointer of sum (z)
double *sigmoid(double *sum)
{
    double *tempPT;
    double *sigPT = tempPT;
    for (int i=0; i<row ; i++)
    {
        *tempPT = 1/(1+exp(-*sum));
        ++sum;
        ++tempPT;
    }
    return sigPT;
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