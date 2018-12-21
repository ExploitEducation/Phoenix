/*
 * phoenix/heap-two, by https://exploit.education
 *
 * This level examines what can happen when heap pointers are stale. This level
 * is completed when you see the "you have logged in already!" message.
 *
 * My dog would, without fail, always chase people on a bike. As soon as he saw
 * someone, he would immediately take off. I spoke to the vet to see if they
 * could be of any help, but they weren't. I spoke to several different dog
 * behaviouralists to see if they have any ideas on how to stop getting him
 * chasing people on a bike. The dog behaviouralists were unable to help. I
 * searched high and low to work out ways to find a way to stop him from
 * chasing people on a bike, to no avail. Eventually, I had no choice but to
 * take the bike away from him.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

struct auth {
  char name[32];
  int auth;
};

struct auth *auth;
char *service;

int main(int argc, char **argv) {
  char line[128];

  printf("%s\n", BANNER);

  while (1) {
    printf("[ auth = %p, service = %p ]\n", auth, service);

    if (fgets(line, sizeof(line), stdin) == NULL) break;

    if (strncmp(line, "auth ", 5) == 0) {
      auth = malloc(sizeof(struct auth));
      memset(auth, 0, sizeof(struct auth));
      if (strlen(line + 5) < 31) {
        strcpy(auth->name, line + 5);
      }
    }
    if (strncmp(line, "reset", 5) == 0) {
      free(auth);
    }
    if (strncmp(line, "service", 6) == 0) {
      service = strdup(line + 7);
    }
    if (strncmp(line, "login", 5) == 0) {
      if (auth && auth->auth) {
        printf("you have logged in already!\n");
      } else {
        printf("please enter your password\n");
      }
    }
  }
}
