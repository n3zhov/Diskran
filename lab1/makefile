CXX = g++
CXXFLAGS = -std=c++14 -O3 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
FILES = main.cpp
NAME = solution

all: main.o

main.o:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(FILES)

clean:
	rm -f *.o $(NAME)

