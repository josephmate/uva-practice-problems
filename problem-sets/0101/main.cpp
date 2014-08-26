#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>

using namespace std;


struct State {
	unordered_map<int, int> blockToStack;
	int * stacks;
	int n;
} ;

void process(State state, char * action1, char *action2, int a, int b);

void output(State state);

void set(int * array, int cols, int r, int c, int value);

int get(int * array, int cols, int r, int c);

int main(int argc, const char *argv[])
{
	char action1[5];
	char action2[5];
	int n, a, b;
	int i,j;

	// read in how many stacks and blocks we have
	fscanf(stdin, "%d\n", &n);

	// initialize data structures
	State s;
	// C++ doesn't allow 2d arrays :(
	s.stacks = new int[n*n];
	s.n = n;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			set(s.stacks,n,i,j,-1) ;
		}
		
		s.blockToStack[i] = i;
		set(s.stacks,n,i,0,i) ;
	}

	while (fscanf(stdin, "%s %d %s %d\n", action1, &a, action2, &b) > 0) {
		process(s, action1,action2,a,b);	
	}	 
	
	output(s);

	// cleaning up all things we allocated
	for (i = 0; i < n; i++) {
		//delete s.stacks[i];
	}	 
	
	delete s.stacks;
	return 0;
}


void set(int * array, int cols, int r, int c, int value){
	array[ r*cols + c ] = value;
}

int get(int * array, int cols, int r, int c){
	return array[ r*cols + c ];
}

void process(State state, char * action1, char *action2, int a, int b) {

}

void output(State state) {
	int i;
	int j;

	for (i = 0; i < state.n; i++) {
		printf("%d:", i);
		
		for (j = 0; j < state.n && get(state.stacks,state.n, i,j) >= 0 ; j++) {
			printf(" %d", get(state.stacks, state.n, i,j));
		}

		printf("\n");
	}
}
