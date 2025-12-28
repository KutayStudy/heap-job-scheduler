#ifndef JOB_H
#define JOB_H

#include <string>

struct Job
{
    int id;                 // unique identifier
    std::string name;       // job name
    int priority;           // higher = more important
    int arrivalTime;        // time when the job entered the system
    int duration;           // total required processing time
    int remainingTime;      // remaining processing time
    int deadline;           // -1 if no deadline
    int startTime;          // first time the job started running, -1 if never started
    int completionTime;     // time when the job finished, -1 if not completed

    Job();
    Job(int id_,const std::string& name_,int priority_,int arrivalTime_,int duration_,int deadline_ = -1);
};

// Comparator for the priority queue / heap.
// It should define which job is considered "less" or "lower priority".
struct JobCompare
{
    bool operator()(const Job& a, const Job& b) const;
};

#endif // JOB_H