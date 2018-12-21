/*
 * phoenix/format-two, by https://exploit.education
 *
 * Can you change the "changeme" variable?
 *
 * What kind of flower should never be put in a vase?
 * A cauliflower.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

int changeme;

void bounce(char *str) {
  printf(str);
}

int main(int argc, char **argv) {
  char buf[256];

  printf("%s\n", BANNER);

  if (argc > 1) {
    memset(buf, 0, sizeof(buf));
    strncpy(buf, argv[1], sizeof(buf));
    bounce(buf);
  }

  if (changeme != 0) {
    puts("Well done, the 'changeme' variable has been changed correctly!");
  } else {
    puts("Better luck next time!\n");
  }

  exit(0);
}
