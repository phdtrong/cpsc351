#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

#include <sys/stat.h>
#include <pthread.h>

#include "sync.h"


void Thread::create(void *(*routine)(void *))
{
    errno = pthread_create(&tid, NULL, routine, NULL);
    if (errno != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
}

void Thread::join()
{
    errno = pthread_join(tid, NULL);
    if (errno != 0) {
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
}


Mutex::Mutex()
{
    errno = pthread_mutex_init(&mutex, NULL);
    if (errno != 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }
}

Mutex::~Mutex()
{
    errno = pthread_mutex_destroy(&mutex);
    if (errno != 0) {
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }
}

void Mutex::lock()
{
    errno = pthread_mutex_lock(&mutex);
    if (errno != 0) {
        perror("pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}

void Mutex::unlock()
{
    errno = pthread_mutex_unlock(&mutex);
    if (errno != 0) {
        perror("pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}


Semaphore::Semaphore(int value)
{
    auto ok = sem_init(&sem, 0, value);
    if (ok < 0) {
        perror("sem_init");
        exit(EXIT_FAILURE);
    }
}

Semaphore::~Semaphore()
{
    auto ok = sem_destroy(&sem);
    if (ok < 0) {
        perror("sem_destroy");
        exit(EXIT_FAILURE);
    }
}

void Semaphore::wait()
{
    auto ok = sem_wait(&sem);
    if (ok < 0) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
}

void Semaphore::post()
{
    auto ok = sem_post(&sem);
    if (ok < 0) {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
}


NamedSemaphore::NamedSemaphore(std::string name, int oflag, mode_t mode, int value)
{
    psem = sem_open(name.c_str(), oflag, mode, value);
    if (psem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
}

NamedSemaphore::~NamedSemaphore()
{
    auto ok = sem_close(psem);
    if (ok < 0) {
        perror("sem_destroy");
        exit(EXIT_FAILURE);
    }
}

void NamedSemaphore::wait()
{
    auto ok = sem_wait(psem);
    if (ok < 0) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
}

void NamedSemaphore::post()
{
    auto ok = sem_post(psem);
    if (ok < 0) {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
}
