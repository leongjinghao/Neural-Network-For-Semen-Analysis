#include <stdlib.h>
#include <time.h>
#include "neuralnetwork.h"

int main()
{
    //at the begining of the program, iteration is at 0
    int itr = 0;
    //utilised for generating random float
    srand(time(NULL));

    //create a new file for mae output, if previous version exist, it will be replaced
    FILE *outputFile = fopen(FILEOUT, "w");
    fprintf(outputFile,"");
    //change fopen mode to append
    outputFile = fopen(FILEOUT, "a");
    
    //access the data set from file input
    char filename[] = FILENAME;
    //initialise pointer of pointers to store pointers of the different arrays we packaged in inputData function
    double **inputArrPT;
    inputArrPT = inputData(filename);

    //unpackage the packaged arrays in previous line
    unpackage(inputArrPT);

    //**Perceptron 1**
    //generate an array of random weight for each column of input for perceptron 1
    static double *weightP1;
    weightP1 = weightGenerate(col);
    //generate a random bias for perceptron 1
    static double biasP1;
    biasP1 = randFloat(-1.0,1.0);

    //**Perceptron 2**
    //generate an array of random weight for each column of input for perceptron 2
    static double *weightP2;
    weightP2 = weightGenerate(col);
    //generate a random bias for perceptron 2
    static double biasP2;
    biasP2 = randFloat(-1.0,1.0);

    //**Final Perceptron**
    //generate an array of random weight for each perceptron output in hidden layer
    static double *weightPF;
    weightPF = weightGenerate(2);
    //generate a random bias for final perceptron
    static double biasPF;
    biasPF = randFloat(-1.0,1.0);

    neuralNetwork(inputTrainPT,itr,outputFile,weightP1,biasP1,weightP2,biasP2,weightPF,biasPF);
    
    return 0;
}
