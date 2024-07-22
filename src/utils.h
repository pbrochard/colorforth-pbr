// The author disclaims copyright to this source code.
#ifndef __UTILS_H
#define __UTILS_H

#include <stdbool.h>

#include "cf.h"

extern void cf_print_cell(struct state *s, cell cell);

extern cell find_entry(struct state *s, struct dictionary *dict);

extern cell find_entry_by_hash(struct dictionary *dict, hash_t opcode);
extern cell find_entry_by_offset(struct dictionary *dict, cell offset);

extern void print_entry (struct state *s, char *format, cell entry_index);

extern void get_stacktrace (struct state *s);
extern void show_stacktrace (struct state *s);
extern void show_full_stacktrace (struct state *s);

extern void clear_r_stack (struct state *s);

extern void quit(struct state *s);

extern void cf_fatal_error(struct state *s, char id);

extern void * cf_calloc(struct state *s, size_t nmemb, size_t size, unsigned char id);

extern hash_t hash(char *str);

extern void dot_s(struct state *s, struct stack *stack);

extern void clear_tib (struct state *s);

extern void dump_words(struct state *s, struct dictionary *dict);

extern void words(struct state *s);

extern void print_tib(struct state *s);

extern void unknow_word (struct state *s);

extern bool tib_to_number(struct state *s, cell *n);

#endif /* __UTILS_H */
