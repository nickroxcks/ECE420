#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#include "Lab3IO.h"
#include "timer.h"


int num_threads;

// Function to perform gauss jorden elemination using openmp
void gaussjordenelim(){
    int i,j,k;
    int size
    double ** Matrix
    
}
// Main function
int main(int argc, char* argv[]){
    if(argc != 2 ){
         printf("please enter in the format <number of threads>\n");
        return 0;
    }

    // initiallization
    num_threads = atoi(argv[1]);

    gaussjordenelim();
}