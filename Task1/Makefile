.default: all

all: Task1 

clean:
	rm -rf task *.o *.dSYM
	
Task1: Task1Filter.o ./Functions.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
	g++ -Wall -Werror -std=c++14 -g -O -c ../Functions.cpp


