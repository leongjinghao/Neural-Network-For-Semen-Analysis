#include <stdio.h>
#include <stdlib.h>

void outputMAE(FILE *outputFile, int itr, double mae);
void confusionMetrix(double *sigPT, double* actPT, int row, int *cMetrix);

void outputMAE(FILE *outputFile, int itr, double mae)
{
    //write to file
    fprintf(outputFile,"%d  %.10f\n",itr,mae);
}

void confusionMetrix(double *sigPT, double* actPT, int row, int *cMetrix)
{
    //temporary pointers
    double *tempSigPT = sigPT;
    double *tempActPT = actPT;

    for (int i=0; i<row; i++)
    {
        //if actual result is positive
        if (*tempActPT == 1)
        {
            //if guess result is also positive, it is a true positive
            if (*tempSigPT >= 0.5)
            {
                //increment counter at cell cMetrix[1][1]
                *(cMetrix+3)+=1;
            }
            //if guess result is negative, it is a false negative
            else
            {
                //increment counter at cell cMetrix[1][1]
                *(cMetrix+2)+=1;
            }
            
        }
        //if actual result is negative
        else
        {
            //if guess reuslt is positive, it is a false positive
            if (*tempSigPT >= 0.5)
            {
                //increment counter at cell cMetrix[0][1]
                *(cMetrix+1)+=1;
            }
            //if guess result is also negative, it is a true positive
            else
            {
                //increment counter at cell cMetrix[0][0]
                *(cMetrix)+=1;
            }
            
        }

        //move to next row
        ++tempSigPT;
        ++tempActPT;
    }
}