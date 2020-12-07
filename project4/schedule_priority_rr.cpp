#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void SchedulePriorityRR::add(string name, int priority, int burst)
{
    cout << "SchedulePriorityRR::add(\"" << name << "\", " << priority << ", " << burst << ")" << endl;

    auto task = new Task;
    task->name = name;
    task->tid = ++next_tid;
    task->priority = priority;
    task->burst = burst;

    tasks[priority-1]->push_back(task);
}

void SchedulePriorityRR::schedule(CPU *cpu)
{
    waitingTiming = new int[next_tid];
    responseTiming = new int[next_tid];
    turnAroundTiming = new int[next_tid];

    timeExit = new int[next_tid];
    burstTime = new int[next_tid];

    for(int i = 0; i<next_tid; i++)
    {
        waitingTiming[i] = 0;
        responseTiming[i] = 0;
        turnAroundTiming[i] = 0;
        burstTime[i] = 0;
        timeExit[i] = 0;
    }
    
    int timeFrame = 0;
    int timeSlice = 0;

    cout << "SchedulePriorityRR::schedule()" << endl;
    cout << "CPU::QUANTUM is set at " << cpu->QUANTUM << endl;
    bool isEmpty = true;
    
    do
    {
        isEmpty = true;
        
        //let process the first task
        Task* tempTask = pickNextTask();

        //then finish this task by pop it off from the 'queue'
        for (int i=tasks.size()-1; i>=0; i--)
        {
            if(i == tempTask->priority-1)
            {//then round-robin here
                indexOfCurrentProcess = 0;
                while(!tasks[i]->empty())
                {
                    //let process the first task
                    tempTask = pickNextTask();

                    //saving time record
                    timeEnter.push_back(timeFrame);
                    arrayOfID.push_back(tempTask->tid-1);

                    //does not care about the slice in this algo.
                    timeSlice = (tempTask->burst > cpu->QUANTUM)?(cpu->QUANTUM):(tempTask->burst);

                    //set time slice of QUANTUM at 3 already for testing purpose
                    cpu->run(tempTask,timeSlice);
                    timeFrame += timeSlice;
                    timeExit[tempTask->tid-1] = timeFrame;
                    burstTime[tempTask->tid-1] += timeSlice;

                    //then finish this task by pop it off from the 'queue'
                    if(tempTask->burst <= cpu->QUANTUM)
                    {
                        tasks[i]->remove(tempTask);
                        tempTask->burst = 0 ;

                        delete tempTask;
                    }
                    else //tempTask->burst > cpu->QUANTUM;
                    {
                        tempTask->burst -= cpu->QUANTUM; //decrease 
                        indexOfCurrentProcess++;//move to the next process
                    }
                }
                break;
            }
        }

        for (int i=tasks.size()-1; i>=0; i--)
        {
            if(tasks[i]->size()>0)
            {
                isEmpty = false;
                break;
            }
        }

    }while(isEmpty == false);
}

Task *SchedulePriorityRR::pickNextTask()
{
    Task* tempTask = NULL;
    for (int i=tasks.size()-1; i>=0; i--)
    {
        if(tasks[i]->size()>0)
        {//then round robin here
            indexOfCurrentProcess = indexOfCurrentProcess % tasks[i]->size();
            tempTask = *next(tasks[i]->begin(),indexOfCurrentProcess);
            break;
        }
    } 
    return tempTask;    
}

void SchedulePriorityRR::averageTiming()
{
    cout << "SchedulePriorityRR::average()" << endl;
    float waitTimeAVG = 0.0;
    float responseTimeAVG = 0.0;
    float turnAroundTimeAVG = 0.0;
    int processID = 0;
    
    for(int i = 0; i<next_tid; i++)
    {//for the response timing
        processID = arrayOfID[i];
        responseTiming[processID] = timeEnter[processID];
        //cout << " ID[" << processID << "]" << responseTiming[processID] << endl;
    }
    
    for(int i = 0; i<next_tid; i++)
    {//for the turn around timing
        processID = arrayOfID[i];
        turnAroundTiming[processID] = timeExit[processID];
        //TURN AROUND = TIME EXIT - ARRIVAL (set 0 for all processes = TIME EXIT)
        //cout << " ID[" << processID << "]" << turnAroundTiming[processID] << endl;
    }

    for(int i = 0; i<next_tid; i++)
    {//for the wait time
        processID = arrayOfID[i];
        waitingTiming[processID] = turnAroundTiming[processID]-burstTime[processID];
        //cout << " ID[" << processID << "]" << waitingTiming[processID] << endl;
    }

    for(int i = 0; i<next_tid; i++)
    {
        waitTimeAVG += 1.0*waitingTiming[i];
        responseTimeAVG += 1.0*responseTiming[i];
        turnAroundTimeAVG += 1.0*turnAroundTiming[i];
    }

    waitTimeAVG /= next_tid;
    responseTimeAVG /= next_tid;
    turnAroundTimeAVG /= next_tid;

    cout << "Average wait | response | turn around = " 
    << waitTimeAVG << " | " << responseTimeAVG << " | " << turnAroundTimeAVG << endl;

    //done with timing, clean it
    delete []timeExit;
    delete []burstTime;
}

Scheduler *create()
{
    return new SchedulePriorityRR;
}
