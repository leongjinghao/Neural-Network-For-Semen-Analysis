#include<stdio.h>
#include<stdlib.h>

void gnuplotMAE();

void gnuplotMAE()
{
    char outputfile[]={"plot 'mae_Output.txt'"};
    FILE * gnuplotPipe = popen("gnuplot -p", "w");

    if(gnuplotPipe==NULL)
    {
        printf("ERROR 404\n");
    }
    else
    {
        fflush(gnuplotPipe);
        fprintf(gnuplotPipe,"%s \n",outputfile);
    }
}