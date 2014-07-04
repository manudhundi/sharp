/*************************************************************************
 *  Compilation:  make
 *  Execution:    ./jobScheduler
 * 
 *  Schedule jobs using greedy algorithms to minimizing the weighted
 *  sum of completion times
 *
 *  C++ implementation
 *
 *  Job weights and lengths are read from a file
 *
 *  This is client file calling the job scheduling class  
 *
 *  This is the solution to the assigment 1 of Algorithms2 course
 *  on coursera by Prof.Tim Roughgarden 
 *************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
#include "job_scheduler.h"

#define INPUT_FILE "jobs.txt"

/* In a big project, this function could be in a separate module */
void selectUtilityModel(jobScheduler** jobSched)
{
    int model = 0;
    cout << "Enter 1 for ratio; 2 for difference" << endl;
    cin >> model;
    
    if (1 == model) {
        ratioScheduler* ratioSched = new ratioScheduler;
        *jobSched = ratioSched;
    } else if (2 == model) {
        diffScheduler* diffSched = new diffScheduler;
        *jobSched = diffSched;
    } else {
        cout << "Unknown utility model selected" << endl;
        exit(1);
    }
}

int main()
{
    unsigned int numJobs;
    jobT* jobs;
    
    cout << "Job Scheduler" << endl;
    
    /* Read jobs weights and lengths from a file */
    ifstream file(INPUT_FILE);
    
    if (!file.is_open()) {
        cout << "File open error" << endl;
        exit(1);
    }
    string word;
    int i = 0;
    while (file >> word) {
        if (!i) { /* First word */
            cout << "Num Jobs is: " << word << endl;
            numJobs = atoi(word.c_str());
            jobs = new jobT[numJobs];
            i++;
            continue;
        }
        jobs[i-1].wt = atoi(word.c_str());
        file >> word;
        jobs[i-1].lt = atoi(word.c_str());
        i++;
    }
    
    /* Ptr to job scheduler base class */
    jobScheduler* jobSched;
    /* Select at runtime the child class. Runtime Polymorphism */
    selectUtilityModel(&jobSched);
    cout << "Weighted sum is: " << jobSched->weightedCompletionTime(jobs, numJobs) << endl;
}
