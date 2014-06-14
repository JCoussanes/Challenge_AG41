/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "data_structure.h"

float eval_sol(Solution s, Data d){
    int i,j,k;
    float eval=0,arrival;

    for(i=0;i<s.nbTrip;i++){
        for(j=0;j<s.tripSize[i];j++){
            if(j==0){
                eval+=d.eta*d.time_matrix[0][s.trip[i][j]];
                arrival=s.tripStartTime[i]+d.time_matrix[0][s.trip[i][j]];
            }
            else{
                eval+=d.eta*d.time_matrix[s.trip[i][j-1]][s.trip[i][j]];
                arrival=arrival+d.time_matrix[s.trip[i][j-1]][s.trip[i][j]];
            }

            for(k=0;k<(sizeof(s.job_delivered[i][j])/sizeof(int));k++){
                eval+=(d.job_due_date[s.job_delivered[i][j][k]]-arrival)*d.customer[d.job_customer[s.job_delivered[i][j][k]]];
            }

        }
    }
}

Solution first_sol(Solution s,Data d){
	int i,j,k;
	/*int * num_job_customer=0; /*Array which contains number of job demander by the client k */
	   
	   for(j=0;j<d.n/d.c;j++){
	   	
   		s.nbTrip=d.n/d.c;
    		s.tripSize[j]=d.c-1;
    		
     
     for(i = j*d.c; i < (j+1)*d.c; i++)
      {
        /* for(k=1;k<=d.m;k++){
         
		 if(d.job_customer[i]==k)
		 num_job_customer[k]++;
		 }*/
		 
         s.tripStartTime[j]+=d.time_matrix[d.job_customer[i]][d.job_customer[i+1]];  
		  
		/*for(f=0;f<s.tripSize[j];f++){
    	   for(k=0;k<d.num_job_customer[k],k++)*/
    	   
    	s.job_delivered[j][i-j*d.c][0]=d.job_customer[i];
	
		}
	
	     s.tripStartTime[j]=d.job_due_date[j*d.c]-s.tripStartTime[j];
        
     }
 }

