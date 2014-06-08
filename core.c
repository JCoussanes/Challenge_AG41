/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


int main(int argc, char** argv){
    int n=0; /*Number of products*/
    int m=0; /*Number of customers*/
    float eta=0; /*Transporter cost factor*/
    int c=0; /*Transporter capacity*/

    int* job_customer=NULL;
    float* job_due_date=NULL;
    float* customer=NULL; /*Array which contains the holding costs of each customer*/
    float** time_matrix=NULL; /*Matrix which contains the travelling time between customers and supplier (if there is no link, the time is -1)*/

    int i,j;

    if(argc != 2){
        printf("Wrong command. should be a.out <file path>.");
    }
    else{
        parse_file(argv[1],&n,&m,&eta,&c,&job_customer,&job_due_date,&customer,&time_matrix);

        printf("n: %d\nm: %d\neta: %f\nc: %d\njobs:",n,m,eta,c);
        for(i=0;i<n;i++){
            printf(" %d",job_customer[i]);
        }
        printf("\n     ");
        for(i=0;i<n;i++){
            printf(" %0.3f",job_due_date[i]);
        }
        printf("\ncustomer:");
        for(i=0;i<4;i++){
            printf(" %0.3f",customer[i]);
        }
        printf("\n\ntime matrix:\n");
        for(i=0;i<m+1;i++){
            for(j=0;j<m+1;j++){
                printf("%0.3f ",time_matrix[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}

