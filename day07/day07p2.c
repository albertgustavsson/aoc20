#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_MAX_LENGTH 50
#define CONTENTS_MAX_NUMBER 5
struct bag_contents {
	unsigned int n_colors;
	char colors[CONTENTS_MAX_NUMBER][COLOR_MAX_LENGTH];
	unsigned int n_colored_bags[CONTENTS_MAX_NUMBER];
};

struct bag {
	char color[COLOR_MAX_LENGTH];
	struct bag_contents contents;
};

#define MAX_COLORS 1000
struct bag bags[MAX_COLORS];
unsigned int n_bags = 0;

int count_inside(char *bag_color);
int count_inside(char *bag_color) {
	unsigned int count = 0;
	for(unsigned int i = 0; i < n_bags; i++) {
		if(strcmp(bags[i].color, bag_color) == 0) {
			for(unsigned int j = 0; j < bags[i].contents.n_colors; j++) {
				count += bags[i].contents.n_colored_bags[j]*(1+count_inside(bags[i].contents.colors[j]));
			}
			return count;
		}
	}
	return 0;
}

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day07p2 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_line_length = 150;
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
		//printf("Line: \"%s\"\n", line);
		char *part1, *part2;
		part1 = strtok(line, " ");
		part2 = strtok(NULL, " ");
		sprintf(bags[n_bags].color, "%s %s", part1, part2);
		//printf("Color: \"%s\"\n", bags[n_bags].color);
		strtok(NULL, " "); // "bags"
		strtok(NULL, " "); // "contain"
		char *num = strtok(NULL, " ");
		bags[n_bags].contents.n_colors = 0;
		if(strcmp(num, "no") == 0) {
			
		} else {
			do {
				unsigned int number = (unsigned int)atoi(num);
				bags[n_bags].contents.n_colored_bags[bags[n_bags].contents.n_colors] = number;
				//printf("Number: %u\n", number);
				part1 = strtok(NULL, " ");
				part2 = strtok(NULL, " ");
				sprintf(bags[n_bags].contents.colors[bags[n_bags].contents.n_colors], "%s %s", part1, part2);
				//printf("Color: %s\n", bags[n_bags].contents.colors[bags[n_bags].contents.n_colors]);
				bags[n_bags].contents.n_colors++;
				strtok(NULL, ",."); // "bag" or "bags"
				num = strtok(NULL, " ");
			} while(num != NULL);
		}
		n_bags++;
	}

	for(unsigned int i = 0; i < n_bags; i++) {
		printf("%s contents:\n", bags[i].color);
		for(unsigned int j = 0; j < bags[i].contents.n_colors; j++) {
			printf("\t%u %s\n", bags[i].contents.n_colored_bags[j], bags[i].contents.colors[j]);
		}
	}

	unsigned int result = count_inside("shiny gold");
	printf("Result: %u\n", result);

	fclose(input_file);
	return EXIT_SUCCESS;
}
