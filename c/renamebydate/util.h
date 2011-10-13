#include <time.h>

#ifndef UTIL_H
#define UTIL_H

time_t get_modification_time(const char * filename);

int is_file(const char * filename);

void get_date_string(char * date_string, const struct tm * tp);

/*
 * Copies the filename extension into the string that ext points to,
 * including the leading '.'. If filename doesn't have an extension,
 * ext contains the empty string.
 */
void get_filename_extension(char * ext, const char * filename);

/*
 * Copies the pathname into the string that pathname points to,
 * including the trailing '/'. If filename doesn't contain a path,
 * pathname contains the empty string.
 */
void get_pathname(char * pathname, const char * filename);

void strcatmulti(char * s, ...);

#endif
