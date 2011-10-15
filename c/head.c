#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARS_MAX_DEFAULT 100

int main(int argc, char ** args) {
	FILE * file;
	char * filename;
	char * endp;
	long i, chars_max;
	int c;
	if (argc < 2) {
		printf("Usage: head filename\n");
		return 1;
	}
	chars_max = strtol(*(args+1), &endp, 10);
	if (strcmp(endp, "") != 0) {
		filename = *(args+1);
		chars_max = CHARS_MAX_DEFAULT;
	} else {
		if (argc < 3) {
			printf("Usage: head number-of-chars filename\n");
			return 1;
		}
		filename = *(args+2);
	}
	file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Cannot read %s\n", filename);
		return 1;
	}
	for (i=0; i < chars_max; i++) {
		if ((c = fgetc(file)) == EOF) {
			break;
		}
		putchar(c);
	}
	if (fclose(file)) {
		printf("Error when closing %s\n", filename);
		return 1;
	}
}
