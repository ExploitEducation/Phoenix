/*
 * phoenix/net-zero, by https://exploit.education
 *
 * What did the fish say when he swam head first into a wall?
 * Dam!
 */

#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/types.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

int main(int argc, char **argv) {
  uint32_t i, j;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  printf("%s\n", BANNER);

  if (getrandom((void *)&i, sizeof(i), 0) != sizeof(i)) {
    errx(1, "unable to getrandom(%d bytes)", sizeof(i));
  }

  printf("Please send '%u' as a little endian, 32bit integer.\n", i);

  if (read(0, (void *)&j, sizeof(j)) != sizeof(j)) {
    errx(1, "unable to read %d bytes from stdin", sizeof(j));
  }

  if (i == j) {
    printf("You have successfully passed this level, well done!\n");
  } else {
    printf("Close - you sent %u instead\n", j);
  }

  return 0;
}
