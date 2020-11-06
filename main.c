#include<stdio.h>
#include<math.h>
#include"input.h"
#include"formula.h"
int main(){
    char filename[]="fertility_Diagnosis_Data_Group9_13.txt";
    inputData(filename);//call function to read in data set input into array and traverse it
    
    //call functions here
    float *z;
    z = linearRegression(90,inputtrain);
    //float sigmoid=sigmoidFunction(z);

    return 0;
}