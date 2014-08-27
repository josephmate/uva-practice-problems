#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>

using namespace std;

//#define DEBUG

struct State {
	unordered_map<int, int> blockToStack;
	int ** stacks;
	int n;
} ;

void process(State & state, char * action1, char *action2, int a, int b);

void move_pile_helper(State & state, int a, int b, bool pile, bool over) ;

// helpers
int find_stack_height(int * stack, int b) ;
void append_to_stack(int * stack, int value);

void output_map(State & state) ;
void outputStack(int * stack, int n) ;
void output(State & state);


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
	s.stacks = new int*[n];
	s.n = n;
	for (i = 0; i < n; i++) {
		s.stacks[i] = new int[n];
		for (j = 0; j < n; j++) {
			s.stacks[i][j] = -1;
		}
		
		s.blockToStack[i] = i;
		s.stacks[i][0] = i;
	}

	#ifdef DEBUG
	output(s);
	#endif
	while (fscanf(stdin, "%s %d %s %d\n", action1, &a, action2, &b) > 0 && action1[0] != 'q') {
		#ifdef DEBUG
		printf("OOOOOOOOOOOOOOOOOOOOOO\n");
		#endif

		process(s, action1,action2,a,b);	

		#ifdef DEBUG
		output(s);
		#endif
	}	 
	
	#ifndef DEBUG
	output(s);
	#endif

	// cleaning up all things we allocated
	for (i = 0; i < n; i++) {
		delete s.stacks[i];
	}	 
	
	delete s.stacks;
	return 0;
}


void process(State & state, char * action1, char *action2, int a, int b) {
	#ifdef DEBUG
	printf("%s %d %s %d\n", action1, a, action2, b);
	#endif
	if (action1[0] == 'm' && action2[1] == 'n') {
		move_pile_helper(state,a,b, false, false);
	} else if (action1[0] == 'm' && action2[1] == 'v') {
		move_pile_helper(state,a,b, false, true);
	} else if (action1[0] == 'p' && action2[1] == 'n') {
		move_pile_helper(state,a,b, true, false);
	} else if (action1[0] == 'p' && action2[1] == 'v') {
		move_pile_helper(state,a,b, true, true);
	} else {
		printf("unrecongized action\n");
	}
}


void move_pile_helper(State & state, int a, int b, bool pile, bool over) {
	int i;
	// find the stack that b is located in
	int astacknum = state.blockToStack[a];
	int bstacknum = state.blockToStack[b];
	if(astacknum == bstacknum){
		return;
	}
	int * astack = state.stacks[astacknum];
	int * bstack = state.stacks[bstacknum];

	int astackheight = find_stack_height(astack, a);
	int bstackheight = find_stack_height(bstack, b);
	#ifdef DEBUG
	printf("a %d is on %d stack\n", a, astacknum);
	printf("a %d stack height %d\n", a, astackheight);
	printf("b %d is on %d stack\n", b, bstacknum);
	printf("b %d stack height %d\n", b, bstackheight);
	#endif




	// if we're not piling, we need to move all the things above a
	if(!pile) {
		// move everything ontop of a to their original stacks
		for (i = astackheight+1; astack[i] != -1 && i < state.n; i++) {
			int value = astack[i];
			astack[i] = -1;
			append_to_stack(state.stacks[value], value);
			state.blockToStack[value] = value;
		}
	}


	// if we're not placing it over, we're placing it onto b. The means we need to
	// move all the things above b to their original location
	if(!over) {
		for (i = bstackheight+1; bstack[i] != -1 && i < state.n; i++) {
			int value = bstack[i];
			bstack[i] = -1;
			append_to_stack(state.stacks[value], value);
			state.blockToStack[value] = value;
		}
	}

	
	// put a right ontop of b
	int ontopOverPos = 1;
	if(over){
		for (i = bstackheight+1; bstack[i] != -1 && i < state.n; i++) ;
		ontopOverPos = i-bstackheight;
	}
	astack[astackheight] = -1;
	bstack[bstackheight+ontopOverPos] = a;
	state.blockToStack[a] = bstacknum;
	

	// since we're piling, we need to move all of the things above a, to above a's
	// new location
	if(pile){
		// move everything ontop of a, ontop of a's new location
		for (i = 0; astack[astackheight+1+i] != -1 && astackheight+1+i < state.n; i++) {
			int value = astack[astackheight+1+i];
			astack[astackheight+1+i] = -1;
			bstack[bstackheight+ontopOverPos+1+i] = value;
			state.blockToStack[value] = bstacknum;
		}
	}

}

void output_map(State & state) {
	printf("==\n");
	int i;
	for (i = 0; i < state.n; i++) {
		printf("\t%d -> %d\n", i, state.blockToStack[i]);
	}
}

// this function assume the array contains b
int find_stack_height(int * stack, int b) {
	#ifdef DEBUG
	printf("find_stack_height %d:", b); fflush(stdout);
	outputStack(stack, 10);
	#endif
	for(int i = 0; ;i++){
		if(stack[i] == b)
			return i;
	}
}

void append_to_stack(int * stack, int value) {
	int i;
	for (i = 0; stack[i]!=-1; i++);
	stack[i] = value;
}

void outputStack(int * stack, int n) {
	int j;
	for (j = 0; j < n ; j++) {
		#ifndef DEBUG
		if(stack[j] < 0){
			break;
		}
		#endif
		printf(" %d", stack[j]);  fflush(stdout);
	}
	printf("\n");
}

void output(State & state) {
	int i;

	for (i = 0; i < state.n; i++) {
		printf("%d:", i);
		outputStack(state.stacks[i], state.n);
	}
}
