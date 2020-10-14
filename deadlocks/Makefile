CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -pthread
TARGETS = deadlock-mutex deadlock-semaphore deadlock-named-semaphore livelock-mutex

.PHONY: clean

all: $(TARGETS)

deadlock-mutex: deadlock-mutex.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-deadlock-mutex: deadlock-mutex
	./try.sh ./deadlock-mutex

deadlock-semaphore: deadlock-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-deadlock-semaphore: deadlock-semaphore
	./try.sh ./deadlock-semaphore

deadlock-named-semaphore: deadlock-named-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-deadlock-named-semaphore: deadlock-named-semaphore
	./try.sh ./deadlock-named-semaphore

livelock-mutex: livelock-mutex.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test-livelock-mutex: livelock-mutex
	./try.sh ./livelock-mutex

sync.o: sync.cpp sync.h
	$(CXX) $(CXXFLAGS) -c $<

test: test-deadlock-mutex test-deadlock-semaphore test-deadlock-named-semaphore livelock-mutex

clean:
	rm -f *.o $(TARGETS)
