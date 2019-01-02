/*
 * phoenix/net-two, by https://exploit.education
 *
 * Shout out to anyone who doesn't know what the opposite of in is.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/random.h>
#include <sys/types.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

int main(int argc, char **argv) {
  int i;
  unsigned long quad[sizeof(long)], result, wanted;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  printf("%s\nFor this level, sizeof(long) == %ld, keep that in mind :)\n",
      BANNER, sizeof(long));

  if (getrandom((void *)&quad, sizeof(quad), 0) != sizeof(quad)) {
    errx(1, "unable to getrandom(%d bytes)", sizeof(quad));
  }

  result = 0;
  for (i = 0; i < sizeof(long); i++) {
    result += quad[i];
    if (write(1, (void *)&quad[i], sizeof(long)) != sizeof(long)) {
      errx(1, "Why have you foresaken me, write()");
    }
  }

  if (read(0, (void *)&wanted, sizeof(long)) != sizeof(long)) {
    errx(1, "Unable to read\n");
  }

  if (result == wanted) {
    printf("You have successfully passed this level, well done!\n");
  } else {
    printf("Whoops, better luck next time. Receieved %lu, wanted %lu\n", wanted,
        result);
  }

  return 0;
}
