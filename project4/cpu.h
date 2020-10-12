#ifndef CPU_H_
#define CPU_H_

#include "task.h"

class CPU {
    public:
        // length of a time quantum
        static const auto QUANTUM = 10;

        // run the specified task for the following time slice
        void run(Task *, int);
};

#endif
