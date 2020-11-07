#include<stdio.h>

double *inputData(char *filename);
int traverseArray(int m,int n,double array[m][n]);

//function for file access and return an array storing package of pointers
double *inputData(char *filename)
{
    static double inputArray[100][10];//All data within 2D array
    static double inputTrain[90][9];//2D array for training data input
    static double inputTest[10][9];//2D array for training data output
    static double outputTrain[90][1];//2D array for testing data input
    static double outputTest[10][1];//2D array for testing data output
    static double *returnArr[5];
    FILE *fertilitydata;
    fertilitydata = fopen(filename,"r"); //open file in read only

    if(fertilitydata==NULL) //if file is unable to be found
    {
        printf("Error while opening file!\n");
    }
    else{//if file is found
        printf("File found successfully!\n");

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
                        outputTrain[i][0]=inputArray[i][j];
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
                        outputTest[i-90][0]=inputArray[i][j];
                    }
                }
            }
        }

        //packaging all the array as a pointer into a single array for return
        returnArr[0] = *inputArray;
        returnArr[1] = *inputTrain;
        returnArr[2] = *inputTest;
        returnArr[3] = *outputTrain;
        returnArr[4] = *outputTest;
        
        printf("[0]: %f\n", *returnArr[0]);
        printf("[1]: %f\n", *returnArr[1]);
        printf("[2]: %f\n", *returnArr[2]);
        printf("[3]: %f\n", *returnArr[3]);
        printf("[4]: %f\n", *returnArr[4]);

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
    return returnArr;
}

//function for printing each element of 2D array, row by column
int traverseArray(int m,int n,double array[m][n])
{
    for(int i=0;i<m;i++)
    {
            printf("Array %d: ",i+1);
            for(int j=0;j<n;j++)
            {
                printf("%.2f ",array[i][j]);
            }
            printf("\n");
        }
    return 0;
}