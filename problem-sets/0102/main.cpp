#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>

using namespace std;

#define DEBUG


void find_min_movements(int ** boxes);

int main(int argc, const char *argv[])
{
	int i;
	int ** boxes;
	boxes = new int*[3];
	for (i = 0; i < 3; i++) {
		boxes[i] = new int[3];
	}

	while (fscanf(stdin, "%d %d %d %d %d %d %d %d %d\n", 
		    &boxes[0][0], &boxes[0][1], &boxes[0][2],
		    &boxes[1][0], &boxes[1][1], &boxes[1][2],
		    &boxes[2][0], &boxes[2][1], &boxes[2][2]
		    )> 0 ) {

		find_min_movements(boxes);	

	}	 
	
	#ifndef DEBUG
	output(s);
	#endif

	// cleaning up all things we allocated
	for (i = 0; i < 3; i++) {
		delete boxes[i];
	}	 
	
	delete boxes;
	return 0;
}


void find_min_movements(int ** boxes) {
	printf("%d %d %d %d %d %d %d %d %d\n",
			boxes[0][0], boxes[0][1], boxes[0][2],
			boxes[1][0], boxes[1][1], boxes[1][2],
			boxes[2][0], boxes[2][1], boxes[2][2]
			);
}
