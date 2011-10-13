#ifndef STREAMING
#define STREAMING
typedef struct s_stream* stream;

stream make_stream(char* chars);
void dispose_stream(stream used_stream);
char current(stream a_stream);
int next(stream a_stream);
int back(stream a_stream);
#endif

