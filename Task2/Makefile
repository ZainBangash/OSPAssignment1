.default: all

all: Task2

clean:
	rm -rf task *.o *.dSYM
	
Task2: Task2.o Functions.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
	g++ -Wall -Werror -std=c++14 -g -O -c ../Functions.cpp

