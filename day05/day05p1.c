#include <stdio.h>
#include <stdlib.h>

#define LOW 0
#define HIGH 1

void split_range(unsigned int *low, unsigned int *high, int half);
unsigned int get_set_id(const char *);

void split_range(unsigned int *low, unsigned int *high, int half) {
	if(half == HIGH) {
		*low = (*high + *low)/2 + 1;
	} else if(half == LOW) {
		*high = (*high + *low)/2;
	}
}
unsigned int get_set_id(const char *line) {
	unsigned int row_l = 0, row_h = 127, col_l = 0, col_h = 7;
	for(unsigned int i = 0; i < 7; i++) {
		if(line[i] == 'F') split_range(&row_l, &row_h, LOW);
		else if(line[i] == 'B') split_range(&row_l, &row_h, HIGH);
	}
	for(unsigned int i = 7; i < 10; i++) {
		if(line[i] == 'L') split_range(&col_l, &col_h, LOW);
		else if(line[i] == 'R') split_range(&col_l, &col_h, HIGH);
	}
	return row_l*8+col_l;
}

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day05p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	unsigned int max_id = 0;
	while(!feof(input_file)) {
		const unsigned int max_line_length = 50;
		char line[max_line_length];
		fscanf(input_file, "%s\n", line);
		unsigned int id = get_set_id(line);
		if(id > max_id) max_id = id;
	}

	printf("Max seat ID: %u\n", max_id);

	fclose(input_file);
	return EXIT_SUCCESS;
}
