#include "Scheduler.h"
#include <iostream>

Scheduler::Scheduler() : readyQueue(),completedJobs(),currentJob(std::nullopt),currentTime(0),nextId(1){
}

void Scheduler::addJob(const std::string& name,int priority,int duration,int deadline){
    Job j(nextId++,name,priority,currentTime,duration,deadline);
    readyQueue.push(j);
}

void Scheduler::tick(int timeUnits){
    if(timeUnits <= 0){
        return;
    }

    currentTime += timeUnits;

    if(currentJob.has_value()){
        currentJob->remainingTime -= timeUnits;

        if(currentJob->remainingTime <= 0){
            currentJob->remainingTime = 0;
            finishCurrentJob();
        }
    }else{
        startNextJobIfNeeded();
    }
}

void Scheduler::runNext()
{
    if (!currentJob.has_value()) {
        startNextJobIfNeeded();
    }

    if (!currentJob.has_value()) {
        std::cout << "No job to run.\n";
        return;
    }

    int t = currentJob->remainingTime;
    if (t < 0){
        t = 0;
    }

    currentTime += t;
    currentJob->remainingTime = 0;

    finishCurrentJob();
}

void Scheduler::runAll()
{
    while (hasPendingJobs()) {
        runNext();
    }
}

void Scheduler::cancelJob(int jobId){
    if (currentJob.has_value() && currentJob->id == jobId) {
        std::cout << "Cancelling currently running job " << jobId << "\n";
        currentJob.reset();
    }

    BinaryHeap temp;

    while (!readyQueue.empty()) {
        Job j = readyQueue.top();
        readyQueue.pop();
        if (j.id != jobId) {
            temp.push(j);
        } else {
            std::cout << "Cancelled job in ready queue: " << jobId << "\n";
        }
    }

    readyQueue = temp;
}

void Scheduler::printReadyQueue() const
{
    if (readyQueue.empty()) {
        std::cout << "Ready queue is empty.\n";
        return;
    }

    BinaryHeap copy = readyQueue;

    std::cout << "Ready queue (highest priority first):\n";
    while (!copy.empty()) {
        const Job& j = copy.top();
        std::cout << "  [id=" << j.id << ", name=" << j.name << ", priority=" << j.priority << ", arrival=" << j.arrivalTime << ", remaining=" << j.remainingTime << ", deadline=" << j.deadline  << "]\n";
        copy.pop();
    }

    if (currentJob.has_value()) {
        std::cout << "Current job: [id=" << currentJob->id << ", name=" << currentJob->name  << ", priority=" << currentJob->priority  << ", remaining=" << currentJob->remainingTime<< "]\n";
    }
}

void Scheduler::printCompletedJobs() const{
    if (completedJobs.empty()) {
        std::cout << "No completed jobs.\n";
        return;
    }

    std::cout << "Completed jobs:\n";
    for (const Job& j : completedJobs) {
        std::cout << "  [id=" << j.id<< ", name=" << j.name << ", arrival=" << j.arrivalTime  << ", start=" << j.startTime << ", completion=" << j.completionTime  << ", duration=" << j.duration  << ", priority=" << j.priority  << ", deadline=" << j.deadline << "]\n";
    }
}

void Scheduler::printStats() const
{
    if (completedJobs.empty()) {
        std::cout << "No completed jobs, no stats.\n";
        return;
    }

    long long totalWaiting = 0;
    long long totalTurnaround = 0;

    for (const Job& j : completedJobs) {
        int waiting = j.startTime - j.arrivalTime;
        int turnaround = j.completionTime - j.arrivalTime;

        totalWaiting += waiting;
        totalTurnaround += turnaround;
    }

    double avgWait = static_cast<double>(totalWaiting) / completedJobs.size();
    double avgTurn = static_cast<double>(totalTurnaround) / completedJobs.size();

    std::cout << "Stats over " << completedJobs.size() << " completed jobs:\n";
    std::cout << "  Average waiting time   : " << avgWait << "\n";
    std::cout << "  Average turnaround time: " << avgTurn << "\n";
}

bool Scheduler::hasPendingJobs() const{
    return !readyQueue.empty() || currentJob.has_value();
}

int Scheduler::getCurrentTime() const
{
    return currentTime;
}

void Scheduler::startNextJobIfNeeded(){
    if(currentJob.has_value()){
        return;
    }

    if(readyQueue.empty()){
        return;
    }

    Job j = readyQueue.top();
    readyQueue.pop();

    if(j.startTime == -1){
        j.startTime = currentTime;
    }

    currentJob = j;
}


void Scheduler::finishCurrentJob()
{
    if(!currentJob.has_value()){
        return;
    }

    currentJob->completionTime = currentTime;
    completedJobs.push_back(*currentJob);
    currentJob.reset();
    startNextJobIfNeeded();
}