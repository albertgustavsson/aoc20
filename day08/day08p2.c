#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day08p2 <input>\n");
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

	for(unsigned int i = 0; i < n_lines; i++) {
		char instruction[5];
		int value;
		sscanf(lines[i], "%s %d", instruction, &value);
		if(strcmp(instruction, "nop") == 0) {
			sprintf(lines[i], "%s %+d", "jmp", value);
		} else if(strcmp(instruction, "jmp") == 0) {
			sprintf(lines[i], "%s %+d", "nop", value);
		} else {
			continue;
		}
		// Check if program terminates
		int terminated;
		int already_run[n_lines];
		for(unsigned int j = 0; j < n_lines; j++) already_run[j] = 0;
		unsigned int position = 0;
		int accumulator = 0;
		/*
		printf("Running with code:\n");
		for(unsigned int j = 0; j < n_lines; j++) {
			printf("\t%s\n", lines[j]);
		}
		*/
		while(1) {
			if(position >= n_lines) {
				terminated = 1;
				break;
			}
			if(already_run[position]) {
				terminated = 0;
				break;
			} else {
				already_run[position] = 1;
			}
			char instr[5];
			int val;
			sscanf(lines[position], "%s %d", instr, &val);
			if(strcmp(instr, "nop") == 0) {
				position++;
			} else if(strcmp(instr, "acc") == 0) {
				accumulator += val;
				position++;
			} else if(strcmp(instr, "jmp") == 0) {
				position+=val;
			}
		}
		if(terminated == 1) {
			printf("Found solution. Accumulator value: %d\n", accumulator);
			break;
		} else {
			// Switch back
			if(strcmp(instruction, "nop") == 0) {
				sprintf(lines[i], "%s %+d", "nop", value);
			} else if(strcmp(instruction, "jmp") == 0) {
				sprintf(lines[i], "%s %+d", "jmp", value);
			}
		}
	}

	fclose(input_file);
	return EXIT_SUCCESS;
}
