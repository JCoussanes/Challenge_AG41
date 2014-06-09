/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "data_structure.h"


int main(int argc, char** argv){

    Data data;

    int i,j;

    if(argc != 2){
        printf("Wrong command. should be a.out <file path>.");
    }
    else{
        parse_file(argv[1],&data);

        printf("n: %d\nm: %d\neta: %f\nc: %d\njobs:",data.n,data.m,data.eta,data.c);
        for(i=0;i<data.n;i++){
            printf(" %d",data.job_customer[i]);
        }
        printf("\n     ");
        for(i=0;i<data.n;i++){
            printf(" %0.3f",data.job_due_date[i]);
        }
        printf("\ncustomer:");
        for(i=0;i<data.m+1;i++){
            printf(" %0.3f",data.customer[i]);
        }
        printf("\n\ntime matrix:\n");
        for(i=0;i<data.m+1;i++){
            for(j=0;j<data.m+1;j++){
                printf("%0.3f ",data.time_matrix[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

