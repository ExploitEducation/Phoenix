/*
 * phoenix/net-one, by https://exploit.education
 *
 * Why aren't octal jokes funny?
 * Because 7 10 11
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
  uint32_t i;
  char buf[12], fub[12], *q;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  printf("%s\n", BANNER);

  if (getrandom((void *)&i, sizeof(i), 0) != sizeof(i)) {
    errx(1, "unable to getrandom(%d bytes)", sizeof(i));
  }

  if (write(1, &i, sizeof(i)) != sizeof(i)) {
    errx(1, "unable to write %d bytes", sizeof(i));
  }

  if (fgets(buf, sizeof(buf), stdin) == NULL) {
    errx(1, "who knew that reading from stdin could be so difficult");
  }
  buf[sizeof(buf) - 1] = 0;

  q = strchr(buf, '\r');
  if (q) *q = 0;
  q = strchr(buf, '\n');
  if (q) *q = 0;

  sprintf(fub, "%u", i);
  if (strcmp(fub, buf) == 0) {
    printf("Congratulations, you've passed this level!\n");
  } else {
    printf("Close, you sent \"%s\", and we wanted \"%s\"\n", buf, fub);
  }

  return 0;
}
