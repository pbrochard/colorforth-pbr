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
  parse_from_string(s, " ");
// 	parse_from_string(s, "cr s\" This is a colorForth inspired implementation\" prn\n");
// 	parse_from_string(s, "s\"   source code: https://github.com/pbrochard/colorforth-pbr\" prn\n");
// 	parse_from_string(s, "s\" Try for example: 2 2 + .\" prn\n");
// 	parse_from_string(s, "cr s\" Here are the defined words:\" prn\n\n");
}
