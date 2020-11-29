#include<stdio.h>
//global declaration
float inputarray[100][10];//All data within 2D array
float inputtrain[90][9];//2D array for training data input
float inputtest[10][9];//2D array for training data output
float outputtrain[90];//1D array for testing data input
float outputtest[10];//1D array for testing data output
//function prototype
int inputData(char *filename);
void traverseArray(int m,float array[m]);
void traverse2DArray(int m,int n,float array[m][n]);
//function 
int inputData(char *filename){
    FILE *fertilitydata;
    if(fertilitydata==NULL){//if file is unable to be found
        printf("Error while opening file!\n");
    }

    fertilitydata = fopen(filename,"r");//open file in read only
    //input data in array
    for(int i=0;i<(100);i++){
        for(int j=0;j<10;j++){
            fscanf(fertilitydata,"%f%*c",&inputarray[i][j]);
            //printf("%f",inputarray[i][j]);
        }
    }
    fclose(fertilitydata);//close access to file

    //Splitting of data into 4 different sets
    for(int i=0;i<100;i++){
        if(i<90){
            for(int j=0;j<10;j++){
                if(j<9){
                    inputtrain[i][j]=inputarray[i][j];
                }
                else{
                    outputtrain[i]=inputarray[i][j];
                }
            }
        }
        else{
            for(int j=0;j<10;j++){
                if(j<9){
                    //printf("Array %d: %.2f\n",i+1,inputarray[i][j]);
                    inputtest[i-90][j]=inputarray[i][j];
                }
                else{
                    //printf("Array %d: %.2f\n",i+1,inputarray[i][j]);
                    outputtest[i-90]=inputarray[i][j];
                }
            }
        }
    }

    //Traverse all arrays
    
    //printf("\nTraverse Input Training array:\n");
    //traverse2DArray(90,9,inputtrain);
    //printf("\nTraverse Output Training array:\n");
    //traverseArray(90,outputtrain);
    //printf("\nTraverse Input Test array:\n");
    //traverse2DArray(10,9,inputtest);
    //printf("\nTraverse Output Test array:\n");
    //traverseArray(10,outputtest);
    

    return 1;
}
void traverseArray(int m,float array[m]){
    for(int i=0;i<m;i++){
            printf("Element %d: %f\n",i+1,array[i]);
        }
}
void traverse2DArray(int m,int n,float array[m][n]){
    for(int i=0;i<m;i++){
            printf("Array %d: ",i+1);
            for(int j=0;j<n;j++){
                printf("%f ",array[i][j]);
            }
            printf("\n");
        }
}