// Serial version

#define LAB4_EXTEND

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Lab4_IO.h"
#include "timer.h"

#define EPSILON 0.00001
#define DAMPING_FACTOR 0.85

#define THRESHOLD 0.0001

int main(int argc, char* argv[]){
    struct node *nodehead;
    int nodecount;
    double *r, *r_pre, *contribution;
    int i,j;
    double damp_constant;
    int iterationcount = 0;
    double start ,end;
    FILE *fp, *ip;

    // Load the data and simple verification
    
    if ((ip = fopen("data_input_meta","r")) == NULL) {
        printf("Error opening the data_input_meta file.\n");
        return 254;
    }
    fscanf(ip, "%d\n", &nodecount);
    fclose(ip);
    if (node_init(&nodehead, 0, nodecount)) return 254;
    // initialize variables
    r = malloc(nodecount * sizeof(double));
    r_pre = malloc(nodecount * sizeof(double));

    //ri(0) = 1/N for all i's
    for ( i = 0; i < nodecount; ++i)
        r[i] = 1.0 / nodecount;
    contribution = malloc(nodecount * sizeof(double));
    for ( i = 0; i < nodecount; ++i)
        contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
    damp_constant = (1.0 - DAMPING_FACTOR) / nodecount;  //make it easier for calculation
    // CORE CALCULATION
    GET_TIME(start);
    do{
        ++iterationcount;
        vec_cp(r, r_pre, nodecount);
        // update the value
        for ( i = 0; i < nodecount; ++i){
            r[i] = 0;
            for ( j = 0; j < nodehead[i].num_in_links; ++j)
                r[i] += contribution[nodehead[i].inlinks[j]];
            r[i] += damp_constant;
        }
        // update and broadcast the contribution
        for ( i=0; i<nodecount; ++i){
            contribution[i] = r[i] / nodehead[i].num_out_links * DAMPING_FACTOR;
        }
    }while(rel_error(r, r_pre, nodecount) >= EPSILON);
    GET_TIME(end);

    printf("%lf\n",end-start);
    Lab4_saveoutput(r,nodecount,end-start);
    // post processing
    node_destroy(nodehead, nodecount);
    free(contribution);
    
    // Compare the result 
    free(r); free(r_pre); 


    return(0);
}