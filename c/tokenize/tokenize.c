#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "streaming.h"

void tokenize(char* input) {
    stream input_stream = make_stream(input);
    while (next(input_stream)) {
	printf("%c is %swhitespace\n", 
	       current(input_stream), isspace(current(input_stream)) ? "" : "not ");
    }
    dispose_stream(input_stream);
}

int main(int argc, char** args) {
    int i;
    for (i=1; i < argc; i++) {
	printf("%s\n", *(args+i));
	stream input_stream = make_stream(*(args+i));
	while (next(input_stream)) {
	    printf("%c", current(input_stream));
	}
	next(input_stream);
	next(input_stream);
	next(input_stream);
	while (back(input_stream)) {
	    printf("%c", current(input_stream));
	}
	while (next(input_stream)) {
	    printf("%c", current(input_stream));
	}
	while (back(input_stream)) {
	    printf("%c", current(input_stream));
	}
	printf("!\n");
	dispose_stream(input_stream);
	//tokenize(*(args+i));
    }

    return 0;
}
