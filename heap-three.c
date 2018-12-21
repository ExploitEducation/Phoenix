/*
 * phoenix/heap-zero, by https://exploit.education
 *
 * This level is linked against //gee.cs.oswego.edu/pub/misc/malloc-2.7.2.c
 * version 2.7.2, with a SHA1 sum of 407329d164e4989b59b9a828760acb720dc5c7db
 * more commonly known as "dlmalloc", Doug Lea Malloc
 *
 * Can you hijack flow control, and execute winner()? Afterwards, how
 * about your own code? This level is solvable on Linux i386 easily enough,
 * as for other architectures, it may not be possible, or may require some
 * creativity - let me know what you come up with :)
 *
 * My friend told me that nothing rhymes with orange.
 * I told them, "No, it doesn't".
 *
 * Or, more seriously, https://www.youtube.com/watch?v=lPcR5RVXHMg
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void winner() {
  printf("Level was successfully completed at @ %ld seconds past the Epoch\n",
         time(NULL));
}

int main(int argc, char **argv) {
  char *a, *b, *c;

  a = malloc(32);
  b = malloc(32);
  c = malloc(32);

  strcpy(a, argv[1]);
  strcpy(b, argv[2]);
  strcpy(c, argv[3]);

  free(c);
  free(b);
  free(a);

  printf("dynamite failed?\n");
}
