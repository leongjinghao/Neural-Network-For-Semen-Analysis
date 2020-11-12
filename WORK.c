#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "output.h"
#include <time.h>

#define rol 100
#define col 10
#define FILENAME "fertility_Diagnosis_Data_Group9_13.txt"

static double MAE = 0.0f;
static double tMAE = 0.25f; // can fine tune //targeted MAE
static double lr = 0.05f; //can fine tune
static double MMSE = 0.0f;


static double input[rol][col];
static double trainInput[90][9];
static double trainOutput[90][1];
static double testInput[10][9];
static double testOutput[10][1];
static double z[90]; // 
static double yhat[90];

static double weight[9];
static double bias = 1;
FILE *out_ptr;

void loadData()
{
    FILE *file_ptr; 
    
    int i,j;
    
    if ((out_ptr = fopen("outputfile.txt", "w")) == NULL) // check if it is not a null pointer
    {
        printf("Error opening file!"); 
        exit(1); //program exits if pointer is NULL
    }

    if ((file_ptr = fopen(FILENAME, "r")) == NULL) // check if it is not a null pointer
    {
        printf("Error opening file!"); 
        exit(1); //program exits if pointer is NULL
    }

    for (i=0; i<100; i ++)
    {
        for (j=0; j<10; j ++)
        {
            if (i < 90)
            {
                if (j < 9)
                {
                    fscanf(file_ptr, "%lf%*c", &trainInput[i][j]);
                }
                else
                {   
                    fscanf(file_ptr, "%lf%*c", &trainOutput[i][0]);
                }
                
            }
            else
            {
                if (j < 9)
                {
                    fscanf(file_ptr, "%lf%*c", &testInput[i-90][j]);
                }
                else
                {
                    fscanf(file_ptr, "%lf%*c", &testOutput[i-90][0]);
                }
            }
            
            //printf ("%d, %d = %lf \n", i, j, input[i][j]);
        }
    
    }

    fclose(file_ptr);
}

void printData()
{
    for (int i=0; i<90; i ++)
    {
        printf("\n row %d\n", i);
        for (int j=0; j<9; j ++)
        {
              printf("%lf ", trainInput[i][j]);
        }
    }
    /*
    for (int i=0; i<90; i ++)
    {
         printf("row %d value=%lf \n", i, trainOutput[i][0]);
    }
    */
}

void printAll()
{
    for (int i=0; i<90; i ++)
    {
        printf("\n row %d\n", i);
        for (int j=0; j<9; j ++)
        {
              printf("%lf", trainInput[i][j]);
        }
         printf(" %lf", trainOutput[i][0]);
    }
}

// sigmoid eq
double sigmoid (double z)
{
    return (1/(1+exp(-z)));
}

double sigmoid1 (double z)
{
    return ((sigmoid(z) * (1 - sigmoid(z))));
}

void linear_regression()
{
    for (int i = 0; i < 90; i ++)
    {
        double sum = 0;
        for (int j = 0; j < 9; j ++)
        {
            sum += weight[j] * trainInput[i][j];
            // printf ("%lf \n", z[i]);
        }
        z[i] = sum + bias;
      // printf ("row=%d, %lf \n", i, z[i]);
    }
}

void cal_ycat()
{
    for (int i = 0; i < 90; i ++)
    {
        yhat[i] = sigmoid(z[i]);
      //  printf ("%lf\n", yhat[i]);
    }
}
 
void cal_MAE()
{
    double I = 90;
    double cal = 0;

    for (int i=0; i<90; i++)
    {
        cal += fabs(yhat[i]-trainOutput[i][0]);
    }

    MAE = cal / I;

}

void update_bias()
{
    //new bias
    double sum = 0;
    int I = 90;
    for (int i=0; i < 90; i ++)
    {
        sum += (yhat[i] - trainOutput[i][0]) * (exp(z[i])/pow((1+exp(z[i])),2));
        //sum += (yhat[i] - trainOutput[i][0]) * sigmoid1(yhat[i]) * (1 - sigmoid1(yhat[i]));
    }
    
    sum = sum / I;
    bias = bias - (lr * sum);
}

void update_weights()
{
    double sum[9];
    int I = 90;

    for (int j = 0; j < 9; j ++)
    {
        for (int i = 0; i < 90; i ++ )
        {
            sum[j] += ((yhat[i] - trainOutput[i][0]) * (exp(z[i])/pow((1+exp(z[i])),2) * trainInput[i][j])) ;
            //sum[j] += (yhat[i] - trainOutput[i][0]) * sigmoid1(yhat[i]) * (1 - sigmoid1(yhat[i])) * trainInput[i][j];
        }
        sum[j] = sum[j] / I;
    }
    
    for (int i=0; i<9; i ++)
    {
        weight[i] = weight[i] - (lr * sum[i]);
    }
}

void assign_weights()
{
    for (int i = 0; i < 9; i ++)
    {
        weight[i] = 1;
    }
}

double cal_mmse()
{
    double sum = 0;
    for (int i=0; i<90;i++)
    {
        sum += pow(yhat[i]-trainOutput[i][0],2);
    }

    sum = sum / 90;

    return sum;
}

double random()
{
    return (rand() % 1 + -1);
}

int main()
{
    int itr = 0;
    loadData();
    assign_weights();

    //printAll();

    srand(time(NULL));

    linear_regression();
    cal_ycat();
    cal_MAE();
    printf ("itr %d MAE=%lf \n", itr, MAE);

    while (MAE > tMAE)
    {
        ++ itr;
        update_weights();
        update_bias();
        linear_regression();
        cal_ycat();
        cal_MAE();
        outputMAE(out_ptr, itr, MAE);
        printf ("itr %d MAE=%lf \n", itr, MAE);
    }

    printf("\n w1: %lf w2: %lf w3: %lf w4: %lf w5: %lf w6: %lf w7: %lf w8: %lf w9: %lf\n", weight[0], weight[1], weight[2], weight[3], weight[4], weight[5], weight[6], weight[7], weight[8]);
    printf("bias = %lf \n", bias);

    printf("MMSE=%lf", cal_mmse());

    fclose(out_ptr);

    return 0;
}
