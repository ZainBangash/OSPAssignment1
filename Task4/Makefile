.default: all

all: Task4

clean:
	rm -rf task *.o *.dSYM
	
Task4: Task4.o Functions.o
	g++ -Wall -Werror -pthread -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
	g++ -Wall -Werror -std=c++14 -g -O -c ../Functions.cpp