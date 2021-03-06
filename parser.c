/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

int parse_file(char* fileName, Data *d){
    FILE *fr;
    int *job_customer;
    float *job_due_date;
    float *customer;
    float ** time_matrix;
    d->m=0;
    char line[200], *str1, *token;
    int nbC=0;

    customer=malloc(sizeof(float));
    time_matrix=malloc(sizeof(float*));
    time_matrix[0]=malloc(sizeof(float));

    customer[0]=0;
    time_matrix[0][0]=0;

    fr = fopen (fileName, "rt");

    while(fgets(line, 200, fr) != NULL)
    {
        char* newLine=NULL;

        int i,j,l;
        for(i=0,l=0;i<strlen(line);i++){
            if(line[i]!=' '){
                newLine=realloc(newLine,(l+1)*sizeof(char));
                newLine[l]=line[i];
                l++;
            }
        }

        for(str1=newLine; ;str1=NULL){
            token=strtok(str1,":");
            if(token==NULL)
                break;
            else{
                if(strcmp(token,"NBR_PRODUCT")==0){
                    d->n=atoi(strtok(NULL,":"));
                }
                else if(strcmp(token,"NBR_CUSTOMER")==0){
                    printf("yo");
                    d->m=atoi(strtok(NULL,":"));
                }
                else if(strcmp(token,"TRANSPORTER_CAPACITY")==0){
                    d->c=atoi(strtok(NULL,":"));
                }
                else if(strcmp(token,"TRANSPORTER_DELIVERY_COST_ETA")==0){
                    d->eta=atof(strtok(NULL,":"));
                }
                else if(strcmp(token,"CUSTOMER")==0){
                    nbC++;
                }
                else if(strcmp(token,"CUSTOMER_HOLDING_COSTS")==0){
                    customer=realloc(customer,(nbC+1)*sizeof(float));
                    customer[nbC]=atof(strtok(NULL,":"));
                }
                else if(strcmp(token,"TRANSPORTER_DELIVERY_TIME_SUPPLIER_CUSTOMER")==0){
                    float tmp;
                    time_matrix=realloc(time_matrix,(nbC+1)*sizeof(float*));
                    time_matrix[nbC]=NULL;
                    for(i=0;i<nbC+1;i++){
                        time_matrix[i]=realloc(time_matrix[i],(nbC+1)*sizeof(float));
                    }
                    tmp=atof(strtok(NULL,":"));
                    time_matrix[0][nbC]=tmp;
                    time_matrix[nbC][0]=tmp;
                }
                else if(strcmp(token,"JOB_CUSTOMER")==0){
                    job_customer=malloc(d->n*sizeof(int));
                    for(i=0;i<d->n;i++){
                        job_customer[i]=atoi(strtok(NULL,";"));
                    }
                }
                else if(strcmp(token,"JOB_DUE_DATES")==0){
                    job_due_date=malloc(d->n*sizeof(float));
                    for(i=0;i<d->n;i++){
                        job_due_date[i]=atof(strtok(NULL,";"));
                    }
                }
                else if(strcmp(token,"TIME_CUSTOMER_CUSTOMER")==0){
                    float tmp;
                    i=atoi(strtok(NULL,";"));
                    j=atoi(strtok(NULL,";"));
                    tmp=atof(strtok(NULL,";"));
                    time_matrix[i][j]=tmp;
                    time_matrix[j][i]=tmp;
                }
            }
        }
        free(newLine);
    }

    if(d->m==0)
        d->m=nbC;

    d->job_customer=job_customer;
    d->job_due_date=job_due_date;
    d->customer=customer;
    d->time_matrix=time_matrix;

    fclose(fr);
}
