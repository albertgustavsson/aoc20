#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum direction {
	north, east, south, west
};

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day12p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 1000;
	const unsigned int max_line_length = 10;
	char lines[max_lines][max_line_length];
	unsigned int n_lines = 0;
	while(n_lines<max_lines && fgets(lines[n_lines],max_line_length,input_file)) {
		unsigned int last_index = strlen(lines[n_lines])-1;
		if(lines[n_lines][last_index] == '\n') lines[n_lines][last_index] = '\0';
		if(strlen(lines[n_lines]) != 0) n_lines++;
	}
	
	char actions[n_lines];
	unsigned int values[n_lines];
	for(unsigned int i = 0; i < n_lines; i++) {
		actions[i] = lines[i][0];
		values[i] = (unsigned int)atol(&lines[i][1]);
	}
	
	enum direction dir = east;
	int pos_ew = 0, pos_ns = 0;
	unsigned int val_temp;
	for(unsigned int i = 0; i < n_lines; i++) {
		switch (actions[i]) {
			case 'N':
			pos_ns+=values[i];
			break;
			case 'E':
			pos_ew+=values[i];
			break;
			case 'S':
			pos_ns-=values[i];
			break;
			case 'W':
			pos_ew-=values[i];
			break;
			case 'F':
			switch (dir) {
				case north:
				pos_ns+=values[i];
				break;
				case east:
				pos_ew+=values[i];
				break;
				case south:
				pos_ns-=values[i];
				break;
				case west:
				pos_ew-=values[i];
				break;
			}
			break;
			case 'L':
			val_temp = values[i];
			while(val_temp > 0) {
				switch (dir) {
					case north:
					dir=west;
					break;
					case east:
					dir=north;
					break;
					case south:
					dir=east;
					break;
					case west:
					dir=south;
					break;
				}
				val_temp -= 90;
			}
			break;
			case 'R':
			val_temp = values[i];
			while(val_temp > 0) {
				switch (dir) {
					case north:
					dir=east;
					break;
					case east:
					dir=south;
					break;
					case south:
					dir=west;
					break;
					case west:
					dir=north;
					break;
				}
				val_temp -= 90;
			}
			break;
		}
	}

	printf("Position:\n\t%s: %u\n\t%s: %u\n", (pos_ns<0?"South":"North"), abs(pos_ns), (pos_ew<0?"West":"East"), abs(pos_ew));
	printf("Manhattan distance: %d\n", abs(pos_ew)+abs(pos_ns));

	fclose(input_file);
	return EXIT_SUCCESS;
}
