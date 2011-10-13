#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#include "util.h"

#define DATE_FORMAT "%d_%m_%Y"
#define DATE_STRING_LENGTH 11

time_t get_modification_time(const char * filename) {
  struct stat stbuf;

  if (stat(filename, &stbuf) == -1) {
    fprintf(stderr, "get_modification_time: can't access %s\n", filename);
    return -1;
  } 

  return stbuf.st_mtime;
}

int is_file(const char * filename) {
  struct stat stbuf;

  if (stat(filename, &stbuf) == -1) {
    fprintf(stderr, "is_file: can't access %s\n", filename);
    return -1;
  } 

  return (stbuf.st_mode & S_IFMT) == S_IFREG;
}

void get_date_string(char * date_string, const struct tm * tp) {
  strftime(date_string, DATE_STRING_LENGTH, DATE_FORMAT, tp);
}

void get_filename_extension(char * ext, const char * filename) {
  const char * last = strrchr(filename, '.');
  if (last) {
    strcpy(ext, last);
  } else {
    strcpy(ext, "");
  }
}

void get_pathname(char * pathname, const char * filename) {
  const char * last = strrchr(filename, '/');
  if (last) {
    strncpy(pathname, filename, last-filename+1);
    *(pathname+(last-filename+1)) = '\0';
  } else {
    *pathname = '\0';
  }

}

void strcatmulti(char * s, ...) {
  va_list char_p;

  va_start(char_p, s);

  char* p = va_arg(char_p, char *);
  while (p) {
    strncat(s, p, strlen(p));
    p = va_arg(char_p, char *);
  }

  va_end(char_p);
}
