// The author disclaims copyright to this source code.
#include "cf.h"

void (*echo_color)(struct state *s, int c, char *color);
void (*init_terminal)(void);
void (*reset_terminal)(void);

#ifdef __ECHO_COLOR

#include "cf-stdio.h"
#include <unistd.h>
#include <termios.h>

struct termios old_tio;

void
echo_color_(struct state *s, int c, char *color)
{
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
}

void
init_terminal_(void)
{
  struct termios new_tio;
  tcgetattr(STDIN_FILENO,&old_tio);
  new_tio=old_tio;
  new_tio.c_lflag &=(~ICANON & ~ECHO);
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
}

void
reset_terminal_(void)
{
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
  printf("%s", COLOR_CLEAR);
}

#endif /* __ECHO_COLOR */

void
echo_color_no_(struct state *s, int c, char *color)
{
}

void
init_terminal_no_(void)
{
}

void
reset_terminal_no_(void)
{
}



void
init_color_fns (void)
{
#ifdef __ECHO_COLOR
  echo_color = echo_color_;
  init_terminal = init_terminal_;
  reset_terminal = reset_terminal_;
#endif /* __ECHO_COLOR */
}


void
init_no_color_fns (void)
{
  echo_color = echo_color_no_;
  init_terminal = init_terminal_no_;
  reset_terminal = reset_terminal_no_;
}
