#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char ** args) {
  char * buf;
  int len = 50;

  buf = malloc(len);
  while (!getcwd(buf, len)) {
    len += 50;
    buf = realloc(buf, len);
  }

  printf("Current working directory: %s\nLength: %d\n", buf, len);

  DIR* cwd = opendir(buf);
  struct dirent* ent;
  while ((ent = readdir(cwd))) {
    puts(ent->d_name);
  }

  closedir(cwd);

  free(buf);
}
