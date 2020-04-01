#define LAB4_EXTEND

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Lab4_IO.h"
#include "timer.h"
#include <mpi.h>

#define EPSILON 0.00001
#define DAMPING_FACTOR 0.85

#define THRESHOLD 0.0001

int main(int argc, char* argv[]){
    struct node *nodehead;
    int nodecount;
    double *r, *r_pre, *contribution, *local_r, *local_contribution;
    int i,j;
    double damp_constant;
    int iterationcount = 0;
    double start ,end;
    FILE *fp, *ip;

    //mpi variables
    int comm_size;
    int curr_rank;
    int chunk_size;
    int local_node_count;
    int start_index;
    int last_index;
    // Load the data and simple verification
    if ((ip = fopen("data_input_meta","r")) == NULL) {
        printf("Error opening the data_input_meta file.\n");
        return 254;
    }
    fscanf(ip, "%d\n", &nodecount);
    fclose(ip);

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &curr_rank);
    
    if (node_init(&nodehead, 0, nodecount)) return 254;
    
    chunk_size = (int)(nodecount / comm_size);
    if (chunk_size * comm_size != nodecount)
    {
        chunk_size += 1;  //undividable number of work case
    }

    local_node_count = chunk_size * comm_size;

    //allocate memory
    r = malloc(local_node_count * sizeof(double));
    r_pre = malloc(local_node_count * sizeof(double));
    local_r = malloc(chunk_size * sizeof(double));

    //ri(0) = 1/N for all i's
    for ( i = 0; i < nodecount; ++i)
        r[i] = 1.0 / nodecount;
   
    contribution = malloc(local_node_count * sizeof(double));
    local_contribution = malloc(chunk_size * sizeof(double));
    
    //equation 3 formula
    for ( i = 0; i < nodecount; ++i)
        contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
    
    damp_constant = (1.0 - DAMPING_FACTOR) / nodecount;  //make it easier for calculation
    
    //start calculating
    GET_TIME(start);
    do{
        ++iterationcount;
        vec_cp(r, r_pre, nodecount);
        //each process has a start and end to use
        start_index = curr_rank * chunk_size;
        last_index = (curr_rank + 1) * chunk_size - 1;
        // updating value
        for ( i = start_index; i < nodecount && i<= last_index; ++i){
            r[i] = 0;
            for ( j = 0; j < nodehead[i].num_in_links; ++j)
                r[i] += contribution[nodehead[i].inlinks[j]];
            r[i] += damp_constant;
        }
        for ( i=start_index; i<nodecount && i<=last_index; ++i){
            contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
        }

        vec_cp(&contribution[start_index], local_contribution, chunk_size);
        vec_cp(&r[start_index], local_r, chunk_size);
        MPI_Allgather(local_r, chunk_size, MPI_DOUBLE, r, chunk_size, MPI_DOUBLE, MPI_COMM_WORLD);
        MPI_Allgather(local_contribution, chunk_size, MPI_DOUBLE, contribution, chunk_size, MPI_DOUBLE, MPI_COMM_WORLD);
    }while(rel_error(r, r_pre, nodecount) >= EPSILON);
    GET_TIME(end);

    MPI_Finalize();
    //ensure this is called once
    if(curr_rank == 0){
    printf("Program converged at %d th iteration.\nElapsed time %f.\n", iterationcount, end-start);
    Lab4_saveoutput(r,nodecount,end-start);
    // post processing
    node_destroy(nodehead, nodecount);
    free(contribution);
    
    // Compare the result 
    free(r); free(r_pre); 
    free(local_contribution);
    free(local_r);
    }

    return(0);
}