
/*
 * phoenix/final-one, by https://exploit.education
 *
 * Even more format string fun!
 *
 * The world's leading expert on European wasps walks into a record shop. He
 * asks the assistant “Do you have ‘European Vespidae Acoustics Volume 2? I
 * believe it was released this week.”
 *
 * “Certainly,” replies the assistant. “Would you like to listen before you buy
 * it?”
 *
 * "That would be wonderful," says the expert, and puts on a pair of
 * headphones.
 *
 * He listens for a few moments and says to the assistant, “I'm terribly sorry,
 * but I am the world's leading expert on European wasps and this is not
 * accurate at all. I don't recognize any of those sounds. Are you sure this is
 * the correct recording?”
 *
 * The assistant checks the turntable, and replies that it is indeed European
 * Vespidae Acoustics Volume 2. The assistant apologizes and lifts the needle
 * onto the next track.
 *
 * Again the expert listens for a few moments and then says to the assistant,
 * "No, this just can't be right! I've been an expert in this field for 43
 * years and I still don't recognize any of these sounds."
 *
 * The assistant apologizes again and lifts the needle to the next track.
 *
 * The expert throws off the headphones as soon as it starts playing and is
 * fuming with rage.
 *
 * "This is outrageous false advertising! I am the world's leading expert on
 * European wasps and no European wasp has ever made a sound like the ones on
 * this record!"
 *
 * The manager of the shop overhears the commotion and walks over.
 *
 * "What seems to be the problem, sir?"
 *
 * "This is an outrage! I am the world's leading expert on European wasps.
 * Nobody knows more about them than I do. There is no way in hell that the
 * sounds on that record were made by European wasps!"
 *
 * The manager glances down and notices the problem instantly.
 *
 * "I'm terribly sorry, sir. It appears we've been playing you the bee side."
 */

#include <arpa/inet.h>
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>
#include <unistd.h>

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

char username[128];
char hostname[64];
FILE *output;

void logit(char *pw) {
  char buf[2048];

  snprintf(buf, sizeof(buf), "Login from %s as [%s] with password [%s]\n",
           hostname, username, pw);

  fprintf(output, buf);
}

void trim(char *str) {
  char *q;

  q = strchr(str, '\r');
  if (q) *q = 0;
  q = strchr(str, '\n');
  if (q) *q = 0;
}

void parser() {
  char line[128];

  printf("[final1] $ ");

  while (fgets(line, sizeof(line) - 1, stdin)) {
    trim(line);
    if (strncmp(line, "username ", 9) == 0) {
      strcpy(username, line + 9);
    } else if (strncmp(line, "login ", 6) == 0) {
      if (username[0] == 0) {
        printf("invalid protocol\n");
      } else {
        logit(line + 6);
        printf("login failed\n");
      }
    }
    printf("[final1] $ ");
  }
}

int testing;

void getipport() {
  socklen_t l;
  struct sockaddr_in sin;

  if (testing) {
    strcpy(hostname, "testing:12121");
    return;
  }

  l = sizeof(struct sockaddr_in);
  if (getpeername(0, (void *)&sin, &l) == -1) {
    err(1, "you don't exist");
  }

  sprintf(hostname, "%s:%d", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
}

int main(int argc, char **argv, char **envp) {
  if (argc >= 2) {
    testing = !strcmp(argv[1], "--test");
    output = stderr;
  } else {
    output = fopen("/dev/null", "w");
    if (!output) {
      err(1, "fopen(/dev/null)");
    }
  }

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  printf("%s\n", BANNER);

  getipport();
  parser();

  return 0;
}
