#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day06p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	int answered['z'-'a'+1];
	for(unsigned int i = 0; i < 'z'-'a'+1; i++) {
		answered[i] = 0;
	}
	unsigned int count = 0;
	const unsigned int max_line_length = 50;
	char line[max_line_length];
	while(fgets(line, max_line_length, input_file)) {
		// Remove newline
		for(unsigned int i = 0; i < max_line_length; i++) {
			if(line[i] == '\n') {
				line[i] = '\0';
				break;
			} else if(line[i] == '\0') {
				break;
			}
		}
		if(strlen(line) == 0) {
			for(unsigned int i = 0; i < 'z'-'a'+1; i++) {
				if(answered[i]) count++;
				answered[i] = 0;
			}
		} else {
			for(unsigned int i = 0; i < strlen(line); i++) {
				answered[line[i]-'a'] = 1;
			}
		}
	}
	
	// If last line was not empty
	if(strlen(line) != 0) {
		for(unsigned int i = 0; i < 'z'-'a'+1; i++) {
			if(answered[i]) count++;
			answered[i] = 0;
		}
	}

	printf("Count: %u\n", count);

	fclose(input_file);
	return EXIT_SUCCESS;
}
