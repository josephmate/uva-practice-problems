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
void solve_exrates(double ** exrates, int dimension);
vector<int> convertBinaryToPath(int binaryDigit, int dimension);
double calcValueOfPath(double ** exrates, int dimension, vector<int> path);

#ifdef DEBUG
void debug_exrates(double ** exrates, int d);
#endif

int main(int argc, const char *argv[])
{
	int dimension;

	// read in how many stacks and blocks we have
	while(scanf("%d\n", &dimension) > 0) {

		//init variables
		double ** exrates = new double*[dimension];
		for (int i = 0; i < dimension; i++) {
			exrates[i] = new double[dimension];
		}
		
		//copy data into variables
		for (int i = 0; i < dimension; i++) {
			for(int j = 0; j < dimension; j++) {
				if(i == j){
					exrates[i][j] = 1.0;
				} else {
					scanf("%lf", &exrates[i][j]);
				}
			}
			scanf("\n");
		}

		solve_exrates(exrates, dimension);


		// free stuff we allocated
		for (int i = 0; i < dimension; i++) {
			delete [] exrates[i];
		}
		delete [] exrates;
#ifdef DEBUG
		printf("=====================\n");
#endif
	}
	
	return 0;
}

void solve_exrates(double ** exrates, int dimension) {
	// 2^(dimension+1) - 1
	// implemented using bit shift
	int possiblePaths = (1<<(dimension))-1;
#ifdef DEBUG
	debug_exrates(exrates, dimension);
	printf("possiblePaths: %d\n", possiblePaths);
#endif
	// First thing to recognize is that the order in which you traverse the exchanges does not matter.
	// The order does not matter because each exchange is a multiplication.
	// Ex: a * b * c = c * b * a
	// As a result, we can enumerate all possible exchange paths as a binary number.
	// 0 means we did not visit that exchange.
	// 1 means we visited that exchange.
	// This would take d digits
	// In the largest possible input, that's a 20 digit binary number
	// 2^21-1 = 2,097,151 possible exchange paths
	// that not that big to brute force.
	// In total, we would do 20*2,097,151=41,943,020 multiplications to explore all possible exchange paths.
	/////////////////////////////////////////////////////
	// THIS ASSUMPTION WAS INCORRECT!!!
	// It's true that the order of the mutliplication does not matter. However, the order in which you visit
	// the nodes matters because each edge has a different exchange rate. As a result, I have to consider all
	// possible paths some how. I hope that this can reduce to shortest path some how. Otherwise I'm not sure
	// how to solve it.
	/////////////////////////////////////////////////////
	for(int i = 1; i <= possiblePaths; i++) {
		vector<int> pathToTry = convertBinaryToPath(i, dimension);
		double valueOfPath = calcValueOfPath(exrates, dimension, pathToTry);
#ifdef DEBUG
		printf("value: %lf\n", valueOfPath);
#endif
	}
}

vector<int> convertBinaryToPath(int binaryDigit, int dimension){
	vector<int> path;
	for(int i = 0; i < dimension; i++) {
		if(binaryDigit & 1 == 1){
			path.push_back(i);
		}
		binaryDigit = binaryDigit >> 1;
	}
#ifdef DEBUG
	printf("path: ");
	for(int i = 0; i < path.size(); i++) {
		printf("%d, ",path.at(i));
	}
	printf("\n");
#endif
	return path;
}

double calcValueOfPath(double ** exrates, int dimension, vector<int> path) {
	double value = 1.0;
	for(int i = 1; i < path.size(); i++) {
		int start = path.at(i-1);
		int end = path.at(i);
		value = value * exrates[start][end];
	}
	int start = path.at(end)
	return value;
}

#ifdef DEBUG
void debug_exrates(double ** exrates, int d) {
		for (int i = 0; i < d; i++) {
			for(int j = 0; j < d; j++) {
				printf("%lf\t", exrates[i][j]);
			}
			printf("\n");
		}

}

#endif
