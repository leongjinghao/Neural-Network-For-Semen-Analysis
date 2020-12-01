#include <stdio.h>
#include <stdlib.h>

void outputMAE(FILE *outputFile, int itr, double mae);
void confusionMatrix(double *sigPT, double* actPT, int row, int *cMatrix);

void outputMAE(FILE *outputFile, int itr, double mae)
{
    //write to file
    fprintf(outputFile,"%d  %.10f\n",itr,mae);
}

void confusionMatrix(double *sigPT, double* actPT, int row, int *cMatrix)
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
                //increment counter at cell cMatrix[1][1]
                *(cMatrix+3)+=1;
            }
            //if guess result is negative, it is a false negative
            else
            {
                //increment counter at cell cMatrix[1][1]
                *(cMatrix+2)+=1;
            }
            
        }
        //if actual result is negative
        else
        {
            //if guess reuslt is positive, it is a false positive
            if (*tempSigPT >= 0.5)
            {
                //increment counter at cell cMatrix[0][1]
                *(cMatrix+1)+=1;
            }
            //if guess result is also negative, it is a true positive
            else
            {
                //increment counter at cell cMatrix[0][0]
                *(cMatrix)+=1;
            }
            
        }

        //move to next row
        ++tempSigPT;
        ++tempActPT;
    }
}