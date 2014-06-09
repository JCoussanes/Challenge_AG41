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
    int i,j;
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
                eval+=(d.job_due_date[s.job_delivered[i][j][k]]-arrival)*d.customer;
            }

        }
    }
}

int main(int argc, char** argv){

    return 0;
}

