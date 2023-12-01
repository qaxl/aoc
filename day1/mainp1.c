#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define how much is wanted to be read. 
// By default I decided 32KiB should be enough.
// If larger data needs to be processed, this can be increased.
#define MAX_READ_SIZE (32 * 1024)

// 256 numbers should be more than enough. 
// Adjust as required.
#define MAX_VALS_PER_LINE 256

// My data has 1000 inputs, so 1000 is enough sums.
#define MAX_SUMS 1000

#define IS_VERBOSE 0

int main() {
	FILE* fp = fopen("input.txt", "rb");
	if (fp == NULL) {
		printf("Couldn't open file 'input.txt'!\n");
		return 1;
	}

	char buffer[32*1024];
	int n = fread(buffer, sizeof(*buffer), sizeof(buffer), fp);

	if (n == 0) {
		if (feof(fp)) 
			printf("Unexpected eof.\n");
		else if (ferror(fp))
			printf("Error reading input.txt!\n");
		return 1;
	}

#ifdef IS_VERBOSE
	printf("VERBOSE: READ: %d bytes with buffer size of %d.\n", n, MAX_READ_SIZE);
#endif

	long long sums[MAX_SUMS] = {0};
	int sums_ind = 0;

	char vals[2] = {};
	for (int i = 0; i < n; ++i) {
		char val = buffer[i];
		if (val == '\n') {
			char buf[3];
			buf[2] = 0;

			buf[0] = vals[0];
			if (vals[1] != 0)
				buf[1] = vals[1];
			else
				buf[1] = vals[0];

			sums[sums_ind++] = atoll(buf);
#if IS_VERBOSE
			printf("VERBOSE: SUM of %c and %c IS %lld. The sum is %dth.\n", buf[0], buf[1], sums[sums_ind-1], sums_ind);
#endif

			vals[0] = 0;
			vals[1] = 0;
		} else if (val >= '0' && val <= '9') {
			// convert the number to integer via a quick way
			// int val_int = val - '0';
			
#ifdef IS_VERBOSE
			printf("VERBOSE: NUMBER: %d (%c); VALS[2] = { %c, %c }\n", (val - '0'), val, vals[0], vals[1]);
#endif

			if (vals[0] != 0)
				vals[1] = val;
			else
				vals[0] = val;

#ifdef IS_VERBOSE
			printf("VERBOSE: VALS[2] = { %c, %c }\n", vals[0], vals[1]);
#endif
		}
	}

	long long sum = 0;
	for (int i = 0; i < sums_ind; ++i) 
		sum += sums[i];

	printf("%lld\n", sum);
	return 0;
}

