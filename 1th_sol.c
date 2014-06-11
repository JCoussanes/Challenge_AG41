#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parser.h"
#include "data_structure.h"


int main(int argc, char** argv){
    
    Data d;
    int i,j,t,f;
    int *dd;
    int *jc;
    int index;
    int num;
    int cap;
    unsigned int seed;
    seed = time(0);
    srand(seed);
    num=d.m; 
    cap=d.c;
    int count[num];
     int **trip;
     int nbTrip;
     int *tripSize;
     float *tripStartTime;
     int ***job_delivered;
     
     
     
   for(i=0; i<num; i++ )
     {
        count[i] = i;
     }
   for(j=0;j<num/cap;j++){
   		nbTrip=num/cap;
    		tripSize[j]=cap-1;
    		
     
     for(i = j*cap; i < (j+1)*cap; i++)
     {
         index = (int)( (num - i) * 1.0 * rand()/(RAND_MAX + 1.0) );

         printf("%d\n",count[index]);
         
         dd[i]=d.job_due_date[count[index]];
         jc[i]=d.job_customer[count[index]];
         tripStartTime[j]+=d.time_matrix[jc[i]][jc[i+1]];  
		  
		for(f=0;f<tripSize[i];j++){
    	
    	job_delivered[j][f][count[index]]=jc[i];
	
		}
         
         count[index] = count[num - i - 1];
     }
      tripStartTime[j]=dd[(j+1)*cap-1]-tripStartTime[j];
	  /*for (i = j*cap; i < (j+1)*cap; i++){
	  
      arrival[i]=tripStartTime[j]+d.time_matrix[jc[i]][jc[i+1]];
      if(arrival[i]>dd[i])
      
  		}*/
      
 	}
 	
 

     

	 
    /* for(n=0;n<num/cap;n++){
     
     for(i=n*cap; i<(n+1)cap; i++ ){
     	for(j=i+1;j<cap;j++){
     	
     	if(dd[i]>dd[j])
    	{
     	t=jc[i];
     	jc[i]=jc[j];
     	jc[j]=t;
     	}
		}
		
	}
	
}

    
	AllTime+=dd[i]+d.time_matrix[jc[i]][jc[i+1]]*/
     return 0;
    
  
  
    
    
    
    }
