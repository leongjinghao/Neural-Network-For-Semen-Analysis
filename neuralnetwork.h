#include "perceptron.h"
#include <time.h>

void neuralNetwork(double* inputTraining, int itr, FILE* outputFile, double *weightP1, double biasP1, double *weightP2, double biasP2, double *weightP3, double biasP3);
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, int itr, double *weightPT, double *bias, FILE *outputFile, int inputRow, int inputCol);

void neuralNetwork(double* inputTrainPT, int itr, FILE* outputFile, double *weightP1, double biasP1, double *weightP2, double biasP2, double *weightP3, double biasP3)
{
    //utilised for generating random float
    srand(time(NULL));
    double mae;
    
    //increase the counter of iteration at the begining of each iteration
    ++itr;
    printf("\nIteration #%d\n",itr);
    
    //**PERCEPTRON 1**
    
    //pointer to store y bar values (90 values) for each iteration for perceptron 1
    double *sumP1;
    double *yBarP1;
    //y bar, sigmoid values of perceptron 1, an array of 90 values
    sumP1 = perceptron(inputTrainPT,weightP1,biasP1,itr,trainRow,col);
    yBarP1 = sigmoid(sumP1,trainRow);

    mae = maeFunc(yBarP1,outputTrainPT,trainRow);
    //write mae result to output file
    outputMAE(outputFile,itr,mae);
    
/*
    //**PERCEPTRON 2**
    
    //pointer to store y bar values (90 values) for each iteration for perceptron 2
    double *sumP2;
    double *yBarP2;
    //y bar, sigmoid values of perceptron 2, an array of 90 values
    sumP2 = perceptron(inputTrainPT,weightP2,biasP2,itr,trainRow,col);
    yBarP2 = sigmoid(sumP2,trainRow);

    //**PERCEPTRON 3**
    
    //pointer to store y bar values (90 values) for each iteration for perceptron 3
    double *sumP3;
    double *yBarP3;
    static double inputP3[2*trainRow];
    //temp pointer used to merge yBarP1 and yBarP2
    double *mergeYBarP1P2;
    mergeYBarP1P2 = inputP3;
    //temp pointer for yBarP1 and yBarP2 to keep the original pointer unchange
    double *tempYBarP1;
    tempYBarP1 = yBarP1;
    double *tempYBarP2;
    tempYBarP2 = yBarP2;
    //merge both yBarP1 and yBarP2 into inputP3 array
    for(int i =0;i<trainRow;i++)
    {
        mergeYBarP1P2 = tempYBarP1;
        //printf("inputP3[%d]: %f\n", i, *mergeYBarP1P2);
        ++mergeYBarP1P2;
        ++tempYBarP1;
    }
    for(int i =0;i<trainRow;i++)
    {
        mergeYBarP1P2 = tempYBarP2;
        //printf("inputP3[%d]: %f\n", i+90, *mergeYBarP1P2);
        ++mergeYBarP1P2;
        ++tempYBarP2;
    }
    sumP3 = perceptron(inputP3,weightP3,biasP3,itr,2*trainRow,1);
    yBarP3 = sigmoid(sumP3,2*trainRow);
    //generate a single value for mae on the whole training data set
    mae = maeFunc(yBarP3,outputTrainPT,2*trainRow);
    //write mae result to output file
    outputMAE(outputFile,itr,mae);
*/

    //conduct training if mae did not reach targeted MAE
    if (mae>targetMAE)
    {
        //temp pointer for weightP3 to not change the original value of weightP3
        double *tempWeightP3;
        tempWeightP3 = weightP3;
        //variable for weight of P1 ybar value before and after
        //**P1 YBar Weight**
        double *yBarP1WeightBef;
        yBarP1WeightBef = tempWeightP3;
        double *yBarP1WeightAft;
        //**P2 YBar Weight**
        double *yBarP2WeightBef;
        yBarP2WeightBef = (tempWeightP3+1);
        double *yBarP2WeightAft;

        training(yBarP1,outputTrainPT,sumP1,inputTrainPT,itr,weightP1,&biasP1,outputFile,trainRow,col);


/*
        //conduct training on P3
        training(yBarP3,outputTrainPT,sumP3,inputP3,itr,weightP3,&biasP3,outputFile,1,2);
        //P1 and P2 YBar after training
        yBarP1WeightAft = tempWeightP3;
        yBarP2WeightAft = (tempWeightP3+1);

        //conduct training on P1 and P2, using the changes in weight as the reference for error
        training(yBarP1,outputTrainPT,sumP1,inputTrainPT,itr,weightP1,&biasP1,outputFile,trainRow,col);
        training(yBarP2,outputTrainPT,sumP2,inputTrainPT,itr,weightP2,&biasP2,outputFile,trainRow,col);
*/

        printf("MAE at iteration %d: %.10f\n",itr,mae);

        //move to next iteration
        neuralNetwork(inputTrainPT,itr,outputFile,weightP1,biasP1,weightP2,biasP2,weightP3,biasP3);
    }
    else
    {
        printf("Training completed!\nMAE met %f tolarance at %f at iteration %d\n",targetMAE,mae,itr);
    }
}


//training function, backwards propagate weight and bias
void training(double *sigPT, double *outputTrainPT, double *sumPT, double *inputTrainPT, int itr, double *weightPT, double *bias, FILE *outputFile, int inputRow, int inputCol)
{
    double *weightErrPT;
    double biasErr;

    printf("Training perceptron at iteration %d...\n",itr);
    weightErrPT=weightErrFunc(sigPT,outputTrainPT,sumPT,inputTrainPT,itr,inputRow,inputCol);
    
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
        //printf("Weight[%d] changed to: %f\n",i,*tempWeightPT);

        //move to next column for both tempWeightPT and tempWeightErrPT
        ++tempWeightPT;
        ++tempWeightErrPT;
    }

    //backwards propagate bias
    //calculate error of bias
    biasErr=biasErrFunc(sigPT,outputTrainPT,sumPT,itr,inputRow);
    *bias-=(biasErr*mu);

    //checking
    //printf("bias changed to: %f\n",*bias);
}