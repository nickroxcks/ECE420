//Guided implementation
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#include "Lab3IO.h"
#include "timer.h"
#include <math.h>

double **Matrix;
double *out_vec;
int size;
int num_rows;
int num_columns;

int thread_count;

// Function to perform gauss elemination using openmp
void gauss_elim(){
    int cur_row;  //k
    int row_section; //the curent row num from cur_row to num_rows - 1
    int max_abs_row;
    double temp;
    int i,j;
    #pragma omp parallel num_threads(thread_count) default(none) private(i,j, row_section,temp) shared(max_abs_row,Matrix,num_rows,num_columns)
    {
        for (int cur_row = 0;cur_row<num_rows-1;cur_row++){
            //Begin pivoting
            #pragma omp single
            {
                max_abs_row = cur_row;
                for(row_section = cur_row + 1;row_section<num_rows;row_section++){
                    //find the row kp that has the maximum value of element in
                    //[max_row][cur_row]

                    if(abs(Matrix[row_section][cur_row]) > abs(Matrix[max_abs_row][cur_row])){
                        max_abs_row = row_section;
                    }

                }
                //if a change has occured, swap the new maximum row
                if(cur_row != max_abs_row){
                    //swap rows by goin through elements in columns
                    
                    int tmp_column;
                    double tmp;
                    for (tmp_column = 0; tmp_column < num_columns; tmp_column++){
                        tmp = Matrix[max_abs_row][tmp_column];
                        Matrix[max_abs_row][tmp_column] = Matrix[cur_row][tmp_column];
                        Matrix[cur_row][tmp_column] = tmp;
                    }
                    
                    
                }      
            }
            //Begin elimination portion
                #pragma omp for schedule(guided)
                for(i = cur_row + 1;i < num_rows;i++){
                    temp = Matrix[i][cur_row] / Matrix[cur_row][cur_row];
                    for(j = cur_row; j < num_columns;j++){
                        Matrix[i][j] = Matrix[i][j] - temp * Matrix[cur_row][j];
                    }
                }
        }
        //Begin jordan elimination
        int cur_row;
        int row_section;
        for(cur_row = num_rows-1;cur_row>0;cur_row--){
            #pragma omp for schedule(guided)
            for(row_section = 0;row_section<cur_row;row_section++){
                Matrix[row_section][num_columns-1] = Matrix[row_section][num_columns-1] - 
                (Matrix[row_section][cur_row] / Matrix[cur_row][cur_row] * Matrix[cur_row][num_columns-1]);
                Matrix[row_section][cur_row] = 0;
            }
        }
    }
}

void jordan_elim(){
    int cur_row;
    int row_section;
    #pragma omp parallel num_threads(thread_count) default(none) private(cur_row,row_section) shared(Matrix,num_columns,num_rows)
    for(cur_row = num_rows-1;cur_row>0;cur_row--){
        #pragma omp for schedule(guided)
        for(row_section = 0;row_section<cur_row;row_section++){
            Matrix[row_section][num_columns-1] = Matrix[row_section][num_columns-1] - 
            (Matrix[row_section][cur_row] / Matrix[cur_row][cur_row] * Matrix[cur_row][num_columns-1]);
            Matrix[row_section][cur_row] = 0;
        }
    }
}
// Main function
int main(int argc, char* argv[]){
    double start_time, end_time;
    if(argc != 2 ){
         printf("please enter in the format <number of threads>\n");
        return 0;
    }

    // initiallization
    thread_count = atoi(argv[1]);
    Lab3LoadInput(&Matrix,&size);
    num_rows = size;
    out_vec = CreateVec(num_rows);
    num_columns = num_rows + 1;

    GET_TIME(start_time);
    gauss_elim();
    //jordan_elim();  //try using the same thread pool
    GET_TIME(end_time);

    //save to output file
    int cur_row;
    for (cur_row = 0; cur_row < num_rows; cur_row++){
        out_vec[cur_row] = Matrix[cur_row][num_columns-1] / Matrix[cur_row][cur_row];
    }
    Lab3SaveOutput(out_vec,num_rows,end_time-start_time);
    return 0;
}