#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include "timer.h"
#include "lab1_IO.h"

int **A;
int **B;
int n;
int **C;
double Time;
int numthreads;

int Lab1_loadinput(int ***A, int ***B, int *n)
{
/*
    Allocate memory and load the input data for Lab 1

    -----
    Input:
    int ***A    pointer to the matrix A
    int ***B    pointer to the matrix B
    int *n      pointer to the matrix size

    original files should be the output of the matrixgen.c with name "data_input" in the same folder

    -----
    Output:
    Generated matrices will be passed back to the array *A and *B

    -----
    Example:
    Two integer array pointers and a integer should be defined before calling this function:
    int **A; int **B; int n
    call this function as
    lab1_loadinput(&A, &B, &n);
*/

    FILE* ip;
    int i,j;

    if ((ip = fopen("data_input","r")) == NULL)
    {
            printf("error opening the input data.\n");
            return 1;
    }
    fscanf(ip, "%d\n", n);

    *A = malloc(*n * sizeof(int*));
    *B = malloc(*n * sizeof(int*));

    for (i = 0; i < *n; i++)
    {
      (*A)[i] = malloc(*n * sizeof(int));
      (*B)[i] = malloc(*n * sizeof(int));
    }

    for (i = 0; i < *n; i++)
        for (j = 0; j< *n; j++)
            fscanf(ip, "%d\t", &(*A)[i][j]);
    for (i = 0; i < *n; i++)
        for (j = 0; j <* n; j++)
            fscanf(ip, "%d\t", &(*B)[i][j]);
    fclose(ip);
    return 0;
}

int Lab1_saveoutput(int **C, int *n, double Time)
{
/*
    Save the data to the file for Lab 1 

    -----
    Input:
    int **C     pointer to the result matrix 
    int *n      pointer to the matrix size
    double Time measure calulation time
    
    -----
    Output:
    data_output the stored data

    -----
    Example:
    lab1_loadinput(C, &n, Time);
*/

    FILE* op;
    int i,j;

    if ((op = fopen("data_output","w")) == NULL)
    {
        printf("Error opening the output file.\n");
        return 1;
    }

    fprintf(op, "%d\n\n", *n);
    for (i = 0; i <* n; i++)
    {
        for (j = 0; j< *n; j++)
            fprintf(op, "%d\t", C[i][j]);
        fprintf(op, "\n");
    }
    fprintf(op, "%f\n", Time);
    fclose(op);
    return 0;
}
void *matrix_mul(void *z){
    int k = *((int *) z);  //the thread number
    //printf("i am thread %d, going to do my calculations now\n",k);
    int x = floor(k/(sqrt((double) numthreads)));
    int y = k % ((int) sqrt((double) numthreads));
    int tmp = n / sqrt((double) numthreads);
    for(int i = tmp*x;i<=tmp*(x+1)-1;i++){
        for(int j = tmp*y;j<=tmp*(y+1)-1;j++){
            int sum = 0;
            for(int pos = 0; pos < n;pos++){
                sum = sum + (A[i][pos]) * (B[pos][j]);
            }
            //printf("The position %d %d has the value %d\n",i,j,sum);
            C[i][j] = sum;
            //printf("saved succefully\n");
        }
    }
}



int main(int argc, char** argv)
{   
    double start_time,end_time;
    numthreads = atoi(argv[1]);
    pthread_t tid[numthreads]; /* array of thread IDs */

    Lab1_loadinput(&A,&B,&n);
    C = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
    {
      (C)[i] = malloc(n * sizeof(int));
    }
    GET_TIME(start_time);
    for ( int i = 0; i < numthreads; i++ ) {
        //printf("this is thread %d bein created\n",i);
        int *arg = malloc(sizeof(*arg));
        if ( arg == NULL ) {
            fprintf(stderr, "Couldn't allocate memory for thread arg.\n");
            exit(EXIT_FAILURE);
        }

        *arg = i;
        pthread_create(&(tid[i]), NULL, matrix_mul, arg);
    }
    for ( int i = 0; i < numthreads; i++){
        pthread_join(tid[i], NULL);
    }
    GET_TIME(end_time);

    Time = end_time - start_time;
    Lab1_saveoutput(C,&n,Time);
    free(C);
    free(B);
    free(A);
    
    return 0;
}

 
