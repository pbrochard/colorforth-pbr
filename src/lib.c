// The author disclaims copyright to this source code.

#ifndef __MINIMAL_BUILD

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_CLEAR                     (opcode_t) 0x93C5A06D                // clear
#define OP_RESET_STATE               (opcode_t) 0xEAA6ED6B                // reset-state
#define OP_HASH                      (opcode_t) 0x3475B2F0                // hash
#define OP_BASE                      (opcode_t) 0x7D3CE245                // base
#define OP_ENTRY_IS                  (opcode_t) 0xDB70432B                // is!
#define OP_ENTRY_C_IS                (opcode_t) 0xBBBFB2BC                // c>is!
#define OP_ENTRY_HIDE                (opcode_t) 0x7C95E439                // entry/hide
#define OP_ROOM                      (opcode_t) 0xE48409A3                // room
#define OP_DROP_ROOM                 (opcode_t) 0xC57E1E23                // drop-room
#define OP_DOT_STACKTRACE            (opcode_t) 0xC6A520A7                // .stacktrace
#define OP_DOT_FULL_STACKTRACE       (opcode_t) 0x306C1267                // .full-stacktrace

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("clear"), OP_CLEAR);
define_primitive(s, ENTRY_NAME("reset-state"), OP_RESET_STATE);
define_primitive(s, ENTRY_NAME("hash"), OP_HASH);
define_primitive(s, ENTRY_NAME("base"), OP_BASE);
define_primitive(s, ENTRY_NAME("is!"), OP_ENTRY_IS);
define_primitive(s, ENTRY_NAME("c>is!"), OP_ENTRY_C_IS);
define_primitive(s, ENTRY_NAME("entry/hide"), OP_ENTRY_HIDE);
define_primitive(s, ENTRY_NAME(".stacktrace"), OP_DOT_STACKTRACE);
define_primitive(s, ENTRY_NAME(".full-stacktrace"), OP_DOT_FULL_STACKTRACE);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_CLEAR:
{
  SP = -1;
  break;
}

case OP_RESET_STATE:
{
  reset_state(s);
  return;
}

case OP_HASH: {
  POP1();
  PUSH((cell) hash(CFSTRING2C(p1)));
  break;
}

case OP_BASE: {
  ENSURE_STACK_MAX(1);
  PUSH((cell) &s->base);
  break;
}

case OP_ENTRY_IS: {
  POP2();
  ENTRY(p1)->offset = ENTRY(p2)->offset;
  break;
}

case OP_ENTRY_C_IS: {
  POP2();
  ENTRY(p1)->offset = p2;
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

case OP_DOT_STACKTRACE: {
  cf_printf(s, "\n");
  show_stacktrace(s);
  break;
}

case OP_DOT_FULL_STACKTRACE: {
  show_full_stacktrace(s);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

extern hash_t hash(char *str);

void
reset_state(struct state *s) {
  s->done = 0;
  s->stack->sp = -1;
  s->r_stack->sp = -1;
  s->color = execute;
  s->str_stream = NULL;
  if (s->file_stream) {
    fclose(s->file_stream);
    s->file_stream = NULL;
  }
  clear_tib(s);
  s->echo_on = 0;
  parse_from_string(s, " ~");
  s->echo_on = 1;
}

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
  while((c = cf_getchar(s)) != CF_EOF && !s->done && s->file_stream)
  {
    parse_colorforth(s, c);
  }

  if (s->file_stream) fclose(s->file_stream);
  s->file_stream = old_stream;

  parse_space(s);
}

#endif /* __SECTION_FUNCTION */

#endif /* __MINIMAL_BUILD */
