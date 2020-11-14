#include<stdio.h>
#include<stdlib.h>
int main(){
    char outputfile[]="mae_Output.txt";
    FILE * gnuplotPipe = _popen ("gnuplot -p", "w");
    if(gnuplotPipe==NULL){
        printf("404");
    }
    else{
        printf("ALLAH\n");
        fflush(gnuplotPipe);
        fprintf(gnuplotPipe,"set title 'gay'\n");
        fprintf(gnuplotPipe,"plot '%s'\n",outputfile);
        
    }

   /* FILE *script=fopen("script.txt","w");//creating script file
    char output[]="mae_Output.txt";
    fprintf(script,"plot \'%s\'",output);
    fclose(script);
    system("wgnuplot -p script.txt");//calling script*/


    return 0;
}