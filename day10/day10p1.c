#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day10p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 500;
	const unsigned int max_line_length = 10;
	char lines[max_lines][max_line_length];
	unsigned int n_lines = 0;
	while(n_lines<max_lines && fgets(lines[n_lines],max_line_length,input_file)) {
		for(unsigned int i = 0; i < max_line_length; i++) {
			if(lines[n_lines][i] == '\n') {
				lines[n_lines][i] = '\0';
				break;
			} else if(lines[n_lines][i] == '\0') {
				break;
			}
		}
		n_lines++;
	}

	unsigned int adapters[n_lines];
	unsigned long n_adapters = 0;
	for(unsigned int i = 0; i < n_lines; i++) {
		if(strlen(lines[i])!=0) {
			sscanf(lines[i],"%u", &adapters[n_adapters++]);
		}
	}
	
	unsigned int adapters_sorted[n_adapters];
	for(unsigned int i = 0; i < n_adapters; i++) {
		adapters_sorted[i] = adapters[i];
	}
	// Sort array
	for(unsigned int i = 0; i < n_adapters; i++) {
		// Find smallest of remaining
		unsigned int min_index = i;
		for(unsigned int j = i+1; j < n_adapters; j++) {
			if(adapters_sorted[j] < adapters_sorted[min_index]) min_index = j;
		}
		unsigned int temp = adapters_sorted[i];
		adapters_sorted[i] = adapters_sorted[min_index];
		adapters_sorted[min_index] = temp;
	}
	
	/*
	printf("Sorted array:\n");
	for(unsigned int i = 0; i < n_adapters; i++) {
		printf("\t%u\n", adapters_sorted[i]);
	}
	*/
	
	unsigned int diff1 = 0;
	unsigned int diff3 = 0;
	
	if(adapters_sorted[0]==1) diff1++;
	else if(adapters_sorted[0]==3) diff3++;
	
	for(unsigned int i = 1; i < n_adapters; i++) {
		if(adapters_sorted[i]-adapters_sorted[i-1] == 1) diff1++;
		else if(adapters_sorted[i]-adapters_sorted[i-1] == 3) diff3++;
	}
	
	// Device joltage is 3 jolts higher than the highest adapter rating
	diff3++;

	//printf("Number of 1 jolt differences: %u\n", diff1);
	//printf("Number of 3 jolt differences: %u\n", diff3);
	printf("Result: %u\n", diff1*diff3);

	fclose(input_file);
	return EXIT_SUCCESS;
}
