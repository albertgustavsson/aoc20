#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day03p2 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 500;
	const unsigned int max_line_length = 50;
	char map[max_lines][max_line_length];
	unsigned int n_lines = 0;
	while(!feof(input_file)) {
		fscanf(input_file, "%s\n", map[n_lines++]);
	}

	unsigned int line_length=strlen(map[0]);
	const unsigned int n_slopes = 5;
	unsigned int n_trees[] = {0,0,0,0,0};
	unsigned int step_x[] = {1,3,5,7,1}, step_y[] = {1,1,1,1,2};
	for(unsigned int slope = 0; slope < n_slopes; slope++) {
		unsigned int pos_x = 0, pos_y = 0;
		while(pos_y < n_lines) {
			if(map[pos_y][pos_x] == '#') n_trees[slope]++;
			pos_x=(pos_x+step_x[slope])%line_length;
			pos_y=pos_y+step_y[slope];
		}
	}

	unsigned int res = n_trees[0];
	for(unsigned int i = 1; i < n_slopes; i++) {
		res *= n_trees[i];
	}
	printf("Final result: %u\n", res);

	fclose(input_file);
	return EXIT_SUCCESS;
}
