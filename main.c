#include <stdlib.h>
#include <time.h>
#include "perceptron.h"
#include "gnuplotMAE.h"

int main()
{
    //time before program execution
    clock_t begin = clock();

    //at the begining of the program, iteration is at 0
    int itr = 1;
    double mae;
    double **percTrainReturn;
    double *sumPT;
    double *sigPT;
    double *sumTestPT;
    double *sigTestPT;

    //utilised for generating random float
    srand(time(NULL));
    //generate an array of random weight for each column of input
    //double weightPT[9] = {1,1,1,1,1,1,1,1,1};
    double *weightPT = weightGenerate();
    //generate a random bias
    //double bias = 1;
    double bias = randFloat(-1.0,1.0);
    //checking
    //printf("bias: %f\n",bias);

    //access the data set from file input
    char filename[] = FILENAME;
    //initialise pointer of pointers to store pointers of the different arrays we packaged in inputData function
    double **inputArrPT;
    inputArrPT = inputData(filename);

    //create a new file for mae output, if previous version exist, it will be replaced
    FILE *outputFile = fopen(FILEOUT, "w");
    fprintf(outputFile,"");
    //change fopen mode to append
    outputFile = fopen(FILEOUT, "a");

    //unpackage the packaged arrays in previous line
    unpackage(inputArrPT);

    //initialise perceptron for training input
    percTrainReturn = perceptron(inputTrainPT,weightPT,bias,itr,NULL,trainRow);

    sumPT = *percTrainReturn;
    sigPT = *(percTrainReturn+1);
    mae = **(percTrainReturn+2);
    
    //print mmse for training input before training
    printf("MMSE of training input before training: %.10lf\n",mmseFunc(sigPT,outputTrainPT,trainRow));

    //print mmse for testing input before training
    sumTestPT = lineReg(inputTestPT,weightPT,bias,testRow);
    sigTestPT = sigmoid(sumTestPT,testRow);
    printf("MMSE of testing input before training: %.10lf\n",mmseFunc(sigTestPT,outputTestPT,testRow));

    //backwards propagate weight and bias if mae did not reach tolerance value
    while (mae>targetMAE)
    //if (itr<2)
    {
        //train perceptron
        training(mae,sigPT,outputTrainPT,sumPT,inputTrainPT,itr,weightPT,&bias,outputFile);
        
        //move to next iteration
        itr++;
        percTrainReturn = perceptron(inputTrainPT,weightPT,bias,itr,outputFile,trainRow);

        sumPT = *percTrainReturn;
        sigPT = *(percTrainReturn+1);
        mae = **(percTrainReturn+2);
    }

    //printf("Training completed!\nMAE met %f tolarance at %.10f at iteration %d\n",targetMAE,mae,itr);

    //plot MAE
    //gnuplotMAE();

    printf("MMSE of training input after training: %.10lf\n",mmseFunc(sigPT,outputTrainPT,trainRow));

    //print mmse for testing input after training
    sumTestPT = lineReg(inputTestPT,weightPT,bias,testRow);
    sigTestPT = sigmoid(sumTestPT,testRow);
    printf("MMSE of testing input after training: %.10lf\n",mmseFunc(sigTestPT,outputTestPT,testRow));

    //time after program execution
    clock_t end = clock();
    //runtime
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Runtime: %.10lf\n", time_spent);
    printf("iteration: %d\n", itr);
    printf("mae: %.10lf\n", mae);

    return 0;
}
