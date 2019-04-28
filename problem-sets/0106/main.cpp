#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

struct IntegerSqrtResult {
	bool found;
	long long result;
};

struct TripletResult {
	// the number of relatively prime triplets x,y,z with the constraints
	// 1) x^2 + y^2 = z^z
	// 2) x <= y <= z
	// 3) x,y,z share no divsors
	long long numRelativelyPrime;

	// The second numberis the number of positive integers <= N that are not part of any triple whose components are all <= N
	// TODO: not sure what this second number is yet
	long long b;
};
TripletResult solve(long long n);
void printResult(TripletResult);
bool* calcIsPrimeArray();
vector<long long>* getPrimes(bool*);
IntegerSqrtResult intSqrt(long long);



int main(int argc, const char *argv[])
{
	bool* isPrime = calcIsPrimeArray();
#ifdef DEBUG
	for(long long i = 0; i < 1001; i++) {
		printf("%d %s\n", i, (isPrime[i])?"true":"false");
	}
#endif
	vector<long long>* primes = getPrimes(isPrime);
#ifdef DEBUG
	for(long long i = 0; i < primes->size(); i++) {
		printf("prime %d\n", primes->at(i));
	}
#endif

	long long n;
	while (fscanf(stdin, "%d\n", &n)> 0) {
#ifdef DEBUG
		printf("%d\n", n);
#endif
		TripletResult result = solve(n);
		printResult(result);
	}	 

	delete isPrime;
	delete primes;
	return 0;
}

bool* calcIsPrimeArray() {
	bool* isPrime = new bool[1001];
	isPrime[0] = false;
	for(long long i = 1; i < 1001; i++) {
		isPrime[i] = true;
	}
	for(long long i = 2; i < 1001; i++) {
		if(isPrime[i]) {
			for(long long j = 2; i*j<1001; j++) {
				isPrime[i*j] = false;
			}
		}
	}
	return isPrime;
}

vector<long long>* getPrimes(bool* isPrime) {
	vector<long long>* primes = new vector<long long>();
	for(long long i = 0; i < 1001; i++) {
		if(isPrime[i]) {
			primes->push_back(i);
		}
	}
	return primes;
}

// binary search for a square root
IntegerSqrtResult intSqrt(long long sqrtee){
	IntegerSqrtResult result;
	result.found = false;
	long long lowerBound = 1;
	long long upperBound = sqrtee;
	while(true) {
		if(lowerBound > upperBound) {
			return result; // NOT FOUND
		}
		long long midPoint = (lowerBound + upperBound)/2;
		long long midSquared = midPoint*midPoint;
		if(midSquared == sqrtee) {
			result.found = true;
			result.result = midPoint;
			return result;
		} else if(midSquared > sqrtee) {
			upperBound = midPoint;
		} else { // midSquared < sqrtee
			lowerBound = midPoint;
		}
	}
}

TripletResult solve(long long n) {
	TripletResult result;
	result.numRelativelyPrime = 0;
	result.b = 0;
	
	for(long long x = 1; x <= 1000; x++) {
		for(long long y = x; y <= 1000; y++) {
		}
	}

	return result;
}

void printResult(TripletResult result) {
	printf("%d %d\n", result.numRelativelyPrime, result.b);
}
