#include<stdio.h>
#include"input.h"
int main(){
    int numoftrain=50, numoftest=50;//In future can read in user input :D
    char filename[]="fertility_Diagnosis_Data_Group9_13.txt";
    inputData(numoftrain,numoftest,filename);//call function to read in data set input into array and traverse it
    return 0;
}