#include <stdio.h>
#include <stdlib.h>
#include "streaming.h"

struct s_stream {
    char* chars;
    int pos;
    int length;
};

stream make_stream(char* chars) {
    stream new_stream = (stream) malloc(sizeof(struct s_stream));
    if (new_stream == NULL) {
	exit(1);
    }

    new_stream->chars = chars;
    new_stream->pos = -1;
    new_stream->length = -2; // choose a different init value than pos init value

    return new_stream;
}

void dispose_stream(stream used_stream) {
    free(used_stream);
}

char current(stream a_stream) {
    return *(a_stream->chars + a_stream->pos);
}

int next(stream a_stream) {
    if (a_stream->pos == a_stream->length) {
	return 0;
    }

    a_stream->pos++;
    if (*(a_stream->chars + a_stream->pos) == '\0') {
	a_stream->length = a_stream->pos;
	return 0;
    }

    return 1;
}

int back(stream a_stream) {
    if (a_stream->pos >= 0) {
	a_stream->pos--;
	return 1;
    }

    return 0;
}

