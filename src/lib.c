// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_HASH                      (opcode_t) 0x3475B2F0                // hash
#define OP_BASE                      (opcode_t) 0x7D3CE245                // base
#define OP_ENTRY_IS                  (opcode_t) 0x84041728                // is
#define OP_ENTRY_C_IS                (opcode_t) 0x6F1B27F5                // c>is
#define OP_ENTRY_HIDE                (opcode_t) 0x7C95E439                // entry/hide
#define OP_ROOM                      (opcode_t) 0xE48409A3                // room
#define OP_DROP_ROOM                 (opcode_t) 0xC57E1E23                // drop-room

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("base"), OP_BASE);
define_primitive(s, ENTRY_NAME("is"), OP_ENTRY_IS);
define_primitive(s, ENTRY_NAME("c>is"), OP_ENTRY_C_IS);
define_primitive(s, ENTRY_NAME("entry/hide"), OP_ENTRY_HIDE);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_BASE: {
  ENSURE_STACK_MAX(1);
  PUSH((cell) &s->base);
  break;
}

case OP_ENTRY_IS: {
  POP2();
  ENTRY(p2)->offset = ENTRY(p1)->offset;
  break;
}

case OP_ENTRY_C_IS: {
  POP2();
  ENTRY(p2)->offset = p1;
  break;
}

case OP_ENTRY_HIDE: {
  POP1();

  ENTRY(p1)->opcode = 0;
#ifdef __KEEP_ENTRY_NAMES
  free(entry->name);
  entry->name = NULL;
  entry->name_len = 0;
#endif

  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

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

#endif /* __SECTION_FUNCTION */
