
/*
 * phoenix/final-two, by https://exploit.education
 *
 * This level is linked against ftp://gee.cs.oswego.edu/pub/misc/malloc.c
 * version 2.7.2, with a SHA1 sum of 407329d164e4989b59b9a828760acb720dc5c7db
 *
 * Can you get a shell via heap corruption?
 *
 * A man drives train for a living in Bulgaria. He absolutely loved his job,
 * and it had been his dream job ever since he was a child. One day, he falls
 * asleep driving, and runs over someone walking on the tracks. Well, his case
 * goes to court, and the court finds him guilty of murder, as had he not been
 * asleep, he could have sounded the horn, or stopped for the person.  The
 * punishment for such recklessness is the death penalty. So, he's on death row
 * and the executioner approaches him.
 *
 * "What would you like for your last meal?"
 *
 * "I would like a banana please."
 *
 * The executioner thinks it's weird, but shrugs and gives him a banana. The
 * guy eats his banana, waits awhile, and gets strapped into the electric
 * chair. When the flip the switch, nothing happens! In Bulgaria, an act of
 * divine intervention means you get released.
 *
 * A few months go by, and the train driver has been working for a new company.
 * Well, old habits die hard, and he falls asleep again. This time, he killed 2
 * people. Bulgarian courts have no patience for recklessness, so he ends up on
 * death row again. After awhile, the same executioner from last time
 * approaches him.
 *
 * "You again? Shit. What do you want this time?"
 *
 * "Two bananas please."
 *
 * The executioner shrugs and hands him two bananas. A bit weird, but whatever.
 * There's no way he can cheat death twice! But, when they flip the switch,
 * nothing happens again. The train driver walks a second time.
 *
 * Some time passes, and the executioner is very busy. After another few
 * months, the same dude shows up, apparently having run over 3 people with a
 * train. Exacerbated, the executioner approaches him for the third time.
 *
 * "Let me guess. Three bananas?"
 *
 * "Actually yes! How did you know?"
 *
 * "Too bad! This has gone on long enough. No more bananas! Today you fry."
 *
 * So, the train driver gets strapped into the chair with no last meal. But,
 * when they flip the switch, nothing happens again.
 *
 * "I dont get it," says the executioner. "I didnt let you eat any bananas!"
 *
 * "Its not the bananas. It's just that I'm a bad conductor."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REQSZ 128

#define BANNER \
  "Welcome to " LEVELNAME ", brought to you by https://exploit.education"

void check_path(char *buf) {
  char *start;
  char *p;
  int l;

  /*
   * Work out old software bug
   */

  p = rindex(buf, '/');
  l = strlen(p);
  if (p) {
    start = strstr(buf, "ROOT");
    if (start) {
      while (*start != '/') start--;
      memmove(start, p, l);
    }
  }
}

void get_requests(int in_fd, int out_fd) {
  char *buf;
  char *destroylist[256];
  int dll;
  int i;

  dll = 0;
  while (1) {
    if (dll >= 255) break;

    buf = calloc(REQSZ, 1);
    if (read(in_fd, buf, REQSZ) != REQSZ) break;

    if (strncmp(buf, "FSRD", 4) != 0) break;

    check_path(buf + 4);

    dll++;
  }

  for (i = 0; i < dll; i++) {
    write(out_fd, "Process OK\n", strlen("Process OK\n"));
    free(destroylist[i]);
  }
}

int main(int argc, char **argv, char **envp) {
  printf("%s\n", BANNER);
  fflush(stdout);

  get_requests(0, 1);
  return 0;
}
