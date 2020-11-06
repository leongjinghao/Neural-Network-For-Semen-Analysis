#include<stdio.h>
int inputData(int train,int test,char *filename);
int traverseArray(int m,int n,float array[m][n]);
int inputData(int train,int test,char *filename){
    float inputarray[train+test][10];//All data within 2D array
    float inputtrain[train][9];//2D array for training data input
    float inputtest[test][9];//2D array for training data output
    float outputtrain[train][1];//2D array for testing data input
    float outputtest[test][1];//2D array for testing data output
    FILE *fertilitydata;
    if(fertilitydata==NULL){//if file is unable to be found
        printf("Error while opening file!\n");
    }
    else{//if file is found
        printf("File found successfully!\n");
        fertilitydata = fopen(filename,"r");//open file in read only
        //input data in array
        for(int i=0;i<(train+test);i++){
            for(int j=0;j<10;j++){
                fscanf(fertilitydata,"%f%*c",&inputarray[i][j]);
                //printf("%f",inputarray[i][j]);
            }
        }
        fclose(fertilitydata);//close access to file

        //Splitting of data into 4 different sets
        for(int i=0;i<train+test;i++){
            if(i<train){
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
                        inputtest[i-train][j]=inputarray[i][j];
                    }
                    else{
                        //printf("Array %d: %.2f\n",i+1,inputarray[i][j]);
                        outputtest[i-train][0]=inputarray[i][j];
                    }
                }
            }
        }

        printf("Traverse Input Training array:\n");
        traverseArray(train,9,inputtrain);
        printf("Traverse Output Training array:\n");
        traverseArray(train,1,outputtrain);
        printf("Traverse Input Test array:\n");
        traverseArray(test,9,inputtest);
        printf("Traverse Output Test array:\n");
        traverseArray(test,1,outputtest);

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