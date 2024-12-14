// The author disclaims copyright to this source code.
#include "cf.h"
#include "cf-stdio.h"

#ifdef __ECHO_COLOR
#include <unistd.h>
#include <termios.h>

struct termios old_tio;
#endif /* __ECHO_COLOR */

void
echo_color(struct state *s, int c, char *color)
{
#ifdef __ECHO_COLOR
  if (s->echo_on)
  {
    if (color)
    {
      cf_printf(s, "%s%c", color, c);
    }
    else
    {
      cf_printf(s, "%c", c);
    }
  }
  else if (color)
  {
    cf_printf(s, "%s", color);
  }
#else
  if (s->echo_on)
  {
    cf_printf(s, "%c", c);
  }
#endif /* __ECHO_COLOR */
}

void
init_terminal(void)
{
#ifdef __ECHO_COLOR
  struct termios new_tio;
  tcgetattr(STDIN_FILENO,&old_tio);
  new_tio=old_tio;
  new_tio.c_lflag &=(~ICANON & ~ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
#endif /* __ECHO_COLOR */
}

void
reset_terminal(void)
{
#ifdef __ECHO_COLOR
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
  printf("%s", COLOR_CLEAR);
#endif /* __ECHO_COLOR */
}
