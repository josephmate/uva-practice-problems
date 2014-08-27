#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BOXES            3
#define MAX_INT 2147483647

//#define DEBUG

struct MoveRes{
	int brownPos;
	int greenPos;
	int clearPos;
	int moves;
};

void find_min_moves(int ** boxes);
MoveRes try_movement(int**boxes, int brownPos, int greenPos, int clearPos);
int count_moves(int**boxes, int colour, int pos);
MoveRes min(MoveRes a, MoveRes b);
void display_res(MoveRes a);
void toString(MoveRes a, char * string);

int main(int argc, const char *argv[])
{
	int i;
	int ** boxes;
	boxes = new int*[BOXES];
	for (i = 0; i < BOXES; i++) {
		boxes[i] = new int[BOXES];
	}

	while (fscanf(stdin, "%d %d %d %d %d %d %d %d %d\n", 
		    &boxes[0][0], &boxes[0][1], &boxes[0][2],
		    &boxes[1][0], &boxes[1][1], &boxes[1][2],
		    &boxes[2][0], &boxes[2][1], &boxes[2][2]
		    )> 0 ) {

		find_min_moves(boxes);	

	}	 

	// cleaning up all things we allocated
	for (i = 0; i < BOXES; i++) {
		delete boxes[i];
	}	 
	
	delete boxes;
	return 0;
}


// brown green clear
void find_min_moves(int ** boxes) {
#ifdef DEBUG
	printf("%d %d %d %d %d %d %d %d %d\n",
			boxes[0][0], boxes[0][1], boxes[0][2],
			boxes[1][0], boxes[1][1], boxes[1][2],
			boxes[2][0], boxes[2][1], boxes[2][2]
			);
#endif

	MoveRes minRes;
	minRes.moves = MAX_INT;
 	minRes = min(minRes, try_movement(boxes, 0, 1, 2));
 	minRes = min(minRes, try_movement(boxes, 0, 2, 1));
 	minRes = min(minRes, try_movement(boxes, 1, 0, 2));
 	minRes = min(minRes, try_movement(boxes, 1, 2, 0));
 	minRes = min(minRes, try_movement(boxes, 2, 0, 1));
 	minRes = min(minRes, try_movement(boxes, 2, 1, 0));

	display_res(minRes);
}



MoveRes try_movement(int**boxes, int brownPos, int greenPos, int clearPos) {
	MoveRes res;
	res.brownPos = brownPos;
	res.greenPos = greenPos;
	res.clearPos = clearPos;
	
	int moves = 0;
	moves += count_moves(boxes, 0, brownPos);
	moves += count_moves(boxes, 1, greenPos);
	moves += count_moves(boxes, 2, clearPos);

	res.moves = moves;
	return res;
}

int count_moves(int**boxes, int colour, int pos) {
	int moves = 0;
	for (int i = 0; i < BOXES; i++) {
		if(i != pos) {
			moves += boxes[i][colour];
		}
	}

	return moves;
}

MoveRes min(MoveRes a, MoveRes b) {
	if(b.moves > a.moves) {
		return a;
	} else	if(b.moves < a.moves) {
		return b;
	} else {
		// alphabetic comparison
		char astr[BOXES+1];
		char bstr[BOXES+1];
		toString(a, astr);
		toString(b, bstr);
		if( strcmp( astr, bstr ) < 0 ) {
			return a;
		} else {
			return b;
		}
	}
}

void display_res(MoveRes a) {
	char posnToColour[BOXES+1];
	
	toString(a, posnToColour);

	printf("%c%c%c %d\n", posnToColour[0],posnToColour[1],posnToColour[2], a.moves);
}


void toString(MoveRes a, char * posnToColour) {
	posnToColour[a.brownPos] = 'B';
	posnToColour[a.greenPos] = 'G';
	posnToColour[a.clearPos] = 'C';
}











