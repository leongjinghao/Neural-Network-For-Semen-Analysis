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
    int trainCMetrix[2][2]={{0,0},{0,0}};
    int testCMetrix[2][2]={{0,0},{0,0}};
    int correctPrediction;
    double accuracy;

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
    //read in input data from filename
    inputData(filename);

    //create a new file for mae output, if previous version exist, it will be replaced
    FILE *outputFile = fopen(FILEOUT, "w");

    //initialise perceptron for training input
    percTrainReturn = perceptron(weightPT,bias,itr,outputFile,trainRow);

    sumPT = *percTrainReturn;
    sigPT = *(++percTrainReturn);
    mae = **(++percTrainReturn);
    
    //print mmse for training input before training
    printf("MMSE of training input before training: %.10lf\n",mmseFunc(sigPT,outputTrain,trainRow));

    //print mmse for testing input before training
    sumTestPT = lineReg(inputTest,weightPT,bias,testRow);
    sigTestPT = sigmoid(sumTestPT,testRow);
    printf("MMSE of testing input before training: %.10lf\n",mmseFunc(sigTestPT,outputTest,testRow));

    //backwards propagate weight and bias if mae did not reach tolerance value
    while (mae>targetMAE)
    //while (0)
    {
        //train perceptron
        training(mae,sigPT,sumPT,itr,weightPT,&bias,outputFile);
        
        //move to next iteration
        itr++;
        percTrainReturn = perceptron(weightPT,bias,itr,outputFile,trainRow);

        sumPT = *percTrainReturn;
        sigPT = *(percTrainReturn+1);
        mae = **(percTrainReturn+2);
    }

    //printf("Training completed!\nMAE met %f tolarance at %.10f at iteration %d\n",targetMAE,mae,itr);

    //plot MAE
    gnuplotMAE();

    printf("MMSE of training input after training: %.10lf\n",mmseFunc(sigPT,outputTrain,trainRow));

    //print mmse for testing input after training
    sumTestPT = lineReg(inputTest,weightPT,bias,testRow);
    sigTestPT = sigmoid(sumTestPT,testRow);
    printf("MMSE of testing input after training: %.10lf\n",mmseFunc(sigTestPT,outputTest,testRow));

    //confusion metrix
    //training set
    confusionMetrix(sigPT,outputTrain,trainRow,trainCMetrix);
    printf("Confusion Metrix for training set:\n");
    printf("TP: %d  FP: %d  TN: %d  FN: %d\n",trainCMetrix[1][1],trainCMetrix[0][1],trainCMetrix[0][0],trainCMetrix[1][0]);
    correctPrediction = trainCMetrix[0][0]+trainCMetrix[1][1];
    accuracy = (correctPrediction/(double)trainRow)*100.0;
    printf("Accuracy: %.2lf%%\n",accuracy);
    //testing set
    confusionMetrix(sigTestPT,outputTest,testRow,testCMetrix);
    printf("Confusion Metrix for testing set:\n");
    printf("TP: %d  FP: %d  TN: %d  FN: %d\n",testCMetrix[1][1],testCMetrix[0][1],testCMetrix[0][0],testCMetrix[1][0]);
    correctPrediction = testCMetrix[0][0]+testCMetrix[1][1];
    accuracy = (correctPrediction/(double)testRow)*100.0;
    printf("Accuracy: %.2f%%\n",accuracy);

    //time after program execution
    clock_t end = clock();
    //runtime
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time Elapsed: %.3lfsec\n", time_spent);
    printf("iteration: %d\n", itr);
    printf("mae: %.10lf\n", mae);

    return 0;
}
