# Deadlock examples

Source file                    | Description
------------------------------ | -----------
`deadlock-mutex.cpp`           | Deadlock on `pthread_mutex_t`
`deadlock-semaphore.cpp`       | Deadlock on `sem_t` with `sem_init`()
`deadlock-named-semaphore.cpp` | Deadlock on `sem_t *` with `sem_open`()
`livelock-mutex.cpp`           | Livelock on `pthread_mutex_t`
`sync.cpp`                     | Lightweight C++ wrappers around POSIX threads and synchronization constructs
`test.sh`                      | Uses `timeout(1)` to determine if an executable has deadlocked

