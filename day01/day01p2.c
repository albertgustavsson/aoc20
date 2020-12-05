#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day01p2 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	// Change if input file contains more than 1000 lines
	const unsigned int max_lines = 1000;
	unsigned int n_numbers = 0;
	unsigned int numbers[max_lines];
	while(!feof(input_file)) {
		fscanf(input_file, "%u\n", &numbers[n_numbers++]);
	}

	int done = 0;
	for(unsigned int i = 0; i < n_numbers && !done; i++) {
		for(unsigned int j = i+1; j < n_numbers && !done; j++) {
			for(unsigned int k = j+1; k < n_numbers && !done; k++) {
				if(numbers[i]+numbers[j]+numbers[k] == 2020) {
					printf("Result: %u*%u*%u=%u\n", numbers[i], numbers[j], numbers[k], numbers[i]*numbers[j]*numbers[k]);
					done = 1;
				}
			}
		}
	}

	fclose(input_file);
	return EXIT_SUCCESS;
}
