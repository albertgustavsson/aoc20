#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day08p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 1000;
	const unsigned int max_line_length = 20;
	char lines[max_lines][max_line_length];
	unsigned int n_lines = 0;
	while(n_lines<max_lines && fgets(lines[n_lines++],max_line_length,input_file));

	int already_run[n_lines];
	for(unsigned int i = 0; i < n_lines; i++) already_run[i] = 0;
	unsigned int position = 0;
	int accumulator = 0;
	while(1) {
		if(already_run[position]) {
			break;
		} else {
			already_run[position] = 1;
		}
		char instruction[5];
		int value;
		sscanf(lines[position], "%s %d", instruction, &value);
		if(strcmp(instruction, "nop") == 0) {
			position++;
		} else if(strcmp(instruction, "acc") == 0) {
			accumulator += value;
			position++;
		} else if(strcmp(instruction, "jmp") == 0) {
			position+=value;
		}
	}

	printf("Accumulator value: %d\n", accumulator);

	fclose(input_file);
	return EXIT_SUCCESS;
}
