#include <stdio.h>
#include <stdlib.h>

void outputMAE(FILE *outputFile, int itr, double mae);

void outputMAE(FILE *outputFile, int itr, double mae)
{
    //write to file
    fprintf(outputFile,"%d  %.10f\n",itr,mae);
    //fprintf(outputFile,"%.10f  %d\n",mae,itr);
}