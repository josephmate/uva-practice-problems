#include <stdlib.h>
#include <stdio.h>

void collatz_search(int a, int b);
int collatz_len(int a);

int main(int argc, const char *argv[])
{
	int n1;
	int n2;
	while (fscanf(stdin, "%d %d\n", &n1, &n2) > 0) {
		collatz_search(n1,n2);
	}	 
	

	return 0;
}

void collatz_search(int a, int b)
{
	int ret;
	int i;
	int max_len = 0;
	int start = a;
	int end = b;

	if( a > b ) {
		start = b;
		end = a;
	}

	for (i = start; i <= end; i++) {
		int len = collatz_len(i);
		if(len > max_len) {
			ret = i;
			max_len = len;
		}
	}

	printf("%d %d %d\n", a, b, max_len);
}

int collatz_len(int a)
{
	int counter = 0;
	while(true) {
		counter = counter + 1;

		if(a == 1){
			break;
		}

		if( a % 2 == 1) {
			a = 3*a + 1;
		} else {
			a = a / 2;
		}
	}
	return counter;
}
