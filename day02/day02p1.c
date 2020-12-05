#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day02p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_password_length = 50;
	unsigned int n_valid = 0;
	while(!feof(input_file)) {
		unsigned int min, max;
		char c;
		char password[max_password_length];
		fscanf(input_file, "%u-%u %c: %s\n", &min, &max, &c, password);

		unsigned int n_chars = 0;
		for(unsigned int i = 0; password[i]!='\0'; i++) {
			if(password[i]==c) n_chars++;
		}
		if(n_chars>=min && n_chars<=max) n_valid++;
	}

	printf("The input contained %u valid passwords\n", n_valid);

	fclose(input_file);
	return EXIT_SUCCESS;
}
