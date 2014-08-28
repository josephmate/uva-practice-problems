#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <map>

using namespace std;

#define DEBUG

void solve_nest_boxes(int ** boxes, int n, int d);

#ifdef DEBUG
void debug_boxes(int ** boxes, int n, int d);
#endif

int main(int argc, const char *argv[])
{
	int numOfBoxes, dimension;

	// read in how many stacks and blocks we have
	while(scanf("%d %d\n", &numOfBoxes, &dimension) > 0) {
		

		//init variables
		int ** boxes = new int*[numOfBoxes];
		for (int i = 0; i < numOfBoxes; i++) {
			boxes[i] = new int[dimension];
		}
		
		//copy data into variables
		for (int i = 0; i < numOfBoxes; i++) {
			for(int j = 0; j < dimension; j++) {
				scanf("%d", &boxes[i][j]);
			}
			scanf("\n");
		}

		solve_nest_boxes(boxes, numOfBoxes, dimension);

		// free stuff we allocated
		for (int i = 0; i < numOfBoxes; i++) {
			delete boxes[i];
		}
		delete boxes;
#ifdef DEBUG
		printf("=====================\n");
#endif
	}
	
	return 0;
}


void solve_nest_boxes(int ** boxes, int n, int d) {
	debug_boxes(boxes, n, d);
}

void debug_boxes(int ** boxes, int n, int d) {
	for(int i = 0 ; i < n; i++) {
			printf("%d:", (i+1));
		for(int j = 0 ; j < d; j++) {
			printf("\t%d", boxes[i][j]);
		}
		printf("\n");
	}
}

