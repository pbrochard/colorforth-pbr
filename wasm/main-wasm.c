// The author disclaims copyright to this source code.
#include <string.h>
#include "colorforth.h"
#include "cf-stdio.h"

#include <emscripten/emscripten.h>

struct state *s;

EMSCRIPTEN_KEEPALIVE
void parse_cf(int c) {
  parse_colorforth(s, c);
}

int
main(int argc, char *argv[])
{
  s = colorforth_newstate();
  cf_printf(s, "This is a colorForth inspired implementation\n");
  cf_printf(s, "   source code: https://github.com/pbrochard/colorforth-pbr\n");
  cf_printf(s, "Try for example: `2 2 + .`\n");
  cf_printf(s, "Type `words` the see the defined words\n");
  cf_printf(s, "~\n");
}
