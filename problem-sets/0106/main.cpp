#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct Pair {
	int a;
	int b;
};
Pair solve(int n);
void printResult(Pair);
bool* calcIsPrimeArray();
vector<int>* getPrimes(bool*);



int main(int argc, const char *argv[])
{
	bool* isPrime = calcIsPrimeArray();
#ifdef DEBUG
	for(int i = 0; i < 1001; i++) {
		printf("%d %s\n", i, (isPrime[i])?"true":"false");
	}
#endif
	vector<int>* primes = getPrimes(isPrime);
#ifdef DEBUG
	for(int i = 0; i < primes->size(); i++) {
		printf("prime %d\n", primes->at(i));
	}
#endif

	int n;
	while (fscanf(stdin, "%d\n", &n)> 0) {
#ifdef DEBUG
		printf("%d\n", n);
#endif
		Pair pair = solve(n);
		printResult(pair);
	}	 

	delete isPrime;
	delete primes;
	return 0;
}

bool* calcIsPrimeArray() {
	bool* isPrime = new bool[1001];
	isPrime[0] = false;
	for(int i = 1; i < 1001; i++) {
		isPrime[i] = true;
	}
	for(int i = 2; i < 1001; i++) {
		if(isPrime[i]) {
			for(int j = 2; i*j<1001; j++) {
				isPrime[i*j] = false;
			}
		}
	}
	return isPrime;
}

vector<int>* getPrimes(bool* isPrime) {
	vector<int>* primes = new vector<int>();
	for(int i = 0; i < 1001; i++) {
		if(isPrime[i]) {
			primes->push_back(i);
		}
	}
	return primes;
}

Pair solve(int n) {
	Pair pair;
	pair.a = 0;
	pair.b = 0;
	return pair;
}

void printResult(Pair p) {
	printf("%d %d\n", p.a, p.b);
}
