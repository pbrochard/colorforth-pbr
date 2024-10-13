// The author disclaims copyright to this source code.
#include <string.h>
#include "cf.h"
#include "cf-stdio.h"

int
main(int argc, char *argv[])
{
  struct state *s = cf_calloc(NULL, 1, sizeof(*s), STATE_ERROR);
  s->heap = calloc(100, sizeof(uint8_t));

  HEAP(0, uint8_t) = 'a';
  HEAP(1, uint8_t) = 'b';
  HEAP(2, cell) = 0xF8F9;

  HEAP(10, uint32_t) = (uint32_t) 0xEEAACCDD99;
  HEAP(20, uint32_t) = (uint32_t) 0xEEAACCDD;
  HEAP(30, uint64_t) = (uint64_t) 0xEEAACCDD99887766;

  HEAP(40, uint8_t) = 'c';
  HEAP(41, uint16_t) = 0xAABB;
  HEAP(44, uint8_t) = 'd';

  s->here = 50;
  HEAP(s->here, uint8_t) = 'X'; s->here += sizeof(uint8_t);
  STORE('Y', uint8_t);
  STORE(0xAABB, uint16_t);
  STORE(0xCCDDEEFF, uint32_t);

  s->here = 60;
  STORE(0xAABBCCDDEEFF9988, uint64_t);
  STORE('A', uint8_t);
  STORE('B', uint8_t);

  printf("\n\n[00]\t");

  for (int i = 0; i < 99; i++) {
    printf("%10X ", *((uint8_t *)s->heap + i));
    if ((i + 1) % 10 == 0) printf("\n[%d]\t", i+1);
  }

  return 0;
}
