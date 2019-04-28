
all: a.out

main.o: main.cpp
	g++ -g -O0 -std=c++11 -c main.cpp -o main.o

maind.o: main.cpp
	g++ -D DEBUG -g -O0 -std=c++11 -c main.cpp -o maind.o

a.out: main.o
	g++ -g -O0 -std=c++11 main.o

d.out: maind.o
	g++ -g -O0 -std=c++11 maind.o -o d.out

test: a.out
	./a < test1.txt > out1.txt

testDebug: d.out
	./d.out < test1.txt > out1.txt

clean:
	rm -f main.o a.out
