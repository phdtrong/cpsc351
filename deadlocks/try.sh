#!/bin/sh

if [ $# -lt 1 ]; then
    echo "Usage: $0 EXECUTABLE [TIMES]"
    exit 1
fi

executable="$1"

if [ $# -lt 2 ]; then
    times=100
else
    times="$2"
fi

echo "Will we hang? Trying $executable $times times."
for i in $(seq 1 "$times"); do
    timeout 5s "$executable" > /dev/null
    if [ $? -eq 124 ]; then
        echo "Hung on try $i."
        exit
    fi
done

echo Apparently not.
