
all: a.out

main.o: main.cpp
	clang++ -c main.cpp -o main.o

a.out: main.o
	clang++ main.o


clean:
	rm -f main.o a.out
