/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#ifndef DEF_GLOBAL_DATA
#define DEF_GLOBAL_DATA

int n=0; /*Number of products*/
int m=0; /*Number of customers*/
float eta=0; /*Transporter cost factor*/
int c=0; /*Transporter capacity*/

int* job_customer=NULL;
float* job_due_date=NULL;
float* customer=NULL; /*Array which contains the holding costs of each customer*/
float** time_matrix=NULL; /*Matrix which contains the travelling time between customers and supplier (if there is no link, the time is -1)*/

#endif

