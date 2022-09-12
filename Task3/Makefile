.default: all

all: Task3

clean:
	rm -rf task *.o *.dSYM
	
Task3: Task3.o Functions.o
	g++ -Wall -Werror -pthread -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
	g++ -Wall -Werror -std=c++14 -g -O -c ../Functions.cpp