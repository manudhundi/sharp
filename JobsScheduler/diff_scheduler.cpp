/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./jobScheduler
 * 
 *  Schedule jobs using greedy algorithms to minimizing the weighted
 *  sum of completion times
 *
 *  C++ implementation
 *
 *  This file implements the derived class diffScheduler which computes
 *  the utility value for a job using (weight - length)
 *
 *  This is the solution to the assigment 1 of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include "job_scheduler.h"

int diffScheduler::computeUtilityVal(jobT* jobs, unsigned int numJobs)
{
    /* Compute w-l for all jobs */
    for (unsigned int i = 0; i < numJobs; i++) {
        auxJobArray[i].utilityVal = jobs[i].wt - jobs[i].lt; /* w-l */
    }
    return 0;
}

