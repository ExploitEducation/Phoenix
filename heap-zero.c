/*
 * phoenix/heap-zero, by https://exploit.education
 *
 * Can you hijack flow control, and execute the winner function?
 *
 * Why do C programmers make good Buddhists?
 * Because they're not object orientated.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

struct data {
  char name[64];
};

struct fp {
  void (*fp)();
  char __pad[64 - sizeof(unsigned long)];
};

void winner() {
  printf("Congratulations, you have passed this level\n");
}

void nowinner() {
  printf(
      "level has not been passed - function pointer has not been "
      "overwritten\n");
}

int main(int argc, char **argv) {
  void *discard;
  struct data *d;
  struct fp *f;
  int i;

  printf("%s\n", BANNER);

  if (argc < 2) {
    printf("Please specify an argument to copy :-)\n");
    exit(1);
  }

  /*
   * https://github.com/esmil/musl/blob/master/src/ldso/dynlink.c#L396-L416
   * work around the cleverness of the dynamic linker reclaiming unused
   * writable pages of shared libraries.
   */

  for (i = 0; i < 3; i++) discard = malloc(sizeof(struct data));

  d = malloc(sizeof(struct data));
  f = malloc(sizeof(struct fp));
  f->fp = nowinner;

  strcpy(d->name, argv[1]);

  printf("data is at %p, fp is at %p, will be calling %p\n", d, f, f->fp);
  fflush(stdout);

  f->fp();

  return 0;
}
