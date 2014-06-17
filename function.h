/*
 * Jérôme COUSSANES
 * jerome.coussanes@utbm.fr
 *
 *
 */

#ifndef DEF_FUNCTION
#define DEF_FUNCTION

/*This function calculate the cost of a solution.
 *  Parameters:
 *      s - is the solution to evaluate
 *      d - is the datas of the problem
 *      index - is the index of the incorrect starting time
 *  Return values:
 *      This function return the evaluation of the solution.
 *      - If the solution is corect the returned value is the
 *      real evaluation and i is equal to -1.
 *      - If the solution is incorrect the returned value is
 *      a negative value which is the time diference beween
 *      the due date of a job and the time when the transporter
 *      arrive. The index value is the index of the trip which
 *      should start sooner.
 *
 *  The negative return of this function is used to set a starting
 *  time which keep a random solution in the solutions' space.
 */
float eval_sol(Solution s, Data d,int *index);

/*This function copy the content of src in dest.
 *  Parameters:
 *      dest - is the pointer on the destination solution.
 *      src - is the pointer on the source solution.
 */
void solcpy(Solution *dest, Solution* src);

/*This function make the first solution.
 *  Parameters:
 *      dest - is the pointer on the solution which will be build.
 *      d - is the datas of the problem.
 */
void mkfsol(Solution *dest, Data d);

/*This function display a solution on the console.
 *  Parameters:
 *      s - is the solution to display.
 *      data - is the datas of the problem.
 */
void print_sol(Solution s,Data data);

/*This function generate randomly a new solution on the neighbourhood
 *of a previous one.
 *  Parameters:
 *      s - is the previous solution.
 *      d - is the datas of the problem.
 *  Return values:
 *      This function return a solution which has only one change one change
 *      compare to the solution s. It can be a 2-op neighbour or a neighbour
 *      which deliver more or less job in one step of one trip.*/
Solution rnd_way(Solution s, Data d);

/*(sizeof(trip_jobs[i])/sizeof(int))-1*/ 
#endif

