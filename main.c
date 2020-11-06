#include <stdio.h>
#include "def.h"
#include "function.h"

int main()
{
    double input[row][col] = { {5,5,5} , {2,2,2} , {3.3,3.3,3.3} , {4.4,4.4,4.4} , {1,1,1} };
    double weight[col] = {1,-1,1};
    double actual[row] = {1,1,0,-1,0};
    double *sumPT;
    double *sigPT;
    double mae = 0;
    int itr = iteration;

    sumPT = lineReg(input,weight);
    sigPT = sigmoid(sumPT);
    mae = maeFunc(sigPT,actual,itr);
    printf("\nMAE: %f", mae);

    return 0;
}