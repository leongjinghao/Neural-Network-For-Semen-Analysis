#include "perceptron.h"
#include <time.h>

void neuralNetwork(double* inputTraining, int itr, FILE* outputFile, double *weightP1, double biasP1, double *weightP2, double biasP2, double *weightPF, double biasPF);
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, double *weightPT, double *bias, FILE *outputFile, int inputRow, int inputCol);

void neuralNetwork(double* inputTrainPT, int itr, FILE* outputFile, double *weightP1, double biasP1, double *weightP2, double biasP2, double *weightPF, double biasPF)
{
    double mae;
    
    //increase the counter of iteration at the begining of each iteration
    ++itr;
    printf("\nIteration #%d\n",itr);
    
    //**PERCEPTRON 1**
    //pointer to store y bar values (90 values) for each iteration for perceptron 1
    double *sumP1;
    double *yBarP1;
    //y bar, sigmoid values of perceptron 1, an array of 90 values
    sumP1 = perceptron(inputTrainPT,weightP1,biasP1,trainRow,col);
    yBarP1 = sigmoid(sumP1,trainRow);

    /*mae = maeFunc(yBarP1,outputTrainPT,trainRow);
    //write mae result to output file
    outputMAE(outputFile,itr,mae);*/
    
    //**PERCEPTRON 2**
    //pointer to store y bar values (90 values) for each iteration for perceptron 2
    double *sumP2;
    double *yBarP2;
    //y bar, sigmoid values of perceptron 2, an array of 90 values
    sumP2 = perceptron(inputTrainPT,weightP2,biasP2,trainRow,col);
    yBarP2 = sigmoid(sumP2,trainRow);

    //**Final PERCEPTRON**
    //pointer to store y bar values (90 values) for each iteration for final perceptron
    double *sumPF;
    double *yBarPF;
    static double inputPF[2*trainRow];
    //temp pointer used to merge all yBar (input for final perceptron) on hidden layer
    double *mergeHiddenYBar;
    mergeHiddenYBar = inputPF;
    //temp pointer for all yBar on hidden layer to keep the original pointer unchange
    double *tempYBarP1;
    tempYBarP1 = yBarP1;
    double *tempYBarP2;
    tempYBarP2 = yBarP2;
    //merge both yBarP1 and yBarP2 into inputP3 array, inputP3 is a 2D array with row=trainRow col=2
    for(int i =0;i<(2*trainRow);i++)
    {
        //add in YbarP1
        mergeHiddenYBar = tempYBarP1;
        ++mergeHiddenYBar;
        //add in YbarP2
        mergeHiddenYBar = tempYBarP2;
        ++mergeHiddenYBar;
        
        ++tempYBarP1;
        ++tempYBarP2;
    }

    //linear regression for 90 rows of all perceptrons on hidden layer
    sumPF = perceptron(inputPF,weightPF,biasPF,trainRow,2);
    yBarPF = sigmoid(sumPF,trainRow);
    //generate a single value for mae on the whole training data set
    mae = maeFunc(yBarPF,outputTrainPT,trainRow);
    //write mae result to output file
    outputMAE(outputFile,itr,mae);


    //conduct training if mae did not reach targeted MAE
    if (mae>targetMAE)
    {
        double yBarP1WeightBef[1];
        double yBarP2WeightBef[1];
        double yBarP3WeightBef[1];
        double *yBarP1WeightAft;
        double *yBarP2WeightAft;
        double *yBarP3WeightAft;
        yBarP1WeightBef[0] = *weightPF;
        yBarP2WeightBef[0] = *(weightPF+1);
        yBarP3WeightBef[0] = *(weightPF+2);

        //training(yBarP1,outputTrainPT,sumP1,inputTrainPT,itr,weightP1,&biasP1,outputFile,trainRow,col);

        //conduct training on final perceptron
        training(yBarPF,outputTrainPT,sumPF,inputPF,weightPF,&biasPF,outputFile,trainRow,3);
        yBarP1WeightAft = weightPF;
        yBarP2WeightAft = (weightPF + 1);
        
        //conduct training on P1 and P2, using the changes in weight as the reference for error
        //assumption: error calculation is by referencing changes in weight, yBarP1 and yBarP2 each has a single weight pass to P3, therefore (1 x 1)
        printf("Training perceptron at iteration %d...\n",itr);
        //training(yBarP1WeightBef,yBarP1WeightAft,sumP1,inputTrainPT,itr,weightP1,&biasP1,outputFile,1,1);
        //training(yBarP2WeightBef,yBarP2WeightAft,sumP2,inputTrainPT,itr,weightP2,&biasP2,outputFile,1,1);
        training(yBarP1,outputTrainPT,sumP1,inputTrainPT,weightP1,&biasP1,outputFile,trainRow,col);
        training(yBarP2,outputTrainPT,sumP2,inputTrainPT,weightP2,&biasP2,outputFile,trainRow,col);


        printf("MAE at iteration %d: %.10f\n",itr,mae);

        //move to next iteration
        neuralNetwork(inputTrainPT,itr,outputFile,weightP1,biasP1,weightP2,biasP2,weightPF,biasPF);
    }
    else
    {
        printf("Training completed!\nMAE met %f tolarance at %f at iteration %d\n",targetMAE,mae,itr);
    }
}


//training function, backwards propagate weight and bias
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, double *weightPT, double *bias, FILE *outputFile, int inputRow, int inputCol)
{
    double *weightErrPT;
    double biasErr;

    weightErrPT=weightErrFunc(sigPT,outputTrainPT,sumPT,inputTrainPT,inputRow,inputCol);
    
    //pointer to the weight array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight pointer while traversing
    double *tempWeightPT;
    tempWeightPT = weightPT;
    //pointer to the weight error array, will be used to change the value of the weight directly
    //temporary pointer is used to maintain original pointed address of the weight error pointer while traversing
    double *tempWeightErrPT;
    tempWeightErrPT = weightErrPT;

    //backwards propagate weight
    //change the value of weight base on the error fomula
    for (int i=0; i<col; i++)
    {
        *tempWeightPT-=((*tempWeightErrPT)*mu);
        
        //checking
        printf("Weight[%d] changed to: %f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightPT;
        ++tempWeightErrPT;
    }

    //backwards propagate bias
    //calculate error of bias
    biasErr=biasErrFunc(sigPT,outputTrainPT,sumPT,inputRow);
    *bias-=(biasErr*mu);

    //checking
    printf("bias changed to: %f\n",*bias);
}