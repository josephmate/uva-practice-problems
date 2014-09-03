#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

//#define DEBUG

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

void solve_nest_boxes(Box ** boxes, int n, int d);
void remove_transitive_edges(bool ** adjmat,int n);
vector<int>* find_longest_chain(Box ** boxes, int n, int d) ;
vector<int>* search(bool ** adjmat, int n) ;
bool fits(Box* a, Box* b);
void sort_boxes(Box ** boxes, int n, int d);
void sort_box(Box * box) ;

#ifdef DEBUG
void debug_vector(const vector<int> * vs) ;
void debug_adjmat(bool ** adjmat, int n);
void debug_boxes(Box ** boxes, int n, int d);
void debug_box(Box * box) ;
#endif

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
	sort_boxes(boxes,n,d);

#ifdef DEBUG
	debug_boxes(boxes, n, d);
#endif

	vector<int>* longestChain = find_longest_chain(boxes, n, d);

	// output the longest chain that we found
	printf("%lu\n", longestChain->size());
	for (vector<int>::iterator itr = longestChain->begin() ; itr != longestChain->end(); ++itr){
		if(itr != longestChain->begin()) {
			printf(" ");
		}
		printf("%d", (*itr) + 1);
	}
	printf("\n");
	
	delete longestChain;
}

// find the longest chain of boxes that fit
vector<int>* find_longest_chain(Box ** boxes, int n, int d) {
	bool ** adjmat = new bool*[n];
	for (int i = 0; i < n; i++) {
		adjmat[i] = new bool[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adjmat[i][j] = fits(boxes[i],boxes[j]);
		}
	}
#ifdef DEBUG 
	printf("--------------------\n");
	debug_adjmat(adjmat,n);
#endif

	// Primary difficult with this problem is that there are SO many edges. One
	// way to describe the number of edges is considering the transitive property
	// of fits. If a fits b and b fits in c then a fits in c. As a result, there's
	// an explosion in the number of edges!
	//
	// The only way to deal with this problem is to remove those extra edges.
	/*
	remove_transitive_edges(adjmat,n);

#ifdef DEBUG 
	printf("--------------------\n");
	debug_adjmat(adjmat,n);
#endif
	*/

	vector<int>* result = search(adjmat, n);

	for (int i = 0; i < n; i++) {
		delete [] adjmat[i];
	}
	delete [] adjmat;

	return result;
}

// 1) if depth is >= 2
//   a) remove startnode <- currentnode from adjmat
// 2) recursively follow edges backwards
void remove_transitive_edges_impl(
		bool ** adjmat,
		int n, 
		set<int> * visited, 
		int startnode,
		int currentnode, 
		int depth) {

	// remove transient edge
	if(depth >= 2) {
		adjmat[currentnode][startnode] = false;
	}

	// keep traversing dag tree 
	for (int i = 0; i < n; i++) {
		if(visited->find(i) == visited->end() && adjmat[i][currentnode]) {
			visited->insert(i);

			remove_transitive_edges_impl(adjmat, n, visited, startnode, i, depth+1);

			visited->erase(i);
		}
	}
}

// We remove transiant edges by traversing the graph structure. Any node that we
// hopped to by following at least two edges transiantly fits into the node we
// started from.
void remove_transitive_edges(bool ** adjmat,int n) {
	// iterative over all starting nodes
	for (int i = 0; i < n; i++) {
		set<int> visited; visited.insert(i);
		remove_transitive_edges_impl(adjmat, n, &visited, i, i, 0);
	}
}




vector<int>* search_impl(
		bool ** adjmat, 
		int n,
		set<int> * visited, 
		int current,
		int depth) {

	int max = 0;
	vector<int> * best = NULL;

	// try each of the directions
	for (int i = 0; i < n; i++) {
		if(visited->find(i) == visited->end() && adjmat[i][current]) {
			visited->insert(i);
			vector<int> * attempt = search_impl(adjmat, n, visited, i, depth + 1);
			if(attempt->size() > max) {
				best = attempt;
				max = attempt->size();
			}
			visited->erase(i);
		}
	}
	
	if(best == NULL) {
		best = new vector<int>();
	}	
	best->push_back(current);

	return best;
}

bool isroot(bool ** adjmat, int n, int i) {
	int sum = 0;
	for (int j = 0; j < n; j++) {
		if(adjmat[i][j]) {
			sum++;
		}
	}

#ifdef DEBUG
	printf("isroot %d: %d\n", (i+1), sum);
#endif

	return sum == 0;
}

// graph search
vector<int>* search(bool ** adjmat, int n) {
	unsigned int max = 0;
	vector<int> * best;

	for (int i = 0; i < n; i++) {
		if(isroot(adjmat, n, i)) {
			set<int> visited; visited.insert(i);

			vector<int>* attempt = search_impl(adjmat, n, &visited, i, 1);

			if(attempt->size() > max) {
				best = attempt;
				max = attempt->size();
			}
		}
	}

	return best;
}


// assumes the dimensions of the boxes are sorted
// 
// box a fits in box b iff a_i < b_i for all i:[1,d]
bool fits(Box* a, Box* b) {
	for (int i = 0; i < a->d; i++) {
		if(a->box[i] >= b->box[i]) {
			return false;
		}
	}

	return true;
}

void sort_boxes(Box ** boxes, int n, int d) {
	for (int i = 0; i < n; i++) {
		sort_box(boxes[i]);
	}
}

void sort_box(Box * box) {
	int i;
	set<int> sortedBox;
	for (i = 0; i < box->d; i++) {
		sortedBox.insert(box->box[i]);
	}

	i = box->d-1;
	for(set<int>::iterator itr = sortedBox.begin(); itr != sortedBox.end(); itr++) {
		box->box[i] = *itr;
		i--;
	}
}


#ifdef DEBUG
void debug_vector(const vector<int> * vs) {
	for(vector<int>::const_iterator itr = vs->begin(); itr != vs->end(); itr++) {
		printf("%d\t", *itr);
	}
}

void debug_adjmat(bool ** adjmat, int n) {
	for(int i = 0 ; i < n; i++) {
		for(int j = 0 ; j < n; j++) {
			printf("%d ", (int)adjmat[i][j]);
		}
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
#endif
