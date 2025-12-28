#include "Job.h"

Job::Job()
    : id(0),
      name(),
      priority(0),
      arrivalTime(0),
      duration(0),
      remainingTime(0),
      deadline(-1),
      startTime(-1),
      completionTime(-1)
{
}

Job::Job(int id_,
         const std::string& name_,
         int priority_,
         int arrivalTime_,
         int duration_,
         int deadline_)
    : id(id_),
      name(name_),
      priority(priority_),
      arrivalTime(arrivalTime_),
      duration(duration_),
      remainingTime(duration_),
      deadline(deadline_),
      startTime(-1),
      completionTime(-1)
{
}

bool JobCompare::operator()(const Job& a, const Job& b) const
{
    if(b.priority > a.priority){
        return true;
    }else if(b.priority < a.priority){
        return false;
    }else{
        if(b.deadline == -1 && a.deadline != -1){
            return false;
        }
        if(a.deadline == -1 && b.deadline != -1){
            return true;
        }
        if(b.deadline < a.deadline){
            return true;
        }else if(b.deadline > a.deadline){
            return false;
        }else{
            if(b.arrivalTime < a.arrivalTime){
                return true;
            }else if(b.arrivalTime > a.arrivalTime){
                return false;
            }else{
                if(b.id < a.id){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
}