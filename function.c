/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 * This file contain functions of the program.
 *
 * For more detail on how to use those functions let see in function.h.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

float eval_sol(Solution s, Data d, int *index){
    int i,j,k;
    float eval=0,arrival;

    *index=-1;

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

            for(k=0;k<(sizeof(s.job_delivered[i][j])/sizeof(int)-1);k++){
                if((d.job_due_date[s.job_delivered[i][j][k]]-arrival)>=0){
                    eval+=(d.job_due_date[s.job_delivered[i][j][k]]-arrival)*d.customer[d.job_customer[s.job_delivered[i][j][k]]];
                }
                else{
                    *index=i;
                    return (d.job_due_date[s.job_delivered[i][j][k]]-arrival);/*Here is returned the delay between arival and due date if arrival is too late*/

                }
            }
        }
    }

    return eval;
}

void solcpy(Solution *dest, Solution* src){
    int i,j,k;

    dest->nbTrip=src->nbTrip;
    dest->trip=malloc(dest->nbTrip*sizeof(int*));
    dest->job_delivered=malloc(dest->nbTrip*sizeof(int**));
    dest->trip_jobs=malloc(dest->nbTrip*sizeof(int*));
    dest->tripSize=malloc(dest->nbTrip*sizeof(int));
    dest->tripStartTime=malloc(dest->nbTrip*sizeof(float));

    for(i=0;i<dest->nbTrip;i++){
        dest->tripSize[i]=src->tripSize[i];
        dest->tripStartTime[i]=src->tripStartTime[i];

        dest->trip[i]=malloc(dest->tripSize[i]*sizeof(int));
        dest->trip_jobs[i]=malloc(dest->tripSize[i]*sizeof(int));
        dest->job_delivered[i]=malloc(dest->tripSize[i]*sizeof(int*));

        for(j=0;j<dest->tripSize[i];j++){
            dest->trip[i][j]=src->trip[i][j];
            dest->trip_jobs[i][j]=src->trip_jobs[i][j];
            dest->job_delivered[i][j]=malloc(sizeof(src->job_delivered[i][j]));
            for(k=0;k<(sizeof(dest->job_delivered[i][j])/sizeof(int)-1);k++){
                dest->job_delivered[i][j][k]=src->job_delivered[i][j][k];
            }
        }
    }
}

void mkfsol(Solution *dest, Data d){
    int i,j,k;

    dest->nbTrip=(d.n/d.c)+(d.n%d.c!=0?1:0);
    dest->trip=malloc(dest->nbTrip*sizeof(int*));
    dest->job_delivered=malloc(dest->nbTrip*sizeof(int**));
    dest->trip_jobs=malloc(dest->nbTrip*sizeof(int*));
    dest->tripSize=malloc(dest->nbTrip*sizeof(int));
    dest->tripStartTime=malloc(dest->nbTrip*sizeof(float));

    for(i=0;i<dest->nbTrip;i++){
        dest->tripSize[i]=(d.n/((i+1)*d.c)==0?d.n%d.c:d.c);

        dest->trip[i]=malloc(dest->tripSize[i]*sizeof(int));
        dest->trip_jobs[i]=malloc(dest->tripSize[i]*sizeof(int));
        dest->job_delivered[i]=malloc(dest->tripSize[i]*sizeof(int*));

        for(j=0;j<dest->tripSize[i];j++){
            dest->trip[i][j]=d.job_customer[(i*5)+j];
            dest->trip_jobs[i][j]=(i*5)+j;
            dest->job_delivered[i][j]=malloc(sizeof(int));
            dest->job_delivered[i][j][0]=(i*5)+j;
        }

    }

    /*This part is to set all starting times logical way*/
    for(i=dest->nbTrip-1;i>=0;i--){
        if(i==dest->nbTrip-1)
            dest->tripStartTime[i]=d.job_due_date[dest->tripSize[i]-1];
        else{
            if(d.job_due_date[dest->tripSize[i]-1]<=(dest->tripStartTime[i+1]-d.time_matrix[dest->trip[i][dest->tripSize[i]-1]][0]))
                dest->tripStartTime[i]=d.job_due_date[dest->tripSize[i]-1];
            else
                dest->tripStartTime[i]=(dest->tripStartTime[i+1]-d.time_matrix[dest->trip[i][dest->tripSize[i]-1]][0]);
        }
        for(j=dest->tripSize[i]-2;j>=-1;j--){
            if(j>-1)
                dest->tripStartTime[i]-=d.time_matrix[dest->trip[i][j]][dest->trip[i][j+1]];
            else
                dest->tripStartTime[i]-=d.time_matrix[0][dest->trip[i][j+1]];
        }

    }
}

void print_sol(Solution s,Data data){
    int i,j,k;
    printf("\n\n # - - - - - - - SOLUTION - - - - - - - #\n\nGENERALITE:\n- - - - - - - - - - - - - - - \n");

    printf("Evaluation : %f",eval_sol(s,data,&i));

    if(i!=-1)
        printf(" /!\\ la solution n'est pas valide sur le temps de départ du voyage %d /!\\", i+1);


    printf("\nNombre de voyages: %d\n\n",s.nbTrip);

    for(i=0;i<s.nbTrip;i++){
        printf("Voyage %d : 0",i+1);
        for(j=0;j<s.tripSize[i];j++){
            printf(" - %d",s.trip[i][j]);
        }
        printf(" - 0 \n");
    }
    printf("\nDETAILS:\n- - - - - - - - - - - - -\n");
    for(i=0;i<s.nbTrip;i++){
        printf("Voyage %d :\n",i+1);
        printf("\tTemps de départ: %f \n\tTaille du voyage: %d\n\n",s.tripStartTime[i],s.tripSize[i]);
        for(j=0;j<s.tripSize[i];j++){
            printf("\tEscale %d: \n",j+1);
            printf("\t\tClient visité: %d\n\t\tJob délivré:",s.trip[i][j]);
            for(k=0;k<(sizeof(s.job_delivered[i][j])/sizeof(int)-1);k++){
                printf(" %d",s.job_delivered[i][j][k]);
            }
            printf("\n\n");
        }
    }

}

Solution rnd_way(Solution s, Data d){
    srand(time(NULL));
    Solution newS;
    solcpy(&newS,&s);
    int chT=rand()%s.nbTrip;
    int chCh1=rand()%s.tripSize[chT];
    int chCh2=rand()%s.tripSize[chT];
    int tmp,i;
    int* tmp_del=malloc(sizeof(newS.job_delivered[chT][chCh1]));
    float eval;

    while (chCh1==chCh2)
        chCh2=rand()%s.tripSize[chT];



    printf("%d %d",newS.trip[chT][chCh1],newS.trip[chT][chCh2]);
    tmp=newS.trip[chT][chCh1];
    newS.trip[chT][chCh1]=newS.trip[chT][chCh2];
    newS.trip[chT][chCh2]=tmp;
    printf("\n%d %d",newS.trip[chT][chCh1],newS.trip[chT][chCh2]);

    memcpy(tmp_del,newS.job_delivered[chT][chCh1],sizeof(newS.job_delivered[chT][chCh1]));
    newS.job_delivered[chT][chCh1]=realloc(newS.job_delivered[chT][chCh1],sizeof(newS.job_delivered[chT][chCh2]));
    memcpy(newS.job_delivered[chT][chCh1],newS.job_delivered[chT][chCh2],sizeof(newS.job_delivered[chT][chCh2]));
    newS.job_delivered[chT][chCh2]=realloc(newS.job_delivered[chT][chCh2],sizeof(tmp_del));
    memcpy(newS.job_delivered[chT][chCh2],tmp_del, sizeof(tmp_del));

    /*This small loop is here to be sure that the solution is correct and every
     * job is delivered before the due date.*/
    while((eval=eval_sol(newS,d,&i))<0)
        newS.tripStartTime[i]+=eval;

    return newS;
}
>>>>>>> rndWay
