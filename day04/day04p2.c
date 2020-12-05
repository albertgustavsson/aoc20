#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char **argv) {
	if(argc != 2) {
		fprintf(stderr, "Usage: day04p2 <input>\n");
		return EXIT_FAILURE;
	}
	const char *filename = argv[1];
	FILE *input_file = fopen(filename,"r");
	if(input_file == NULL) {
		perror("Couldn't open file");
		return EXIT_FAILURE;
	}

	const unsigned int max_line_length = 100;
	char line[max_line_length];
	int has_byr = 0, has_iyr = 0, has_eyr = 0, has_hgt = 0, has_hcl = 0, has_ecl = 0, has_pid = 0/*, has_cid = 0*/;
	unsigned int n_valid = 0;
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
		printf("Line: \"%s\"\n", line);
		if(strlen(line) == 0) { // if line is empty
			if(has_byr && has_iyr && has_eyr && has_hgt && has_hcl && has_ecl && has_pid) {
				n_valid++;
				printf("Passport was valid\n");
			}
			has_byr = 0;
			has_iyr = 0;
			has_eyr = 0;
			has_hgt = 0;
			has_hcl = 0;
			has_ecl = 0;
			has_pid = 0;
			/*has_cid = 0;*/
		} else {
			char pair[100];
			char *line_temp = line;
			while(sscanf(line_temp, "%s", pair) != 0) {
				line_temp += strlen(pair);
				while(*line_temp == ' ') line_temp++;
				printf("\tPair: \"%s\"\n", pair);
				char *key = strndup(pair, 3);
				char *value = pair+4;
				printf("\t\tKey: \"%s\"\n", key);
				printf("\t\tValue: \"%s\"\n", value);
				if(strcmp(key, "byr") == 0) {
					if(strlen(value) == 4 && atol(value) >= 1920 && atol(value) <= 2002) has_byr = 1;
				} else if(strcmp(key, "iyr") == 0) {
					if(strlen(value) == 4 && atol(value) >= 2010 && atol(value) <= 2020) has_iyr = 1;
				} else if(strcmp(key, "eyr") == 0) {
					if(strlen(value) == 4 && atol(value) >= 2020 && atol(value) <= 2030) has_eyr = 1;
				} else if(strcmp(key, "hgt") == 0) {
					int height;
					if(sscanf(value, "%d", &height) == 1) {
						char *unit = value;
						while(isdigit(*unit)) unit++;
						if( (strcmp(unit, "cm") == 0 && height >= 150 && height <= 193) ||
							(strcmp(unit, "in") == 0 && height >= 59 && height <= 76)) has_hgt = 1;
					}
				} else if(strcmp(key, "hcl") == 0) {
					if(value[0] == '#') {
						unsigned int i;
						for(i = 0; i < 6; i++) {
							if(!((value[i+1]>='0' && value[i+1]<='9') || (value[i+1]>='a' && value[i+1]<='f'))) break;
						}
						if(i == 6) has_hcl = 1;
					}
				} else if(strcmp(key, "ecl") == 0) {
					if( strcmp(value, "amb") == 0 ||
						strcmp(value, "blu") == 0 ||
						strcmp(value, "brn") == 0 ||
						strcmp(value, "gry") == 0 ||
						strcmp(value, "grn") == 0 ||
						strcmp(value, "hzl") == 0 ||
						strcmp(value, "oth") == 0) has_ecl = 1;
				} else if(strcmp(key, "pid") == 0) {
					if(strlen(value) == 9) {
						unsigned int i;
						for(i = 0; i < 9; i++) {
							if(!isdigit(value[i])) break;
						}
						if(i == 9) has_pid = 1;
					}
				} /*else if(strcmp(key, "cid") == 0) {
					has_cid = 1;
				}*/
				free(key);
				if(strlen(line_temp) == 0) break;
				//printf("\t\tRemainder of line: \"%s\"\n", line_temp);
			}
		}
	}

	// If last line was not empty
	if(strlen(line) != 0) {
		if(has_byr && has_iyr && has_eyr && has_hgt && has_hcl && has_ecl && has_pid) {
			n_valid++;
			printf("Passport was valid\n");
		}
	}

	printf("Number of valid passports: %u\n", n_valid);

	fclose(input_file);
	return EXIT_SUCCESS;
}
