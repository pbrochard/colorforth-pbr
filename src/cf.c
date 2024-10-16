// The author disclaims copyright to this source code.

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "cf.h"
#include "cf-stdio.h"
#include "utils.h"

#ifdef __KEEP_ENTRY_NAMES
#define ENTRY_NAME(name) (name)
#else
#define ENTRY_NAME(name) (NULL)
#endif /* __KEEP_ENTRY_NAMES */

#define __SECTION_HASH_DEF
#include "core.c"
#include "ext.c"
#include "lib.c"
#undef __SECTION_HASH_DEF

#ifdef __CHECK_DICT
extern char check_entry(struct state *s, struct entry *check_entry);
extern void display_clash_found(struct state *s, char clash_found);
#endif /* __CHECK_DICT */

#define __SECTION_FUNCTION
#include "core.c"
#include "ext.c"
#include "lib.c"
#undef __SECTION_FUNCTION


// 'hashed_name' is 'hash(name)' or 0x0 if names are kept
// 'name' must be null-terminated.
static void
define_primitive(struct state *s, char name[] __attribute__((unused)), hash_t hashed_name)
{
  cell entry_index = find_entry_by_hash(&s->dict, hashed_name);

  if (entry_index != -1)
  {
#ifdef __KEEP_ENTRY_NAMES
    struct entry *found_entry = ENTRY(entry_index);
    cf_printf(s, "'%s' clash with '%s'\n", name, found_entry->name);
#endif /* __KEEP_ENTRY_NAMES */

    cf_fatal_error(s, DUPLICATE_HASH_ERROR);
  }

  s->dict.latest++;
  struct entry *entry = ENTRY(s->dict.latest);

  entry->opcode = hashed_name;

  entry->mode = CORE;
  entry->offset = s->here;
  STORE(entry->opcode, opcode_t);
  STORE(OP_RETURN, opcode_t);

#ifdef __KEEP_ENTRY_NAMES
  entry->name_len = strlen(NON_NULL(name));
  entry->name = cf_calloc(s, 1, entry->name_len + 1, PRIMITIVE_ERROR);
  memcpy(entry->name, NON_NULL(name), entry->name_len);
#endif /* __KEEP_ENTRY_NAMES */

#ifdef __SHOW_MISSING_HASH
#ifdef __KEEP_ENTRY_NAMES
  char *up_name = cf_calloc(s, 1, entry->name_len + 1, PRIMITIVE_ERROR);
  memcpy(up_name, name, entry->name_len + 1);

  char *p = up_name;
  while((*p=toupper(*p))) p++;

  cf_printf(s, "%20s <-> %-20lX   hashed_name=%-20lX | %20s_HASH %20lX | %20s\n", name, entry->opcode, hashed_name, up_name, hash(name), entry->name);

  free(up_name);
#else
  cf_printf(s, "%-20lX %lX\n", entry->opcode, hashed_name);
#endif /* __KEEP_ENTRY_NAMES */
#endif /* __SHOW_MISSING_HASH */
}

/**
 *
 * Color functions
 *
 **/
static void
define(struct state *s)
{
  struct dictionary * dict = &s->dict;
  dict->latest++;
  struct entry *entry = &dict->entries[dict->latest];

  entry->opcode = hash(s->tib.buf);

#ifdef __KEEP_ENTRY_NAMES
  entry->name_len = s->tib.len;
  entry->name = cf_calloc(s, 1, entry->name_len + 1, DEFINE_ERROR);
  memcpy(entry->name, s->tib.buf, s->tib.len);

#ifdef __LIVE_CHECK_DICT
  // TODO
  //if (check_entry(s, entry)) display_clash_found(s, 1);
#endif /* __LIVE_CHECK_DICT */
#endif /* __KEEP_ENTRY_NAMES */

  entry->offset = s->here;
  entry->mode = CALL;
  // printf("\ndefine: %s offset=%ld\n", entry->name, entry->offset);
}

static void
compile_entry(struct state *s, cell entry_index)
{
  struct entry* entry = ENTRY(entry_index);
  if (entry->mode == CORE) {
    STORE(entry->opcode, opcode_t);
  } else if (entry_index == s->dict.latest) {
    STORE(OP_TAIL_CALL, opcode_t);
    STORE(entry_index, cell);
  } else {
    STORE(OP_CALL, opcode_t);
    STORE(entry_index, cell);
  }
}

static void
compile_literal(struct state *s, cell n)
{
  STORE(OP_NUMBER, opcode_t);
  STORE(n, cell);
}

static void
compile(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index != -1)
  {
    compile_entry(s, entry_index);
  }
  else
  {
    // try to interpret as an unsigned decimal number
    cell n = 0;
    if (tib_to_number(s, &n))
    {
      compile_literal(s, n);
    }
    else
    {
      unknow_word(s);
    }
  }
}

void
execute_(struct state *s, struct entry *entry)
{
  // cf_printf(s, "-> %s offset=%d\n", entry->name, entry->offset);
  PC = entry->offset;

  ENSURE_R_STACK_MAX(1);
  R_PUSH(-1);

#ifdef __USE_REGISTER
  register cell A = 0;
  register cell B = 0;
  register cell I = 0;
  register cell J = 0;
  register cell K = 0;
#endif


  // don't forget to COMPILE a return!!!!
  while(1)
  {
    switch (HEAP(PC, opcode_t))
    {
      case OP_RETURN:
      {
        ENSURE_R_STACK_MIN(1);
        cell offset = R_POP();
        if (offset == -1) {
          // cf_printf(s, "   %s(done) <-\n", entry->name);
          clear_r_stack(s);
          return ;
        }
        PC = offset;
        continue;
      }

#define __SECTION_SWITCH
#include "core.c"
#include "ext.c"
#include "lib.c"
#undef __SECTION_SWITCH

      default:
      {
        cf_printf(s, "??");
      }
    }
    PC += sizeof(opcode_t);
  }
}

void
execute(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index != -1)
  {
    execute_(s, ENTRY(entry_index));
  }
  else
  {
    // try to interpret as an unsigned decimal number
    cell n = 0;
    if (tib_to_number(s, &n))
    {
      ENSURE_STACK_MAX(1);
      PUSH(n);
    }
    else
    {
      unknow_word(s);
      return;
    }
  }
}

static void
tick(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index == -1) {
    unknow_word(s);
    return;
  }

  ENSURE_STACK_MAX(1);
  PUSH(ENTRY(entry_index)->offset);
}

static void
compile_tick(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index == -1) {
    unknow_word(s);
    return;
  }

  STORE(OP_TICK_NUMBER, opcode_t);
  STORE(ENTRY(entry_index)->offset, cell);
}

static void
tick_entry(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index == -1) {
    unknow_word(s);
    return;
  }

  ENSURE_STACK_MAX(1);
  PUSH(entry_index);
}

static void
compile_tick_entry(struct state *s)
{
  cell entry_index = find_entry(s, &s->dict);
  if (entry_index == -1) {
    unknow_word(s);
    return;
  }

  STORE(OP_TICK_NUMBER, opcode_t);
  STORE(entry_index, cell);
}

void
init_stack(struct stack *stack, int len, unsigned char id)
{
  stack->cells = cf_calloc(NULL, len, sizeof(cell), id);
  stack->sp = -1;
  stack->lim = len - 1;
}

void
free_stack(struct stack *stack)
{
  free(stack->cells);
  free(stack);
}

void
free_dictionary(struct dictionary *dict)
{
#ifdef __KEEP_ENTRY_NAMES
  for (int i = dict->latest; i >= 0; i--)
  {
    if (dict->entries[i].name != NULL) free(dict->entries[i].name);
  }
#endif

  free(dict->entries);
}

void
parse_colorforth(struct state *s, int c)
{
  if (s->tib.len == 0) {
    // Handle prefix
    switch(c) {
#define __SECTION_PREFIX_DEF
#include "core.c"
#include "ext.c"
#include "lib.c"
#undef __SECTION_PREFIX_DEF
    }
  }

  if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
  {
    echo_color(s, c, NULL);
    if (s->tib.len == 0)
    {
      // Strip leading whitespace.
    }
    else
    {
      // Have word.
      s->color(s);
      clear_tib(s);
    }

    return;
  }

  if (c == CF_EOF)
  {
    echo_color(s, c, COLOR_CLEAR);
    return;
  }

  if (c == '\b' || c == 127)
  {
    if (s->tib.len > 0)
    {
      cf_printf(s, "\b \b");
      s->tib.len -= 1;
    }
    return;
  }

  echo_color(s, c, NULL);
  if (s->tib.len < sizeof(s->tib.buf))
  {
    s->tib.buf[s->tib.len++] = c;
  }
}

void
parse_space(struct state *s)
{
  char *old_str_stream = s->str_stream;
  FILE *old_file_stream = s->file_stream;

  s->str_stream = NULL;
  s->file_stream = NULL;

  parse_colorforth(s, ' '); parse_colorforth(s, '~');

  s->str_stream = old_str_stream;
  s->file_stream = old_file_stream;
}

void
parse_from_string(struct state *s, char *str)
{
  char *old_stream = s->str_stream;

  s->str_stream = str;
  int c;
  while((c = (char) cf_getchar(s)) != 0 && !s->done && s->str_stream)
  {
    parse_colorforth(s, c);
  }

  parse_colorforth(s, ' ');

  s->str_stream = old_stream;

  parse_space(s);
}

struct state*
colorforth_newstate(void)
{
  struct state *s = cf_calloc(NULL, 1, sizeof(*s), STATE_ERROR);
  s->color = execute;

  s->base = 10;

  s->stack = cf_calloc(s, 1, sizeof(struct stack), STACK_ERROR);
  init_stack(s->stack, STACK_SIZE, STACK_INIT_ERROR);

  s->r_stack = cf_calloc(s, 1, sizeof(struct stack), RSTACK_ERROR);
  init_stack(s->r_stack, R_STACK_SIZE, RSTACK_INIT_ERROR);

  s->dict.entries = cf_calloc(s, DICT_SIZE, sizeof(struct entry), DICT_ERROR);
  s->dict.latest = -1;

  s->heap = cf_calloc(s, 1, HEAP_SIZE, HEAP_ERROR);
  s->here = 0;
  STORE(OP_NOP, opcode_t);
  STORE(OP_RETURN, opcode_t);

  s->done = 0;
  s->echo_on = 0;

  s->str_stream = NULL;
  s->file_stream = NULL;

#define __SECTION_WORD_DEF
#include "core.c"
#include "ext.c"
#include "lib.c"
#undef __SECTION_WORD_DEF

  s->color = execute;
  echo_color(s, '~', COLOR_YELLOW);
  s->echo_on = 1;

  return s;
}

void
free_state(struct state *s)
{
  free(s->heap);

  free_dictionary(&s->dict);

  free_stack(s->r_stack);
  free_stack(s->stack);

#ifdef __EXTENDED_MATH
  free(s->fstack.cells);
#endif

#ifdef __MP_MATH
  free(s->mpstack.cells);
#endif

  free(s);
}
