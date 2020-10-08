#!/bin/sh

echo Will we deadlock? Mutex edition
for i in $(seq 1 100); do
    timeout 5s ./deadlock-mutex
    if [ $? -eq 124 ]; then
        echo Yes, we deadlocked.
        break
    fi
done

echo Will we deadlock? Semaphore edition
for i in $(seq 1 100); do
    timeout 5s ./deadlock-semaphore
    if [ $? -eq 124 ]; then
        echo Yes, we deadlocked.
        break
    fi
done

echo Will we deadlock? Named semaphore edition
for i in $(seq 1 100); do
    timeout 5s ./deadlock-named-semaphore
    if [ $? -eq 124 ]; then
        echo Yes, we deadlocked.
        break
    fi
done
