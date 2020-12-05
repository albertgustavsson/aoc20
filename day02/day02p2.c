#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day02p2 <input>\n");
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
		unsigned int index1, index2;
		char c;
		char password[max_password_length];
		fscanf(input_file, "%u-%u %c: %s\n", &index1, &index2, &c, password);

		char c1 = password[index1-1];
		char c2 = password[index2-1];
		if((c1 == c && c2 != c) || (c1 != c && c2 == c)) n_valid++;
	}

	printf("The input contained %u valid passwords\n", n_valid);

	fclose(input_file);
	return EXIT_SUCCESS;
}
