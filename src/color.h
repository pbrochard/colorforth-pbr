// The author disclaims copyright to this source code.
#ifndef __ECHO_COLOR_H
#define __ECHO_COLOR_H

extern void init_color_fns(void);
extern void init_no_color_fns(void);

#define COLOR_RED      "\x1B[01;91m"
#define COLOR_MAGENTA  "\x1B[01;95m"
#define COLOR_GREEN    "\x1B[01;92m"
#define COLOR_YELLOW   "\x1B[01;93m"
#define COLOR_BLUE     "\x1B[01;94m"
#define COLOR_CYAN     "\x1B[01;96m"
#define COLOR_WHITE    "\x1B[01;37m"
#define COLOR_CLEAR    "\x1B[0m"

//extern void (*echo_color)(struct state *state, int c, char *color);
extern void (*echo_color)();
extern void (*init_terminal)(void);
extern void (*reset_terminal)(void);

#endif /* __ECHO_COLOR_H */
