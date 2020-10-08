#include <cstdlib>
#include <iostream>
#include <tuple>

#include "sync.h"

using std::cout;
using std::endl;
using std::ignore;

Semaphore first_mutex;
Semaphore second_mutex;

void *do_work_1(void *);
void *do_work_2(void *);

int main()
{
    Thread t1, t2;
    t1.create(do_work_1);
    t2.create(do_work_2);

    t1.join();
    t2.join();

    return EXIT_SUCCESS;
}

void *do_work_1(void *param)
{
    ignore = param;

    first_mutex.wait();
    second_mutex.wait();

    cout << "do_work_1()" << endl;

    second_mutex.post();
    first_mutex.post();

    pthread_exit(NULL);
}

void *do_work_2(void *param)
{
    ignore = param;

    second_mutex.wait();
    first_mutex.wait();

    cout << "do_work_2()" << endl;

    first_mutex.post();
    second_mutex.post();

    pthread_exit(NULL);
}
