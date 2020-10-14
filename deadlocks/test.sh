#!/bin/sh
executable="$1"

echo Will we lock up?
for i in $(seq 1 100); do
    timeout 5s "./$executable" > /dev/null
    if [ $? -eq 124 ]; then
        echo Hung on try "$i".
        exit
    fi
done

echo Apparently not.
