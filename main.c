#include<stdio.h>
#include<math.h>
#include"input.h"
#include"formula.h"
int main(){
    clock_t start=clock(),end;//time at start of program
    printf("Program start!\n");
    double timetaken;
    char plotfile[]="plot.txt";
    char outputfile[]="output.txt";
    FILE *plot,*output;
    plot = fopen(plotfile,"w");//file to store parameters to solve for
    output = fopen(outputfile,"w");
    
    srand(time(NULL));
    rngwb();//randomize w and b between -1 and 1
    inputData();//call function to read in data set input into array and traverse it
    int itrcount=1;

    //Training phase
    //printf("\nITERATION %d\n",itrcount);
    //First iteration start outside the loop to allow the MMSE before training and testing to be computed
    linearRegression(inputtrain,linearRegtrain,TRAIN);
    sigmoidActivation(linearRegtrain,sigmoidtrain,TRAIN);
    getmae(sigmoidtrain,outputtrain,TRAIN);
    getmmse(sigmoidtrain,outputtrain,TRAIN);
    fprintf(plot,"%d   %.10f\n",itrcount,mae);
    printf("MMSE before training: %10f\n",mmse);
    //printf("MAE before training: %10f\n",mae);
    fprintf(output,"MMSE before training: %10f\n",mmse);
    linearRegression(inputtest,linearRegtest,TEST);
    sigmoidActivation(linearRegtest,sigmoidtest,TEST);
    //getmae(sigmoidtest,outputtest,TEST);
    getmmse(sigmoidtest,outputtest,TEST);
    printf("MMSE before testing: %10f\n",mmse);
    fprintf(output,"MMSE before testing: %10f\n",mmse);
    feedback();
    while(mae>0.25){
        itrcount++;
        //printf("\nITERATION %d\n",itrcount);
        linearRegression(inputtrain,linearRegtrain,TRAIN);
        sigmoidActivation(linearRegtrain,sigmoidtrain,TRAIN);
        getmae(sigmoidtrain,outputtrain,TRAIN);
        fprintf(plot,"%d   %.10f\n",itrcount,mae);
        feedback();
    }
    getmmse(sigmoidtrain,outputtrain,TRAIN);
    printf("MMSE after training: %10f\n",mmse);
    fprintf(output,"MMSE after training: %10f\n",mmse);
    
    //check final weight and bias
    //printf("Final Weight:\n");
    //traverseArray(10,weight);
    //printf("Final Bias=%f\n",bias);
    fclose(plot);

    //Testing phase
    linearRegression(inputtest,linearRegtest,TEST);
    sigmoidActivation(linearRegtest,sigmoidtest,TEST);
    //getmae(sigmoidtest,outputtest,TEST);
    getmmse(sigmoidtest,outputtest,TEST);
    printf("MMSE after testing: %10f\n",mmse);
    fprintf(output,"MMSE after testing: %10f\n",mmse);
    printf("Iteration count: %d\n",itrcount);
    confusionMatrix();

    //Plot graph of linear regression (itr to mae)
    FILE * gnuplot = _popen ("gnuplot -p", "w");
    if(gnuplot==NULL){
        printf("404");
    }
    printf("Plotting Graph using GNUPlot......\n");
    fprintf(gnuplot,"set title 'Linear Regression Graph'\n");
    fprintf(gnuplot,"plot '%s' with lines\n",plotfile);
    fflush(gnuplot);
    fclose(plot);

    end=clock();//time at end of program
    timetaken=((double)(end-start))/CLOCKS_PER_SEC;//calculate time taken for program to run
    printf("Time Elapsed: %lf seconds\n",timetaken);
    return 0;
}