
all: a.out

main.o: main.cpp
	g++ -g -O0 -std=c++11 -c main.cpp -o main.o

a.out: main.o
	g++ -g -O0 -std=c++11 main.o


clean:
	rm -f main.o a.out
