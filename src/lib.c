// The author disclaims copyright to this source code.
#include "colorforth.h"
#include "cf-stdio.h"

extern hash_t hash(char *str);

void
hash_fn (struct state *s)
{
  POP1();
  char *input = CFSTRING2C(p1);
  PUSH(hash(input));
}

void
room (struct state *s)
{
//  const unsigned int defined = s->dict.latest - s->dict.entries + 1;
//  const unsigned int used = (char *)s->here - (char *)s->heap;
//  const unsigned int cell_bytes = sizeof(cell);
//  const unsigned int cell_bits = sizeof(cell) * 8;
//
//#ifdef __KEEP_ENTRY_NAMES
//  cf_printf(s, "Entries: %u/%d %u%%|Heap (bytes): %u/%d %u%%|Cell: %u bytes, %u bits\n",
//            defined, DICT_SIZE, (defined*100/DICT_SIZE),
//            used, HEAP_SIZE,(used*100/HEAP_SIZE), cell_bytes, cell_bits);
//#endif /* __KEEP_ENTRY_NAMES */
//
//  PUSH3(cell_bits, cell_bytes, HEAP_SIZE);
//  PUSH3(used, DICT_SIZE, defined);
}

void
drop_room (struct state *s)
{
  ENSURE_STACK_MIN(6);
  SP -= 6;
}

//void
//init_lib(struct state *state)
//{
//  define_primitive_extension(state, HASH_HASH,           ENTRY_NAME("hash"), hash_fn);
//  define_primitive_extension(state, ROOM_HASH,           ENTRY_NAME("room"), room);
//  define_primitive_extension(state, DROP_ROOM_HASH,      ENTRY_NAME("drop-room"), drop_room);
//}


void
parse_from_file(struct state *s, char *filename)
{
  s->tib.len = 0;
  FILE *old_stream = s->file_stream;
  s->file_stream = fopen(filename, "r");
  if (!s->file_stream)
  {
    s->file_stream = old_stream;
    cf_printf(s, "Unable to read '%s'\n", filename);
    return;
  }

  int c;
  while((c = cf_getchar(s)) != CF_EOF && !s->done)
  {
    parse_colorforth(s, c);
  }

  fclose(s->file_stream);
  s->file_stream = old_stream;

  parse_space(s);
}
