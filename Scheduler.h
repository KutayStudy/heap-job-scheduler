#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <optional>   // C++17
#include <string>
#include "Job.h"
#include "BinaryHeap.h"

// Heap-based job scheduler that uses an array-based BinaryHeap
// as the ready queue.
class Scheduler
{
public:
    Scheduler();

    // Add a new job to the system
    void addJob(const std::string& name,
                int priority,
                int duration,
                int deadline = -1);

    // Advance the global clock by a given amount of time units
    void tick(int timeUnits);

    // Run the next job (non-preemptive: run until completion)
    void runNext();

    // Run all remaining jobs until the system is idle
    void runAll();

    // Cancel a job by id (if it is waiting or currently running)
    void cancelJob(int jobId);

    // Print the jobs in the ready queue (without destroying the heap)
    void printReadyQueue() const;

    // Print all completed jobs
    void printCompletedJobs() const;

    // Print statistics (e.g., average waiting time, turnaround time)
    void printStats() const;

    // Query whether there are any pending jobs
    bool hasPendingJobs() const;

    // Get current global clock
    int getCurrentTime() const;

private:
    BinaryHeap readyQueue;          // heap-based ready queue
    std::vector<Job> completedJobs; // finished jobs

    std::optional<Job> currentJob;  // currently running job, if any
    int currentTime;                // global time
    int nextId;                     // id generator for new jobs

    // If there is no current job, pick one from the heap
    void startNextJobIfNeeded();

    // Finalize the current job and move it to completed list
    void finishCurrentJob();
};

#endif // SCHEDULER_H