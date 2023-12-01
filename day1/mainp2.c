#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define how much is wanted to be read. 
// By default I decided 32KiB should be enough.
// If larger data needs to be processed, this can be increased.
#define MAX_READ_SIZE (32 * 1024)

// My data has 1000 inputs, so 1000 is enough sums.
#define MAX_SUMS 1000+1

#define IS_VERBOSE 0

void insert_value(char array[2], char val) {
	if (array[0] != 0)
		array[1] = val;
	else
		array[0] = val;
}

int main() {
	FILE* fp = fopen("input.txt", "rb");
	if (fp == NULL) {
		printf("Couldn't open file 'input.txt'!\n");
		return 1;
	}

	char buffer[MAX_READ_SIZE];
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

			insert_value(vals, val);
#ifdef IS_VERBOSE
			printf("VERBOSE: VALS[2] = { %c, %c }\n", vals[0], vals[1]);
#endif
		} else {
			switch (val) {
				case 'o':
					if (buffer[i + 1] == 'n' && buffer[i + 2] == 'e')
						insert_value(vals, '1');
					break;

				case 't':
					if (buffer[i + 1] == 'w' && buffer[i + 2] == 'o')
						insert_value(vals, '2');
					else if (strncmp(&buffer[i + 1], "hree", 4) == 0)
						insert_value(vals, '3');
					break;

				case 'f':
					if (strncmp(&buffer[i + 1], "our", 3) == 0)
						insert_value(vals, '4');
					else if(strncmp(&buffer[i + 1], "ive", 3) == 0)
						insert_value(vals, '5');
					break;

				case 's':
					if (buffer[i + 1] == 'i' && buffer[i + 2] == 'x')
						insert_value(vals, '6');
					else if(strncmp(&buffer[i + 1], "even", 4) == 0)
						insert_value(vals, '7');
					break;

				case 'e':
					if (strncmp(&buffer[i + 1], "ight", 4) == 0)
						insert_value(vals, '8');
					break;

				case 'n':
					if (buffer[i + 1] == 'i' && buffer[i + 2] == 'n' && buffer[i + 3] == 'e')
						insert_value(vals, '9');
					break;
			}
		}
	}

	long long sum = 0;
	for (int i = 0; i < sums_ind; ++i) 
		sum += sums[i];

	printf("%lld\n", sum);
	return 0;
}

