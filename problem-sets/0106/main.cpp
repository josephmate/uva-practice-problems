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



int main(int argc, const char *argv[])
{
	int n;
	while (fscanf(stdin, "%d\n", &n)> 0) {
#ifdef DEBUG
		printf("%d\n", n);
#endif
	}	 
	
	return 0;
}


