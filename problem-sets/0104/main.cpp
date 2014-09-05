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
void solve_exrates(double ** exrates, int d);

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

void solve_exrates(double ** exrates, int d) {
#ifdef DEBUG
	debug_exrates(exrates,d);
#endif
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
