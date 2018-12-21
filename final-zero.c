
/*
 * phoenix/final-zero, by https://exploit.education
 *
 * The aim is to change the contents of the changeme variable.
 *
 * A woman has twins and gives them up for adoption.
 *
 * One of them goes to a family in Egypt and is named Amal. The other goes to a
 * family in Spain. They name him Juan.
 *
 * Years later, Juan sends a picture of himself to his birth mother. Upon
 * receiving the picture, she tells her husband that she wishes she also had a
 * picture of Amal. He responds, "They're twins! If you've seen Juan, you've
 * seen Amal."
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

char *gets(char *s);

/*
 * Read the username in from the network
 */

char *get_username() {
  char buffer[512];
  char *q;
  int i;

  memset(buffer, 0, sizeof(buffer));
  gets(buffer);

  /* Strip off trailing new line characters */
  q = strchr(buffer, '\n');
  if (q) *q = 0;
  q = strchr(buffer, '\r');
  if (q) *q = 0;

  /* Convert to lower case */
  for (i = 0; i < strlen(buffer); i++) {
    buffer[i] = toupper(buffer[i]);
  }

  /* Duplicate the string and return it */
  return strdup(buffer);
}

int main(int argc, char **argv, char **envp) {
  char *username;

  printf("%s\n", BANNER);
  fflush(stdout);

  username = get_username();
  printf("No such user %s\n", username);
}
