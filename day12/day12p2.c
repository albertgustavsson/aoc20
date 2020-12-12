#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day12p2 <input>\n");
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
	
	int ship_ns = 0, ship_ew = 0, waypoint_ns = 1, waypoint_ew = 10;
	unsigned int val_temp;
	for(unsigned int i = 0; i < n_lines; i++) {
		switch (actions[i]) {
			case 'N':
			waypoint_ns+=values[i];
			break;
			case 'E':
			waypoint_ew+=values[i];
			break;
			case 'S':
			waypoint_ns-=values[i];
			break;
			case 'W':
			waypoint_ew-=values[i];
			break;
			case 'F':
			ship_ns+=waypoint_ns*values[i];
			ship_ew+=waypoint_ew*values[i];
			break;
			case 'L':
			val_temp = values[i];
			while(val_temp > 0) {
				unsigned int temp = waypoint_ew;
				waypoint_ew = -waypoint_ns;
				waypoint_ns = temp;
				val_temp -= 90;
			}
			break;
			case 'R':
			val_temp = values[i];
			while(val_temp > 0) {
				unsigned int temp = waypoint_ew;
				waypoint_ew = waypoint_ns;
				waypoint_ns = -temp;
				val_temp -= 90;
			}
			break;
		}
	}

	printf("Position:\n\t%s: %u\n\t%s: %u\n", (ship_ns<0?"South":"North"), abs(ship_ns), (ship_ew<0?"West":"East"), abs(ship_ew));
	printf("Manhattan distance: %d\n", abs(ship_ns)+abs(ship_ew));

	fclose(input_file);
	return EXIT_SUCCESS;
}
