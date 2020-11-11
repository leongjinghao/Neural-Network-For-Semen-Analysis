#include <stdlib.h>
#include <time.h>
#include "perceptron.h"

int main()
{
    //at the begining of the program, iteration is at 0
    int itr = 0;

    //flush all data inside outputFile
    FILE *outputFile = fopen("mae_Output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Output file does not exist!\n");
        exit(-1);
    }
    fprintf(outputFile,"");
    outputFile = fopen("mae_Output.txt", "a");
    

    //utilised for generating random float
    srand(time(NULL));
    //generate an array of random weight for each column of input
    double *weightPT = weightGenerate();
    //generate a random bias
    double bias = randFloat(-1.0,1.0);
    //checking
    printf("bias: %f\n",bias);

    //access the data set from file input
    char filename[] = FILENAME;
    //initialise pointer of pointers to store pointers of the different arrays we packaged in inputData function
    double **inputArrPT;
    inputArrPT = inputData(filename);

    //unpackage the packaged arrays in previous line
    unpackage(inputArrPT);

    //initialise perceptron and train the perceptron accordingly
    perceptron(inputTrainPT,weightPT,bias,itr,outputFile);
    
    return 0;
}
