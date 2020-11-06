#include <stdio.h>
#include <math.h>
#define row 5
#define col 3

double weight [col];
void line_reg(double [row][col], double [col], double sum[row]);
double sigmoid(double sum);
double mae(double guess, double actual, int itr);
double float_abs(double a);


int main()
{
    double input[row][col] = { {1,1,1} , {2,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {5,5,5}};
    double weight[col] = {1,-1,1};
    double actual[row] = {1,1,0,1,0};
    double sum[row];
    double sigout;
    int itr=0;
    line_reg(input,weight);
    printf("\nSummation: %f", sum);
    sigout = sigmoid(sum);
    printf("\nGuess: %f", sigout);
    printf("\nabs: %f", float_abs(-0.1));
    printf("\nabs: %f", float_abs(-0.01));
}

//linear regresion function
void line_reg(double input[row][col], double weight[col], double sum[row])
{   
    double bias = 3.2;
    for (int i=0; i<row; i++)
    {
        double total = 0;
        for (int k=0; k<col; k++)
        {
            total+=(input[i][k]*weight[k]);
        }
        sum[i] = total;
    }
}

//sigmoid activation function
double sigmoid(double sum)
{
    return 1/(1+pow(M_E,-sum));
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