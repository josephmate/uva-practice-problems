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
	char action1[5];
	char action2[5];
	int n, a, b;

	// read in how many stacks and blocks we have
	fscanf(stdin, "%d\n", &n);

	while (fscanf(stdin, "%s %d %s %d\n", action1, &a, action2, &b) > 0 && action1[0] != 'q') {
	}	 
	
	return 0;
}


