#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int count(long long int *calculated, unsigned int *adapters, unsigned int n_adapters,
		unsigned int start_index);

long long int count(long long int *calculated, unsigned int *adapters, unsigned int n_adapters,
		unsigned int start_index) {
	if(calculated[start_index] != -1) return calculated[start_index];
	if(start_index == n_adapters-1) return 1;
	unsigned long long int result = 0;
	for(unsigned int i = start_index + 1; i < n_adapters; i++) {
		if(adapters[i] - adapters[start_index] > 3) break;
		result += count(calculated, adapters, n_adapters, i);
	}
	calculated[start_index] = result;
	return result;
}

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day10p2 <input>\n");
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

	unsigned int adapters[n_lines+2];
	unsigned int n_adapters = 0;
	unsigned int max = 0;
	for(unsigned int i = 0; i < n_lines; i++) {
		if(strlen(lines[i])!=0) {
			sscanf(lines[i],"%u", &adapters[n_adapters]);
			if(adapters[n_adapters] > max) max = adapters[n_adapters];
			n_adapters++;
		}
	}
	
	adapters[n_adapters++] = 0;
	adapters[n_adapters++] = max+3;
	
	/*
	printf("Unsorted array:\n");
	for(unsigned int i = 0; i < n_adapters; i++) {
		printf("\t%u\n", adapters[i]);
	}
	*/
	
	// Sort array
	for(unsigned int i = 0; i < n_adapters; i++) {
		// Find smallest of remaining
		unsigned int min_index = i;
		for(unsigned int j = i+1; j < n_adapters; j++) {
			if(adapters[j] < adapters[min_index]) min_index = j;
		}
		unsigned int temp = adapters[i];
		adapters[i] = adapters[min_index];
		adapters[min_index] = temp;
	}
	
	printf("Sorted array:\n");
	for(unsigned int i = 0; i < n_adapters; i++) {
		printf("\t%u\n", adapters[i]);
	}
	
	long long int calculated[n_adapters];
	for(unsigned int i = 0; i < n_adapters; i++) calculated[i] = -1;
	long long int result = count(calculated, adapters, n_adapters, 0);
	printf("Result: %lld\n", result);

	fclose(input_file);
	return EXIT_SUCCESS;
}
