// The author disclaims copyright to this source code.
#include <string.h>
#include "colorforth.h"
#include "cf-stdio.h"

extern void parse_from_file(struct state *s, char *filename);

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
  for (int i = 1; i < argc; i++)
  {
    if (memcmp(argv[i], "-e", 2) == 0)
    {
      nextIsEval = 1;
      continue;
    }

    if (nextIsEval)
    {
      parse_from_string(s, argv[i]);
      nextIsEval = 0;
      continue;
    }

    parse_from_file(s, argv[i]);
  }

  s->echo_on = 1;

  parse_colorforth(s, '~');
}



int
main(int argc, char *argv[])
{
  if (argc ==3 && memcmp(argv[1], "--hash", 6) == 0) {
    printf("0x%X", hash(argv[2]));
    return 0;
  }

  init_terminal();

  struct state *s = colorforth_newstate();

  parse_home_lib(s, argc, argv);
  parse_command_line(s, argc, argv);

  while (!s->done)
  {
    parse_colorforth(s, cf_getchar(s));
  }

  free_state(s);

  reset_terminal();

  return 0;
}
