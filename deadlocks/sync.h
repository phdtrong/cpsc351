#ifndef SYNC_H
#define SYNC_H

#include <semaphore.h>

#include <sys/stat.h>

const auto DEFAULT_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

class Thread {
    public:
        void create(void *(*thread)(void *));
        void join();
    private:
        pthread_t tid;
};

class Mutex {
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();

    private:
        pthread_mutex_t mutex;
};

class Semaphore {
    public:
        Semaphore(int = 1);
        ~Semaphore();
        void wait();
        void post();

    private:
        sem_t sem;
};

class NamedSemaphore {
    public:
        NamedSemaphore(std::string, int, mode_t = DEFAULT_MODE, int = 1);
        ~NamedSemaphore();
        void wait();
        void post();

    private:
        sem_t *psem;
        std::string name;
};

#endif
