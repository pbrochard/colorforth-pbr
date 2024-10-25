// The author disclaims copyright to this source code.
#include <stdbool.h>
#include <string.h>

#include "cf.h"
#include "cf-stdio.h"

void
cf_print_cell(struct state *s, cell cell)
{
  switch (s->base)
  {
    case 16:
    {
      cf_printf(s, "0x%02lX", cell);
      break;
    }
    case 2:
    {
      cf_putchar(s, 'b');
      if (cell == 0)
      {
        cf_printf(s, "0 ");
      } else {
        int i = CF_CHAR_BIT * sizeof cell;
        char output = 0;
        while(i--)
        {
          const char n = ((cell >> i) & 1);
          if (n) output = 1;
          if (output) cf_putchar(s, '0' + n);
        }
      }
      break;
    }
    default:
    {
      cf_printf(s, CELL_FMT, cell);
      break;
    }
  }
}

cell
find_entry(struct state *s, struct dictionary *dict)
{
  s->tib.buf[s->tib.len] = '\0';
  const hash_t tib_opcode = hash(s->tib.buf);

  for (int i = dict->latest; i >= 0; i--)
  {
    if (dict->entries[i].opcode == tib_opcode)
    {
      return i;
    }
  }
  return -1;
}

cell
find_entry_by_hash(struct dictionary *dict, hash_t opcode)
{
  for (int i = dict->latest; i >= 0; i--)
  {
    if (dict->entries[i].opcode == opcode)
    {
      return i;
    }
  }
  return -1;
}

cell
find_entry_by_offset(struct dictionary *dict, cell offset)
{
  for (int i = dict->latest; i >= 0; i--)
  {
    if (dict->entries[i].offset == offset)
    {
      return i;
    }
  }
  return -1;
}

void
print_entry (struct state *s, char *format, cell entry_index) {
#ifdef __KEEP_ENTRY_NAMES
  if (entry_index == -1) {
    return;
  }

  struct entry *entry = ENTRY(entry_index);

  cf_printf(s, format,  entry->name == NULL ? "???" : entry->name, entry_index, entry->offset);
#endif /* __KEEP_ENTRY_NAMES */
}

void
get_stacktrace (struct state *s) {
  PUSH(-1);
  PUSH(find_entry_by_offset(&s->dict, PC));

  for (int i = s->r_stack->sp; i > 0; i--) {
    PUSH(find_entry_by_offset(&s->dict, R_CELLS[i]));
  }
}

void
show_stacktrace (struct state *s) {
  char * format = "%s:%ld:%ld";

  cf_printf(s, "  %s", COLOR_RED);
  print_entry(s, format, find_entry_by_offset(&s->dict, PC));

  for (int i = s->r_stack->sp; i > 0; i--) {
    cf_printf(s, " <- ");
    print_entry(s, format, find_entry_by_offset(&s->dict, R_CELLS[i]));
  }

  cf_printf(s, "%s\n", COLOR_YELLOW);
}

void
show_full_stacktrace (struct state *s) {
  char *format = "%-15s | %ld | %ld";
  cell current_index = find_entry_by_offset(&s->dict, PC);

  cf_printf(s, "%s", COLOR_RED);
  for (cell i = 0; i < R_LIM && R_CELLS[i]; i++) {
    cell index = find_entry_by_offset(&s->dict, R_CELLS[i]);

    cf_printf(s, "%s", index == current_index ? "---> " : "     ");

    print_entry(s, format, index);
    cf_printf(s, "\n");
  }

  cf_printf(s, "%s", COLOR_YELLOW);
  cf_printf(s, "\n");
}

void
clear_r_stack (struct state *s) {
  for (cell i = 0; i < R_LIM && R_CELLS[i]; i++) {
    R_CELLS[i] = 0;
  }
}

void
quit(struct state *s)
{
  s->done = 1;
  echo_color(s, ' ', COLOR_CLEAR);
  cf_printf(s, "\n");
}

void
cf_fatal_error(struct state *s, char id)
{
  cf_printf(s, "E%d", id);
  show_stacktrace(s);

  if (s)
  {
    echo_color(s, ' ', COLOR_CLEAR);
  }
  cf_fflush();
  reset_terminal();
  exit(1);
}

void *
cf_calloc(struct state *s, size_t nmemb, size_t size, unsigned char id)
{
  void *ptr = calloc(nmemb, size);
  if (!ptr) cf_fatal_error(s, id);

  return ptr;
}


#define FNV_32_PRIME ((hash_t)0x01000193)

hash_t
hash(char *str)
{
  if (!str) return 0;

  unsigned char *s = (unsigned char *)str;
  hash_t hval = 0;

  while (*s) {
    hval ^= (hash_t)*s++;

    /* multiply by the 32 bit FNV magic prime mod 2^32 */
    hval *= FNV_32_PRIME;
  }

  return hval;
}

void
dot_s(struct state *s, struct stack *stack)
{
  cf_printf(s, "[%d] ", stack->sp + 1);
  for (int i = 0; i < stack->sp + 1; i++)
  {
    cf_print_cell(s, stack->cells[i]);
    cf_printf(s, " ");
  }
  cf_printf(s, "<tos\n");
}

void
clear_tib (struct state *s){
  for(size_t i = 0; i < s->tib.len; i++)
  {
    s->tib.buf[i] = 0;
  }
  s->tib.len = 0;
}

#ifdef __KEEP_ENTRY_NAMES
void
dump_words(struct state *s, struct dictionary *dict)
{
  for (int i = dict->latest; i >= 0; i--)
  {
    struct entry entry = dict->entries[i];

    if (entry.name == NULL || entry.opcode == 0) continue;

    s->tib.len = entry.name_len;
    memcpy(s->tib.buf, entry.name, entry.name_len);
    s->tib.buf[s->tib.len] = '\0';
    cf_printf(s, "%s ", s->tib.buf);
  }
}
#else
void
dump_words(struct state *s, struct dictionary *dict __attribute__((unused)))
{
  cf_printf(s, "...\n");
}
#endif /* __KEEP_ENTRY_NAMES */


void
words(struct state *s)
{
  dump_words(s, &s->dict);
  cf_printf(s, "\n");
}

// struct entry*
// find_entry_by_code(struct dictionary *dict, struct code *code)
// {
//   for (struct entry *entry = dict->latest; entry != dict->entries - 1; entry--)
//   {
//     if (entry->code->opcode == code->opcode)
//     {
//       return entry;
//     }
//   }
//   return NULL;
// }
//
// struct entry*
// find_entry_by_fn(struct dictionary *dict, struct code *code)
// {
//   for (struct entry *entry = dict->latest; entry != dict->entries - 1; entry--)
//   {
//     if (entry->code->value == code->value)
//     {
//       return entry;
//     }
//   }
//   return NULL;
// }

void
print_tib(struct state *s)
{
  for(size_t i = 0; i < s->tib.len; i++)
  {
    cf_putchar(s, s->tib.buf[i]);
  }
}

void
unknow_word (struct state *s)
{
  print_tib(s);
  cf_printf(s, "?\n");

  if (s->str_stream || s->file_stream)
  {
    cf_fatal_error(s, -1);
  }
}

bool
tib_to_number(struct state *s, cell *n)
{
  char *endptr;
  s->tib.buf[s->tib.len] = '\0';
  *n = strtol(s->tib.buf, &endptr, s->base);
  return *s->tib.buf != 0 && *endptr == 0;
}
