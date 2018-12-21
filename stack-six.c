/*
 * phoenix/stack-six, by https://exploit.education
 *
 * Can you execve("/bin/sh", ...) ?
 *
 * Why do fungi have to pay double bus fares? Because they take up too
 * mushroom.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

char *ret;

int main(int argc, char **argv) {
  char buffer[128];
  char *ptr;

  printf("%s\n", BANNER);

  ptr = getenv("ExploitEducation");
  if (NULL == ptr) {
    // This style of comparison prevents issues where you may accidentally
    // type if(ptr = NULL) {}..

    errx(1, "Please specify an environment variable called ExploitEducation");
  }
  ret = ptr;

  strcpy(buffer, "its a pleasure to meet you");
  strncpy(buffer + strlen(buffer), ptr,
          sizeof(buffer) - /* make sure it stays null terminated */ 1);

  // Work around GCC explicitly setting the return value to 0
  //
  // Previously, the compiler would return the value last set
  // (the return value from strncpy).
  return ret;
}
