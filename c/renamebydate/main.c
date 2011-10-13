#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "bintree.h"
#include "util.h"

struct file_info_t {
  char * name;
  time_t mod_time;
};
typedef struct file_info_t * file_info;

int file_info_compare(void * fi_1, void * fi_2) {
  time_t mt_1 = ((file_info) fi_1)->mod_time;
  time_t mt_2 = ((file_info) fi_2)->mod_time;

  if (mt_1 < mt_2) {
    return -1;
  } else { // files may have identical mod_times, don't drop them accidentally
    return 1;
  }
}

char* construct_new_filename(const char* filename, const char* date_str, 
			     const int count) {
  char* pathname = (char*) malloc(strlen(filename));
  get_pathname(pathname, filename);

  // add 1 because we floor(), another 1 for '\0':
  char* count_str = (char*) malloc(floor(log10(count)) + 2); 
  sprintf(count_str, "%d", count);

  char* ext = (char*) malloc(strlen(filename));
  get_filename_extension(ext, filename);
  
  char* new_filename = (char*) malloc(strlen(pathname) + strlen(ext)
				      + strlen(date_str) + strlen("_") 
				      + strlen(count_str) + 1);
  strcpy(new_filename, "");

  strcatmulti(new_filename, pathname, date_str, "_", count_str, ext, NULL);

  free(pathname);
  free(count_str);
  free(ext);

  return new_filename;
}

static int do_rename = 0;

void file_info_action(void * object) {
  static char* curr_date_str = NULL;
  static int count = 1;

  file_info fi = (file_info) object;

  char* date_str = (char *) malloc(100*sizeof(char)); // hopefully large enough
  get_date_string(date_str, localtime(&fi->mod_time));

  if (!curr_date_str || strcmp(curr_date_str, date_str)) {
    count = 1;
    free(curr_date_str);
    curr_date_str = date_str;
  } else {
    count++;
    free(date_str);
  }

  char* new_filename = construct_new_filename(fi->name, curr_date_str, count);

  if (!do_rename) {
    printf("%s -> %s\n", fi->name, new_filename);
  } else {
    if (rename(fi->name, new_filename)) {
      fprintf(stderr, "Couldn't rename %s to %s\n", fi->name, new_filename);
    }
  }

  free(new_filename);
}

int main(int argc, char* argv[]) {
  tree t = create_tree(file_info_compare);

  if (argc > 1) {
    if (strcmp(*(argv+1), "-x") == 0) {
      do_rename = 1;
      argc--;
      argv++;
    } else if (strcmp(*(argv+1), "-t") == 0) {
      do_rename = 0;
      argc--;
      argv++;
    } else {
      do_rename = 0;
    }
  }

  while (--argc > 0) {
     if (is_file(*++argv) <= 0) { 
       continue; 
     } 

    file_info fi = (file_info) malloc(sizeof(struct file_info_t));
    fi->name = *argv;
    fi->mod_time = get_modification_time(fi->name);

    add_object(t, fi);
  }

  walk_tree(t, file_info_action);

  destruct_tree(t);

  exit(0);
}

