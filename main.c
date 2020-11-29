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
    char filename[]="fertility_Diagnosis_Data_Group9_13.txt";
    srand(time(NULL));
    //rngwb();//randomize w and b between -1 and 1
    inputData(filename);//call function to read in data set input into array and traverse it

    //Training phase
    while(mae>0.25){
        mae=feedforward(inputtrain,weight,bias,plot,output);
        feedback();
    }
    //check final weight and bias
    //printf("Final Weight:\n");
    //traverseArray(10,weight);
    //printf("Final Bias=%f\n",bias);
    fclose(plot);

    //Testing phase
    //mae=feedforward(inputtest,weight,bias,plot,output);//this is wrong, adjustments must be made, use diff function for test/train

    //Plot graph of linear regression (itr to mae)
    FILE * gnuplot = _popen ("gnuplot -p", "w");
    if(gnuplot==NULL){
        printf("404");
    }
    printf("Plotting Graph using GNUPlot......\n");
    fprintf(gnuplot,"set title 'Linear Regression Graph'\n");
    fprintf(gnuplot,"plot '%s'\n",plotfile);
    fflush(gnuplot);
    fclose(plot);
    end=clock();//time at end of program
    timetaken=((double)(end-start))/CLOCKS_PER_SEC;//calculate time taken for program to run
    printf("Time Elapsed: %lf seconds\n",timetaken);

    return 0;
}