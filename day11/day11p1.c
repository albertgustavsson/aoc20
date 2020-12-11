#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day11p1 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_lines = 500;
	const unsigned int max_line_length = 150;
	char lines[max_lines][max_line_length];
	unsigned int n_lines = 0;
	while(n_lines<max_lines && fgets(lines[n_lines],max_line_length,input_file)) {
		unsigned int last_index = strlen(lines[n_lines])-1;
		if(lines[n_lines][last_index] == '\n') lines[n_lines][last_index] = '\0';
		n_lines++;
	}
	
	unsigned int map_width = strlen(lines[0]);
	unsigned int map_height = n_lines;
	
	char seats[map_height][map_width];
	for(unsigned int r = 0; r < map_height; r++) {
		for(unsigned int c = 0; c < map_width; c++) {
			seats[r][c] = lines[r][c];
		}
	}
	
	/*
	printf("Seats:\n");
	for(unsigned int r = 0; r < map_height; r++) {
		for(unsigned int c = 0; c < map_width; c++) {
			printf("%c", seats[r][c]);
		}
		printf("\n");
	}
	*/
	
	int changed = 0;
	do {
		changed = 0;
		char seats_next[map_height][map_width];
		for(unsigned int r = 0; r < map_height; r++) {
			for(unsigned int c = 0; c < map_width; c++) {
				unsigned int adjacent_occupied = 0;
				for(int rd = -1; rd <= 1; rd++) {
					for(int cd = -1; cd <= 1; cd++) {
						if(rd==0 && cd==0) continue;
						if(r==0 && rd==-1) continue;
						if(c==0 && cd==-1) continue;
						if(r==map_height-1 && rd==1) continue;
						if(c==map_width-1 && cd==1) continue;
						if(seats[r+rd][c+cd]=='#') adjacent_occupied++;
					}
				}
				if(seats[r][c] == 'L' && adjacent_occupied == 0) {
					seats_next[r][c] = '#';
					changed = 1;
				} else if(seats[r][c] == '#' && adjacent_occupied >= 4) {
					seats_next[r][c] = 'L';
					changed = 1;
				} else seats_next[r][c] = seats[r][c];
			}
		}
		for(unsigned int r = 0; r < map_height; r++) {
			for(unsigned int c = 0; c < map_width; c++) {
				seats[r][c] = seats_next[r][c];
			}
		}
	} while(changed);
	
	unsigned int occupied = 0;
	for(unsigned int r = 0; r < map_height; r++) {
		for(unsigned int c = 0; c < map_width; c++) {
			if(seats[r][c] == '#') occupied++;
		}
	}
	
	printf("%u seats are occupied\n", occupied);

	fclose(input_file);
	return EXIT_SUCCESS;
}
