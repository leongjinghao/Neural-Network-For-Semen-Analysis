#include<stdio.h>
float inputarray[100][10];//All data within 2D array
float inputtrain[90][9];//2D array for training data input
float inputtest[10][9];//2D array for training data output
float outputtrain[90][1];//2D array for testing data input
float outputtest[10][1];//2D array for testing data output
int inputData(char *filename);
int traverseArray(int m,int n,float array[m][n]);
int inputData(char *filename){
    FILE *fertilitydata;
    if(fertilitydata==NULL){//if file is unable to be found
        printf("Error while opening file!\n");
    }
    else{//if file is found
        printf("File found successfully!\n");
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
                        outputtrain[i][0]=inputarray[i][j];
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
                        outputtest[i-90][0]=inputarray[i][j];
                    }
                }
            }
        }

        /*printf("\nTraverse Input Training array:\n");
        traverseArray(90,9,inputtrain);
        printf("\nTraverse Output Training array:\n");
        traverseArray(90,1,outputtrain);
        printf("\nTraverse Input Test array:\n");
        traverseArray(10,9,inputtest);
        printf("\nTraverse Output Test array:\n");
        traverseArray(10,1,outputtest);*/

    }
    return 1;
}
int traverseArray(int m,int n,float array[m][n]){
    for(int i=0;i<m;i++){
            printf("Array %d: ",i+1);
            for(int j=0;j<n;j++){
                printf("%.2f ",array[i][j]);
            }
            printf("\n");
        }
    return 2;
}