CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -pthread
TARGETS = deadlock-mutex deadlock-semaphore deadlock-named-semaphore livelock-mutex

.PHONY: clean

all: $(TARGETS)

deadlock-mutex: deadlock-mutex.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

deadlock-semaphore: deadlock-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

deadlock-named-semaphore: deadlock-named-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

livelock-mutex: livelock-mutex.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

sync.o: sync.cpp sync.h
	$(CXX) $(CXXFLAGS) -c $<

test: $(TARGETS)
	./test.sh ./deadlock-mutex
	./test.sh ./deadlock-semaphore
	./test.sh ./deadlock-named-semaphore
	./test.sh ./livelock-mutex

clean:
	rm -f *.o $(TARGETS)
