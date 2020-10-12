#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleFCFS::schedule(CPU *cpu)
{
    cout << "ScheduleFCFS::schedule()" << endl;
    ignore = cpu;
}

Task *ScheduleFCFS::pickNextTask()
{
    return NULL;
}

Scheduler *create()
{
    return new ScheduleFCFS;
}
