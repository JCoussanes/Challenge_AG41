/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#ifndef DEF_DATA_STRUCTURE
#define DEF_DATA_STRUCTURE

/*Here is the structure which contains all datas of the problem*/
struct data{
    int n; /*Number of products*/
    int m; /*Number of customers*/
    float eta; /*Transporter cost factor*/
    int c; /*Transporter capacity*/

    int* job_customer;/*Array which contains what customer ordered the job i*/
    float* job_due_date;/*Array which contains what time the job i have to be delivered*/
    float* customer; /*Array which contains the holding costs of each customer*/
    float** time_matrix; /*Matrix which contains the travelling time between customers and supplier (if there is no link, the time is -1)*/
    
};
typedef struct data Data;

/*Here is the structure which contains all datas of a solution*/
struct sol{
    int **trip;/*Array of trip. Each trip is an array of customers ordered by visiting order*/
    int ***job_delivered;/*Array of job delivered. job_delivered[0][0] is the array of job delivered at the first step of the first trip.*/
    int nbTrip;/*Number of trips*/
    int *tripSize;/*Array of lenght of trip.*/
    float *tripStartTime;/*Array of starting time of trip*/
};
typedef struct sol Solution;
#endif

