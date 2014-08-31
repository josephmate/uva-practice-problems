#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

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

typedef struct Memo Memo;
typedef struct keyhasher keyhasher;
void solve_nest_boxes(Box ** boxes, int n, int d);
vector<int>* find_longest_chain(Box ** boxes, int n, int d) ;
vector<int>* search(bool ** adjmat, int n) ;
bool fits(Box* a, Box* b);
void sort_boxes(Box ** boxes, int n, int d);
void sort_box(Box * box) ;

#ifdef DEBUG
void debug_memos(unordered_map<Memo, vector<int>*, keyhasher> * memos) ;
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
	debug_adjmat(adjmat,n);
#endif

	vector<int>* result = search(adjmat, n);

	for (int i = 0; i < n; i++) {
		delete [] adjmat[i];
	}
	delete [] adjmat;

	return result;
}

struct Memo {
	vector<int> visitorder;

	Memo(vector<int>  v) {
		visitorder = v;
	}

	bool operator==(const Memo &other) const {
		if(this->visitorder.size() != other.visitorder.size()) {
			return false;
		}

		vector<int>::const_iterator itrA = this->visitorder.begin();
		vector<int>::const_iterator itrB = other.visitorder.begin();
		while(itrA != this->visitorder.end() ) {
			if(*itrA != *itrB){
				return false;
			}

			itrA++;
			itrB++;
		}

		return true;

	}
};

struct keyhasher {
	std::size_t operator()(const Memo& k) const {
		size_t ret = 0;

		for(vector<int>::const_iterator itr = k.visitorder.begin(); itr != k.visitorder.end(); itr++) {
			ret = ret << 1;
			ret += *itr;
		}

		return ret;
	}
};


vector<int>* search_impl(
		bool ** adjmat, 
		int n,
		unordered_map<Memo, vector<int>*, keyhasher> * memos,
		Memo memo, // the order in which we visited matters for the memoization
		set<int> * visited, 
		int current,
		int depth) {
#ifdef DEBUG
	printf("Memos so far\n");
	debug_memos(memos);
#endif
	
	if(memos->count(memo) > 0) {
#ifdef DEBUG
		printf("CACHED\n");
#endif
		return memos->find(memo)->second;
	}


	int max = 0;
	vector<int> * best = NULL;

	// try each of the directions
	for (int i = 0; i < n; i++) {
		if(visited->find(i) == visited->end() && adjmat[i][current]) {
			visited->insert(i);
			Memo newmemo(memo.visitorder);
			newmemo.visitorder.push_back(i);
			vector<int> * attempt = search_impl(adjmat, n, memos, newmemo, visited, i, depth + 1);
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

	(*memos)[memo] = best;
	return best;
}

// graph search
vector<int>* search(bool ** adjmat, int n) {
	unordered_map<Memo, vector<int>*, keyhasher> * memos = new unordered_map<Memo, vector<int>*, keyhasher>();
	unsigned int max = 0;
	vector<int> * best;

	for (int i = 0; i < n; i++) {
		set<int> visited; visited.insert(i);

		vector<int> visitorder; visitorder.push_back(i);
		Memo memo(visitorder);

		vector<int>* attempt = search_impl(adjmat, n, memos, memo, &visited, i, 1);

		if(attempt->size() > max) {
			best = attempt;
			max = attempt->size();
		}
	}

	return best;
}



bool fits(Box* a, Box* b) {
	for (int i = 0; i < a->d; i++) {
		if(a->box[i] > b->box[i]) {
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
void debug_memos(unordered_map<Memo, vector<int>*, keyhasher> * memos) {
	unordered_map<Memo, vector<int>*, keyhasher>::const_iterator itr;
	for( itr = memos->begin(); itr != memos->end(); itr++) {
		debug_vector( &itr->first.visitorder);
		printf(" --> ");
		debug_vector(itr->second);
		printf("\n");
	}

}

void debug_vector(const vector<int> * vs) {
	for(vector<int>::const_iterator itr = vs->begin(); itr != vs->end(); itr++) {
		printf("%d\t", *itr);
	}
}

void debug_adjmat(bool ** adjmat, int n) {
	for(int i = 0 ; i < n; i++) {
		for(int j = 0 ; j < n; j++) {
			printf("%d\t", (int)adjmat[i][j]);
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
