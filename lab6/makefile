CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wextra -Wall -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp
NAME = solution

all: main.o

main.o:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

benchmark1: benchmark1.o
	$(CXX) $(CXXFLAGS) benchmark1.o -o $@ -lgmpxx -lgmp

benchmark2: benchmark2.o
	$(CXX) $(CXXFLAGS) benchmark2.o -o $@ -lgmpxx -lgmp

benchmark1.o: benchmark1.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lgmpxx -lgmp

benchmark2.o: benchmark2.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lgmpxx -lgmp

clean:
	rm -f *.o $(NAME)