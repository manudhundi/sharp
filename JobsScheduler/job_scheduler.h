/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./jobScheduler
 * 
 *  Schedule jobs using greedy algorithms to minimizing the weighted
 *  sum of completion times
 *
 *  C++ implementation
 *
 *  This header file contains the api for the base class jobScheduler
 *  and the derived classes ratioScheduler and diffScheduler
 *
 *  This is the solution to the assigment 1 of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include <iostream>
#include <stdint.h>
using namespace std;

/* Job with necessary details */
typedef struct job {
    float wt;
    float lt;
    float utilityVal; /* indicates job priority precedence */
}jobT;

class jobScheduler {
public:
    ~jobScheduler();
    int64_t weightedCompletionTime(jobT* jobs, unsigned int numJobs);
protected:
    /* Accessed only by derived classes */
    virtual int computeUtilityVal(jobT* jobs, unsigned int numJobs) 
    { 
        cout << "Unknown utility model selected" << endl;
        return -1;
    }
    jobT *auxJobArray;
};

/* Compute utility val using wt/lt */
class ratioScheduler: public jobScheduler
{
private:
    int computeUtilityVal(jobT* jobs, unsigned int numJobs);
};

/* Compute utility val using wt-lt */
class diffScheduler: public jobScheduler
{
private:
    int computeUtilityVal(jobT* jobs, unsigned int numJobs);
};

