#include <cstdlib>
#include <iostream>
#include <tuple>

#include "sync.h"

using std::cout;
using std::endl;
using std::ignore;

Mutex first_mutex;
Mutex second_mutex;

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

    auto done = false;
    while (!done) {
        first_mutex.lock();

        if (second_mutex.trylock()) {
            cout << "do_work_1()" << endl;

            second_mutex.unlock();
            first_mutex.unlock();

            done = true;
        } else {
            first_mutex.unlock();
        }
    }

    pthread_exit(NULL);
}

void *do_work_2(void *param)
{
    ignore = param;

    auto done = false;
    while (!done) {
        second_mutex.lock();

        if (first_mutex.trylock()) {
            cout << "do_work_2()" << endl;

            first_mutex.unlock();
            second_mutex.unlock();

            done = true;
        } else {
            first_mutex.unlock();
        }
    }

    pthread_exit(NULL);
}
