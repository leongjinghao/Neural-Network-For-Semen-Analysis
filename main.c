#include <stdlib.h>
#include <time.h>
#include "perceptron.h"

int main()
{
    srand(time(NULL));
    double *weightPT = weightGenerate();
    double bias = randFloat(-1.0,1.0);
    printf("bias: %f\n",bias);
    char filename[] = FILENAME;
    double **inputArrPT;

    //pointer to store the whole set of data (array)
    inputArrPT = inputData(filename);
    unpackage(inputArrPT);
    perceptron(inputTrainPT,weightPT,bias);
    //perceptron(inputTrainPT,weightPT,bias);
    
    return 0;
}
