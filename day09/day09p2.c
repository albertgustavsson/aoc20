#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day09p2 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 1500;
	const unsigned int max_line_length = 20;
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

	unsigned long long int numbers[n_lines];
	unsigned long n_numbers = 0;
	for(unsigned int i = 0; i < n_lines; i++) numbers[i] = 0;
	for(unsigned int i = 0; i < n_lines; i++) {
		if(strlen(lines[i])!=0) {
			numbers[n_numbers++] = strtoull(lines[i],NULL,10);
		}
	}
	
	//for(unsigned int i = 0; i < n_lines; i++) printf("Number %4u: %llu\n", i+1, numbers[i]);
	
	unsigned long long int invalid;
	unsigned int n_check = 25;
	for(unsigned int i = n_check; i < n_numbers; i++) {
		// Check if number is valid
		int valid = 0;
		unsigned long long int target = numbers[i];
		for(unsigned int j = i-n_check; j < i; j++) {
			unsigned long long int n1 = numbers[j];
			for(unsigned int k = j+1; k < i; k++) {
				unsigned long long int n2 = numbers[k];
				if(n1+n2 == target) valid = 1;
				if(valid) break;
			}
			if(valid) break;
		}
		if(!valid) {
			invalid = target;
			break;
		}
	}
	
	printf("First invalid number: %llu\n", invalid);
	
	unsigned long range_index_start = 0;
	unsigned long range_index_end = 1;
	while(1) {
		unsigned long long int sum = 0;
		for(unsigned int i = range_index_start; i <= range_index_end; i++) {
			sum += numbers[i];
		}
		if(sum < invalid) range_index_end++;
		else if(sum > invalid) range_index_start++;
		else break;
	}
	
	printf("Range is numbers %lu - %lu\n", range_index_start, range_index_end);
	
	unsigned long long int min = numbers[range_index_start], max = numbers[range_index_start];
	for(unsigned int i = range_index_start; i <= range_index_end; i++) {
		if(numbers[i] > max) max = numbers[i];
		if(numbers[i] < min) min = numbers[i];
	}
	printf("Min: %llu\nMax: %llu\n", min, max);
	
	printf("Encryption weakness: %llu\n", min+max);

	fclose(input_file);
	return EXIT_SUCCESS;
}
