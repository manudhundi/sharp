/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./jobScheduler
 * 
 *  Schedule jobs using greedy algorithms to minimizing the weighted
 *  sum of completion times
 *
 *  C++ implementation
 *
 *  This file implements the base class that schedules the jobs as per
 *  utility value computed by inherited classes and calculates the
 *  weighted completion times
 *
 *  This is the solution to the assigment 1 of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include "job_scheduler.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

/* Compare jobs based on wts. When there is a tie in utility val
   we schedule job with higher wt first */
bool myCompWt (jobT i, jobT j) 
{
    return (i.wt > j.wt); 
}

/* Compare utility val */
bool myComp (jobT i, jobT j) 
{
    return (i.utilityVal > j.utilityVal); 
}

/* Clean up */
jobScheduler::~jobScheduler()
{
    delete []auxJobArray;
}

int64_t jobScheduler::weightedCompletionTime(jobT* jobs, unsigned int numJobs)
{
    int64_t weightedSum = 0;
    unsigned int time = 0;
    int retVal = 0;
    auxJobArray = new jobT[numJobs];
    /* Compute w-l for all jobs */
    for (unsigned int i = 0; i < numJobs; i++) {
        auxJobArray[i].wt = jobs[i].wt;
        auxJobArray[i].lt = jobs[i].lt;
    }
    retVal = computeUtilityVal(jobs, numJobs);
    if (retVal) {
        return 0;
    }
    /* sort jobs based on wt using STL */
    sort(auxJobArray, auxJobArray + numJobs, myCompWt);

    /* Stable sort auxJobArray based on utility val using STL
       Stable sort because in case of tie we want to schedule job with highest
       wt first */
    stable_sort(auxJobArray, auxJobArray + numJobs, myComp);

    /* Now compute the weighted completion time */
    for (unsigned int i = 0; i < numJobs; i++) {
        time += auxJobArray[i].lt;
        weightedSum += (auxJobArray[i].wt * time);
    }
    return weightedSum;
}
