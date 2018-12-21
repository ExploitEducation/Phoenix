/*
 * phoenix/format-three, by https://exploit.education
 *
 * Can you change the "changeme" variable to a precise value?
 *
 * How do you fix a cracked pumpkin? With a pumpkin patch.
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
  char buf[4096];
  printf("%s\n", BANNER);

  if (read(0, buf, sizeof(buf) - 1) <= 0) {
    exit(EXIT_FAILURE);
  }

  bounce(buf);

  if (changeme == 0x64457845) {
    puts("Well done, the 'changeme' variable has been changed correctly!");
  } else {
    printf("Better luck next time - got 0x%08x, wanted 0x64457845!\n",
           changeme);
  }

  exit(0);
}
