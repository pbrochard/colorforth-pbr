#ifndef __COLORFORTH_H
#define __COLORFORTH_H

#include <stdlib.h>

typedef long cell;

#define CELL_FMT "ld"

enum opcode
{
  OP_PRINT_TOS,
  OP_DUP,
  OP_OVER,
  OP_SWAP,
  OP_DROP,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_EQUAL,
  OP_LESS,
  OP_WHEN,
  OP_UNLESS,
  OP_CHOOSE,
  OP_BYE,
  OP_WORDS,
  OP_RETURN,
  OP_EMIT,
  OP_KEY,
  OP_LOAD,
  OP_STORE,
  OP_CLOAD,
  OP_CSTORE,
  OP_CELL,
  // call defined word
  OP_CALL,
  OP_TAIL_CALL,
  OP_EXECUTE,
  OP_NUMBER,
  OP_TICK_NUMBER,
  OP_HERE,

  /* Extensions */
  OP_SEE,
  OP_DISASSEMBLE_DICT,
  OP_SYSTEM,
  OP_ECHO_SET,

  /* Last non opcode - do not remove! */
  __LAST_NOT_AN_OPCODE__,
};

// terminal input buffer
struct tib
{
  char buf[20];
  size_t len;
};

struct code;
struct code
{
  enum opcode opcode;
  cell this;
};

struct entry;
struct entry
{
  char name[20];
  size_t name_len;
  struct code *code;
};

struct stack
{
  // circular stack
  cell cells[8];
  // stack position
  int sp;
};

struct state
{
  void (*color)(struct state *s);
  struct stack *stack;
  struct stack *r_stack;
  struct tib tib;
  struct entry *dictionary;
  struct entry *latest;
  void *heap;
  void *here;
  // track stream position for debugging compilation
  unsigned int line, coll;
  int done;
  int echo_on;
};

struct primitive_map
{
  char *name;
  enum opcode opcode;
  void (*func)();
} primitive_map[__LAST_NOT_AN_OPCODE__];

extern void push(struct stack *stack, const cell n);
extern cell pop(struct stack *stack);

extern struct entry* find_entry(struct state *s);
extern void unknow_word (struct state *s, const char *msg);

extern void define_extension(struct state *s, char name[], const enum opcode opcode, void (*func)(struct state *s));

extern struct state* colorforth_newstate(void);
extern void parse_colorforth(struct state *state, int c);

#endif /* __COLORFORTH_H */
