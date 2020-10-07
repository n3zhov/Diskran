CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp
NAME = solution

all: main.o

main.o:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

benchmark: benchmark.o
	$(CXX) $(CXXFLAGS) benchmark.o -o $@

benchmark.o: benchmark.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(NAME)

