CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -pthread

.PHONY: clean

example: client.o threadpool.o
	$(CXX) $(CXXFLAGS) -o example $^

clean:
	rm -f *.o example
