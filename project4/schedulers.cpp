#include <iostream>

#include "schedulers.h"

using std::cout;
using std::endl;

Scheduler::Scheduler()
{
    next_tid = 1;
}

void Scheduler::add(string name, int priority, int burst)
{
    cout << "Scheduler::add(\"" << name << "\", " << priority << ", " << burst << ")" << endl;

    auto task = new Task;
    task->name = name;
    task->tid = next_tid++;
    task->priority = priority;
    task->burst = burst;

    tasks.push_back(task);
}

Scheduler::~Scheduler()
{
    for (auto task : tasks) {
        delete task;
    }
}

extern "C" void destroy(Scheduler *scheduler)
{
    delete scheduler;
}
