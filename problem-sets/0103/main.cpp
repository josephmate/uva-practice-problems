#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <set>

using namespace std;

#define DEBUG

struct Box {

	int * box;
	int d;

	Box(int d) {
		this->d = d;
		box = new int[d];
	}

	~Box(){
		delete [] box;
	}


};


typedef struct cmp cmp;
void solve_nest_boxes(Box ** boxes, int n, int d);
void find_longest_chain(map<Box*,int,cmp> boxes, int d, int * longestLen, int * longestStartPosn) ;
bool fits(Box* a, Box* b);
map<Box*,int,cmp> sort_boxes(Box ** boxes, int n, int d);
void sort_box(Box * box) ;

#ifdef DEBUG
void debug_boxes(map<Box*,int,cmp> boxes, int n, int d) ;
void debug_boxes(Box ** boxes, int n, int d);
void debug_box(Box * box) ;
#endif

struct cmp {
	bool operator()(Box* const& a, Box* const& b) const {
		for(int i = 0; i < a->d; i++) {
			if(a->box[i] < b->box[i]) {
				return true; // a < b
			} else if(a->box[i] > b->box[i]) {
				return false; // b < a
			}
		}
		return false; // equal
	}
};


int main(int argc, const char *argv[]) {
	int numOfBoxes, dimension;

	// read in how many stacks and blocks we have
	while(scanf("%d %d\n", &numOfBoxes, &dimension) > 0) {
		

		//init variables
		Box ** boxes = new Box*[numOfBoxes];
		for (int i = 0; i < numOfBoxes; i++) {
			boxes[i] = new Box(dimension);
		}
		
		//copy data into variables
		for (int i = 0; i < numOfBoxes; i++) {
			for(int j = 0; j < dimension; j++) {
				scanf("%d", &boxes[i]->box[j]);
			}
			scanf("\n");
		}

		solve_nest_boxes(boxes, numOfBoxes, dimension);

		// free stuff we allocated
		for (int i = 0; i < numOfBoxes; i++) {
			delete boxes[i];
		}
		delete [] boxes;
#ifdef DEBUG
		printf("=====================\n");
#endif
	}
	
	return 0;
}


void solve_nest_boxes(Box ** boxes, int n, int d) {
#ifdef DEBUG
	debug_boxes(boxes, n, d);
#endif

	// i'm assuming that the fit IFF their sorted dimensions fit (without moving)
	map<Box*,int,cmp> sortedBoxes = sort_boxes(boxes,n,d);

#ifdef DEBUG
	debug_boxes(boxes, n, d);
	debug_boxes(sortedBoxes, n, d);
#endif

	int length = 0;
	int startPosn = -1;
	find_longest_chain(sortedBoxes, d, &length, &startPosn) ;
#ifdef DEBUG
	printf("longest chain length: %d\n", length);
	printf("start posn of chain: %d\n", startPosn);
#endif


	// output the longest chain that we found
	

}

// find the longest chain of boxes that fit
void find_longest_chain(map<Box*,int,cmp> boxes, int d, int * longestLen, int * longestStartPosn) {
	*longestLen = 0;
	*longestStartPosn = -1;
	int currentLen = 0;
	int i = 0;
	int posn = 0;
	Box* prev = NULL;

	for(map<Box*,int,cmp>::iterator itr = boxes.begin(); itr != boxes.end(); itr++) {

		if(prev == NULL) {
			posn = 0;
			currentLen = 1;
#ifdef DEBUG
			printf("i %d, origPosn %d, start %d, currentLen %d, START ", i, itr->second, posn, currentLen);
			debug_box(itr->first);
			printf("\n");
#endif
		} else if(fits(prev,itr->first)) {
#ifdef DEBUG
			printf("i %d, origPosn %d, start %d, currentLen %d, FITS  ", i, itr->second, posn, currentLen);
			debug_box(itr->first);
			printf("\n");
#endif
			currentLen++;
		} else {
#ifdef DEBUG
			printf("i %d, origPosn %d, start %d, currentLen %d, START ", i, itr->second, posn, currentLen);
			debug_box(itr->first);
			printf("\n");
#endif
			// The previous box did not fit.
			//
			// We check if the previous chain is longer than the longest chain so far.
			//
			// As a result, we reset the the counters
			// and have this guy as the starting posn.
			
			if(currentLen > *longestLen) {
				*longestLen = currentLen;
				*longestStartPosn = posn;
			}

			posn = i;
			currentLen = 1;
		}
		
		i++;
		prev = itr->first;
	}
	if(currentLen > *longestLen) {
		*longestLen = currentLen;
		*longestStartPosn = posn;
	}
}

bool fits(Box* a, Box* b) {
	for (int i = 0; i < a->d; i++) {
		if(a->box[i] > b->box[i]) {
			return false;
		}
	}

	return true;
}

map<Box*,int,cmp> sort_boxes(Box ** boxes, int n, int d) {
	for (int i = 0; i < n; i++) {
		sort_box(boxes[i]);
	}
	
	map<Box*, int,cmp> sortedBoxes;
	for (int i = 0; i < n; i++) {
		sortedBoxes[boxes[i]] = i+1;
	}

	return sortedBoxes;
}

void sort_box(Box * box) {
	int i;
	set<int> sortedBox;
	for (i = 0; i < box->d; i++) {
		sortedBox.insert(box->box[i]);
	}

	i = 0;
	for(set<int>::iterator itr = sortedBox.begin(); itr != sortedBox.end(); itr++) {
		box->box[i] = *itr;
		i++;
	}
}


void debug_boxes(map<Box*,int,cmp> boxes, int n, int d) {
	printf("AoAoA\n");
	for(map<Box*,int,cmp>::iterator itr = boxes.begin(); itr != boxes.end(); itr++) {
		printf("%d:", itr->second);
		debug_box(itr->first);
		printf("\n");
	} 
}

void debug_boxes(Box ** boxes, int n, int d) {
	printf("AoAoA\n");
	for(int i = 0 ; i < n; i++) {
			printf("%d:", (i+1));
		debug_box(boxes[i]);
		printf("\n");
	}
}

void debug_box(Box * box) {
	for(int j = 0 ; j < box->d; j++) {
		printf("\t%d", box->box[j]);
	}
}
