// The author disclaims copyright to this source code.
#include <string.h>

#include "cf.h"
#include "cf-stdio.h"

#ifdef __EXCEPTION
#include <signal.h>
#include <setjmp.h>
#endif /* __EXCEPTION */


struct state *s;

#ifndef __MINIMAL_BUILD

extern void parse_from_file(struct state *s, char *filename);
extern void reset_state(struct state *s);
extern void show_full_stacktrace(struct state *s);

void
parse_home_lib(struct state *s, int argc, char *argv[]) {
#ifdef config_file
  for (int i = 1; i < argc; i++)
  {
    if (memcmp(argv[i], "-n", 2) == 0) return;
  }

  char *filename = calloc(1024, sizeof(char));

  s->echo_on = 0;

  strcat(filename, getenv("HOME"));
  strcat(filename, "/");
  strcat(filename, config_file);

  parse_from_file(s, filename);

  free(filename);

  s->echo_on = 1;
#endif
}

void
parse_command_line(struct state *s, int argc, char *argv[])
{
  s->echo_on = 0;

  char nextIsEval = 0;
  char hasColor = 1;
  for (int i = 1; i < argc; i++)
  {
    if (memcmp(argv[i], "-e", 2) == 0)
    {
      nextIsEval = 1;
      continue;
    }

    if (memcmp(argv[i], "-d", 2) == 0)
    {
      hasColor = 0;
      continue;
    }

    if (nextIsEval)
    {
      parse_colorforth(s, '~');
      parse_from_string(s, argv[i]);
      cf_printf(s, "\n");
      nextIsEval = 0;
      continue;
    }

    parse_from_file(s, argv[i]);
  }

  if (hasColor) init_color_fns();
}

#ifdef __EXCEPTION
sigjmp_buf mark;


void
print_exception(char *msg, siginfo_t *info) {
  printf("%s", COLOR_RED);
  printf("\n%s (%d)%s\n", strsignal(info->si_signo), info->si_signo, msg);
  printf("Stacktrace:");
  show_full_stacktrace(s);
}

void
handler0(int signo, siginfo_t *info, void *context)
{
  print_exception("\nFailed to parse command line arguments", info);
  reset_terminal();
  exit(1);
}

void
handler(int signo, siginfo_t *info, void *context)
{
  print_exception("", info);
  siglongjmp(mark, -1);
}

void
install_sigaction (void (*sigact)(int, siginfo_t *, void *)) {
  struct sigaction act = { 0 };
  act.sa_sigaction = sigact;
  act.sa_flags = SA_SIGINFO;
  sigemptyset(&(act.sa_mask));
  sigaddset(&(act.sa_mask), SIGSEGV);
  sigaction(SIGSEGV, &act, NULL);
  sigaction(SIGFPE, &act, NULL);
}
#endif /* __EXCEPTION */


#endif /* __MINIMAL_BUILD */

int
main(int argc, char *argv[])
{
  if (argc ==3 && memcmp(argv[1], "--hash", 6) == 0) {
    printf("0x%X", hash(argv[2]));
    return 0;
  }

  init_no_color_fns();

  s = colorforth_newstate();

#ifndef __MINIMAL_BUILD

#ifdef __EXCEPTION
  install_sigaction(&handler0);
#endif /* __EXCEPTION */

  parse_home_lib(s, argc, argv);
  parse_command_line(s, argc, argv);

  init_terminal();

  parse_colorforth(s, '~');
  s->echo_on = 1;

#ifdef __EXCEPTION
  install_sigaction(&handler);

  if (sigsetjmp(mark, 1) == -1) reset_state(s);
#endif /* __EXCEPTION */

#endif /* __MINIMAL_BUILD */

  while (!s->done)
  {
    parse_colorforth(s, cf_getchar(s));
  }

  free_state(s);

  reset_terminal();

  return 0;
}
