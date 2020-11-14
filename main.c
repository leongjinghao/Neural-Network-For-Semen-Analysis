#include<stdio.h>
#include<math.h>
#include"input.h"
#include"formula.h"
int main(){
    char outputfile[]="mother die.txt";
    FILE *output;
    output = fopen(outputfile,"w");
    char filename[]="fertility_Diagnosis_Data_Group9_13.txt";
    srand(time(NULL));
    rngwb();
    inputData(filename);//call function to read in data set input into array and traverse it
    while(mae>0.25){
        mae=feedforward(inputtrain,weight,bias,output);
        feedback();
    }
    fclose(output);

    //PLOT BABY
    FILE * gnuplot = _popen ("gnuplot -p", "w");
    if(gnuplot==NULL){
        printf("404");
    }
    printf("ALLAHU ACKBAR");
    fflush(gnuplot);
    fprintf(gnuplot,"set title 'gay'\n");
    fprintf(gnuplot,"plot '%s'\n",outputfile);
    fclose(output);

    return 0;
}