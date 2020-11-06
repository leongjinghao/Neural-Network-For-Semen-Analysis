#include<stdio.h>
int inputData(char *filename);
int inputData(char *filename){
    float inputarray[100][10];
    FILE *fertilitydata;
    if(fertilitydata==NULL){
        printf("Error while opening file!\n");
    }
    else{
        printf("File found successfully!\n");
        fertilitydata = fopen(filename,"r");
        for(int i=0;i<100;i++){
            for(int j=0;j<10;j++){
                fscanf(fertilitydata,"%f%*c",&inputarray[i][j]);
                //printf("%f",inputarray[i][j]);
            }
        }
        fclose(fertilitydata);

        //Traverse 2D array
        for(int i=0;i<100;i++){
                printf("Array #%d\n",i+1);
                for(int j=0;j<10;j++){
                    printf("Element #%d is %f \n",j+1,inputarray[i][j]);
                }
                printf("\n");
            }
    }
    return 1;
}