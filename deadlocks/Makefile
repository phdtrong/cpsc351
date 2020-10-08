CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -pthread
TARGETS = deadlock-mutex deadlock-semaphore deadlock-named-semaphore
LDLIBS = -lrt

.PHONY: test check check-leaks check-threads clean

all: $(TARGETS)

deadlock-mutex: deadlock-mutex.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

deadlock-semaphore: deadlock-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

deadlock-named-semaphore: deadlock-named-semaphore.o sync.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TARGETS)
	./test.sh

clean:
	rm -f *.o $(TARGETS)
