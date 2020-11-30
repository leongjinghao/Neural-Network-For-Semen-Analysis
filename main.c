#include <stdlib.h>
#include <time.h>
#include "gnuplotMAE.h"
#include "neuralNetwork.h"

int main()
{
    //time before program execution
    clock_t begin = clock();

    //at the begining of the program, iteration is at 1
    int itr = 1;
    double mae;
    double sum[8][trainRow],sig[8][trainRow],sumTest[testRow],sigTest[testRow];
    double (*sumPT)[trainRow]=sum;
    double (*sigPT)[trainRow]=sig;
    double *sumOPT = sumPT+7;
    double *sigOPT = sigPT+7;
    double sigHidden[trainRow][7];
    double sigTestHidden[trainRow][7];
    double *sumTestPT=sumTest;
    double *sigTestPT=sigTest;
    int trainCMetrix[2][2]={{0,0},{0,0}};
    int testCMetrix[2][2]={{0,0},{0,0}};
    int correctPrediction;
    double accuracy;

    //utilised for generating random float
    srand(time(NULL));
    //generate random weight for 7 hidden layer perceptrons and 1 output layer perceptron
    double weightH[7][9]/*={{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1}}*/;
    double weightO[7]/*={1,1,1,1,1,1,1}*/;
    double (*weightHPT)[9] = weightH;
    double *weightOPT = weightO;
    for (int i=0;i<7;i++)
    {
        arrayGenerate(weightHPT,9);
        ++weightHPT;
    }
    arrayGenerate(weightOPT,9);
    

    //generate a random bias for 7 hidden layer perceptrons and 1 output layer perceptron
    double biasH[7]/*={1,1,1,1,1,1,1}*/;
    double *biasHPT = biasH;
    double biasO/*=1*/;
    
    arrayGenerate(biasH,7);
    biasO = randFloat(-1.0,1.0);
    

    //access the data set from file input
    char filename[] = FILENAME;
    //read in input data from filename
    inputData(filename);

    //create a new file for mae output, if previous version exist, it will be replaced
    FILE *outputFile = fopen(FILEOUT, "w");

    //initialise perceptron for training input
    //perceptron(inputTrain,weight,bias[0],itr,dataCol,&sumPT,&sigPT);
    mae = neuralNetwork(inputTrain,weightH,biasH,weightO,biasO,trainRow,itr,sum,sig,sigHidden,outputFile);
    //printf("mae: %f\n", mae);

    //print mmse for training and testing data before training
    //training input
    printf("\n-------------MMSE BEFORE TRAINING-------------\n");
    printf("MMSE of training input before training: %.10lf\n",mmseFunc(&sig[7][0],outputTrain,trainRow));
    //testing input
    neuralNetwork(inputTest,weightH,biasH,weightO,biasO,testRow,itr,sumTestPT,sigTestPT,sigTestHidden,NULL);
    printf("MMSE of testing input before training: %.10lf\n",mmseFunc(sigTestPT,outputTest,testRow));

    //backwards propagate weight and bias if mae did not reach tolerance value
    while (mae>targetMAE)
    //while (itr<5)
    {
        //printf("\n\n\n");
        //train perceptrons
        training(sigHidden,sigOPT,sumOPT,weightO,&biasO,weightH,biasH,sum,itr);
        
        for (int i=0; i<7; i++)
        {
            //printf("P8[%d]: %f\n",i,weightO[i]);
        }

        //move to next iteration
        itr++;
        
        //perceptron(inputTrain,weight,bias[0],itr,dataCol,&sumPT,&sigPT);
        mae = neuralNetwork(inputTrain,weightH,biasH,weightO,biasO,trainRow,itr,sum,sig,sigHidden,outputFile);
        //printf("mae: %f\n", mae);
    }

    //printf("Training completed!\nMAE met %f tolarance at %.10f at iteration %d\n",targetMAE,mae,itr);

    //plot MAE
    gnuplotMAE();

    //print mmse for training and testing data after training complete
    //training input
    printf("\n-------------MMSE AFTER TRAINING-------------\n");
    printf("MMSE of training input after training: %.10lf\n",mmseFunc(sigOPT,outputTrain,trainRow));
    //testing input
    neuralNetwork(inputTest,weightH,biasH,weightO,biasO,testRow,itr,sumTestPT,sigTestPT,sigTestHidden,NULL);
    printf("MMSE of testing input after training: %.10lf\n",mmseFunc(sigTestPT,outputTest,testRow));

    //confusion metrix
    //training set
    confusionMetrix(sigOPT,outputTrain,trainRow,trainCMetrix);
    printf("\nConfusion Metrix for training set:\n");
    printf("TN: %d      FP: %d\nFN: %d      TP: %d\n",trainCMetrix[0][0],trainCMetrix[0][1],trainCMetrix[1][0],trainCMetrix[1][1]);
    correctPrediction = trainCMetrix[0][0]+trainCMetrix[1][1];
    accuracy = (correctPrediction/(double)trainRow)*100.0;
    printf("Accuracy: %.2lf%%\n", accuracy);
    //testing set
    confusionMetrix(sigTestPT,outputTest,testRow,testCMetrix);
    printf("\nConfusion Metrix for testing set:\n");
    printf("TN: %d      FP: %d\nFN: %d      TP: %d\n",testCMetrix[0][0],testCMetrix[0][1],testCMetrix[1][0],testCMetrix[1][1]);
    correctPrediction = testCMetrix[0][0]+testCMetrix[1][1];
    accuracy = (correctPrediction/(double)testRow)*100.0;
    printf("Accuracy: %.2f%%\n", accuracy);

    //time after program execution
    clock_t end = clock();
    //runtime
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nRuntime: %.3lfsec\n", time_spent);
    printf("iteration: %d\n", itr);
    printf("mae: %.10lf\n", mae);

    return 0;
}
