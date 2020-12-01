#include<stdio.h>
#include <stdlib.h>

//global variables
double inputArray[100][10];//All data within 2D array
double inputTrain[90][9];//2D array for training data input
double inputTest[10][9];//2D array for training data output
double outputTrain[90];//1D array for testing data input
double outputTest[10];//1D array for testing data output

//function prototype
void inputData(char *filename);

//function for file access and return an array storing package of pointers
void inputData(char *filename)
{
    FILE *fertilitydata;
    fertilitydata = fopen(filename,"r"); //open file in read only

    if(fertilitydata==NULL) //if file is unable to be found
    {
        printf("Error while opening file!\n");
        exit(1);
    }
    else{//if file is found
        //printf("File found successfully!\n");

        //input data in array
        for(int i=0;i<(100);i++)
        {
            for(int j=0;j<10;j++)
            {
                fscanf(fertilitydata,"%lf%*c",&inputArray[i][j]);
                //printf("%f",inputArray[i][j]);
            }
        }
        fclose(fertilitydata);//close access to file

        //Splitting of data into 4 different sets
        for(int i=0;i<100;i++)
        {
            if(i<90)
            {
                for(int j=0;j<10;j++)
                {
                    if(j<9)
                    {
                        inputTrain[i][j]=inputArray[i][j];
                    }
                    else{
                        outputTrain[i]=inputArray[i][j];
                    }
                }
            }
            else
            {
                for(int j=0;j<10;j++)
                {
                    if(j<9)
                    {
                        //printf("Array %d: %.2f\n",i+1,inputArray[i][j]);
                        inputTest[i-90][j]=inputArray[i][j];
                    }
                    else
                    {
                        //printf("Array %d: %.2f\n",i+1,inputArray[i][j]);
                        outputTest[i-90]=inputArray[i][j];
                    }
                }
            }
        }
        
        /* checking
        printf("\nTraverse Input Training array:\n");
        traverseArray(90,9,inputTrain);
        printf("\nTraverse Output Training array:\n");
        traverseArray(90,1,outputTrain);
        printf("\nTraverse Input Test array:\n");
        traverseArray(10,9,inputTest);
        printf("\nTraverse Output Test array:\n");
        traverseArray(10,1,outputTest); */

    }
}