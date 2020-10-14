# Deadlock examples

Source file                    | Description
------------------------------ | -----------
`deadlock-mutex.cpp`           | Deadlock on `pthread_mutex_t`
`deadlock-semaphore.cpp`       | Deadlock on `sem_t` with `sem_init`()
`deadlock-named-semaphore.cpp` | Deadlock on `sem_t *` with `sem_open`()
`livelock-mutex.cpp`           | Livelock on `pthread_mutex_t`
`sync.cpp`                     | Lightweight C++ wrappers around POSIX threads and synchronization constructs
`try.sh`                       | Use `timeout(1)` to see if an executable will hang

