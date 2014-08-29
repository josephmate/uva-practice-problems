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
map<Box*,int,cmp> sort_boxes(Box ** boxes, int n, int d);
void sort_box(Box * box, int d) ;

#ifdef DEBUG
void debug_boxes(map<Box*,int,cmp> boxes, int n, int d) ;
void debug_boxes(Box ** boxes, int n, int d);
void debug_box(Box * box, int d) ;
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
}


map<Box*,int,cmp> sort_boxes(Box ** boxes, int n, int d) {
	for (int i = 0; i < n; i++) {
		sort_box(boxes[i], d);
	}
	
	map<Box*, int,cmp> sortedBoxes;
	for (int i = 0; i < n; i++) {
		sortedBoxes[boxes[i]] = i+1;
	}

	return sortedBoxes;
}

void sort_box(Box * box, int d) {
	int i;
	set<int> sortedBox;
	for (i = 0; i < d; i++) {
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
		debug_box(itr->first, d);
		printf("\n");
	} 
}

void debug_boxes(Box ** boxes, int n, int d) {
	printf("AoAoA\n");
	for(int i = 0 ; i < n; i++) {
			printf("%d:", (i+1));
		debug_box(boxes[i], d);
		printf("\n");
	}
}

void debug_box(Box * box, int d) {
	for(int j = 0 ; j < d; j++) {
		printf("\t%d", box->box[j]);
	}
}
