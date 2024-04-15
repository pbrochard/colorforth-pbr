// The author disclaims copyright to this source code.

/**********************************************************************************
 *   PREFIX DEF
 *********************************************************************************/
#ifdef __SECTION_PREFIX_DEF

case '$': { s->color = define_float; echo_color(s, c, COLOR_MAGENTA); return; }

#endif /* __SECTION_PREFIX_DEF */


/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_FLOAT                     (opcode_t) 0xEF099DDA                // float
#define OP_F_DOTS                    (opcode_t) 0xDF52D985                // f.s
#define OP_F_DOT                     (opcode_t) 0x4EFD07F4                // f.
#define OP_F_DROP                    (opcode_t) 0x36C934A7                // fdrop
#define OP_F_DUP                     (opcode_t) 0x31A4657F                // fdup
#define OP_F_SWAP                    (opcode_t) 0xC890D5A5                // fswap
#define OP_F_OVER                    (opcode_t) 0x81A85DC0                // fover
#define OP_F_ROT                     (opcode_t) 0xE25FE90B                // frot
#define OP_F_SUBROT                  (opcode_t) 0x124F37B6                // f-rot
#define OP_F_NIP                     (opcode_t) 0xC38C7AB5                // fnip
#define OP_F_ADD                     (opcode_t) 0x4BFD033B                // f+
#define OP_F_SUB                     (opcode_t) 0x51FD0CAD                // f-
#define OP_F_MUL                     (opcode_t) 0x4AFD01A8                // f*
#define OP_F_DIV                     (opcode_t) 0x4FFD0987                // f/
#define OP_F_SUP                     (opcode_t) 0x3EFCEEC4                // f>
#define OP_F_INF                     (opcode_t) 0x40FCF1EA                // f<
#define OP_F_LOAD                    (opcode_t) 0x64FD2A96                // f@
#define OP_F_STORE                   (opcode_t) 0x45FCF9C9                // f!
#define OP_F_INLINE                  (opcode_t) 0xBF067E82                // [f,]

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

init_fstack(&s->fstack, FSTACK_SIZE);

define_primitive(s, ENTRY_NAME("float"),    OP_FLOAT); // fsize);

define_primitive(s, ENTRY_NAME("f.s"),      OP_F_DOTS); // fdot_s);
define_primitive(s, ENTRY_NAME("f."),       OP_F_DOT); // print_ftos);

define_primitive(s, ENTRY_NAME("fdrop"),    OP_F_DROP); // fdrop);
define_primitive(s, ENTRY_NAME("fdup"),     OP_F_DUP); // fdup);
define_primitive(s, ENTRY_NAME("fswap"),    OP_F_SWAP); // fswap);
define_primitive(s, ENTRY_NAME("fover"),    OP_F_OVER); // fover);
define_primitive(s, ENTRY_NAME("frot"),     OP_F_ROT); // frot);
define_primitive(s, ENTRY_NAME("f-rot"),    OP_F_SUBROT); // fminus_rot);
define_primitive(s, ENTRY_NAME("fnip"),     OP_F_NIP); //fnip);

define_primitive(s, ENTRY_NAME("f+"),       OP_F_ADD); // fadd);
define_primitive(s, ENTRY_NAME("f-"),       OP_F_SUB); // fsub);
define_primitive(s, ENTRY_NAME("f*"),       OP_F_MUL); // fmul);
define_primitive(s, ENTRY_NAME("f/"),       OP_F_DIV); // fdiv);

define_primitive(s, ENTRY_NAME("f>"),       OP_F_SUP); // fsup);
define_primitive(s, ENTRY_NAME("f<"),       OP_F_INF); // finf);

define_primitive(s,ENTRY_NAME("f@"),        OP_F_LOAD); //; // fload);
define_primitive(s, ENTRY_NAME("f!"),       OP_F_STORE); // fstore);

define_primitive(s, ENTRY_NAME("[f,]"),     OP_F_INLINE); //,   fcompile_literal);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_FLOAT: {
  PUSH1(sizeof(number_t));
  break;
}

case OP_F_DOTS: {
  cf_printf(s, "[%d] ", s->fstack.sp);
  for (int i = 0; i < s->fstack.sp; i++)
  {
    cf_printf(s, "%lf ", s->fstack.cells[i]);
  }
  cf_printf(s, "<ftos\n");
  break;
}

case OP_F_DOT: {
  cf_printf(s, "%lf ", fpop(&s->fstack));
  cf_fflush();
  break;
}


case OP_F_DROP: {
  fpop(&s->fstack);
  break;
}


case OP_F_DUP: {
  fpush(&s->fstack, s->fstack.cells[s->fstack.sp - 1]);
  break;
}


case OP_F_SWAP: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);
  fpush(&s->fstack, n1);
  fpush(&s->fstack, n2);
  break;
}


case OP_F_OVER: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);
  fpush(&s->fstack, n2);
  fpush(&s->fstack, n1);
  fpush(&s->fstack, n2);
  break;
}


case OP_F_ROT: {
  const cell n3 = fpop(&s->fstack);
  const cell n2 = fpop(&s->fstack);
  const cell n1 = fpop(&s->fstack);
  fpush(&s->fstack, n2);
  fpush(&s->fstack, n3);
  fpush(&s->fstack, n1);
  break;
}


case OP_F_SUBROT: {
  const cell n3 = fpop(&s->fstack);
  const cell n2 = fpop(&s->fstack);
  const cell n1 = fpop(&s->fstack);
  fpush(&s->fstack, n3);
  fpush(&s->fstack, n1);
  fpush(&s->fstack, n2);
  break;
}


case OP_F_NIP: {
  const number_t n2 = fpop(&s->fstack);
  fpop(&s->fstack);
  fpush(&s->fstack, n2);
  break;
}


case OP_F_ADD: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  fpush(&s->fstack, n1 + n2);
  break;
}


case OP_F_SUB: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  fpush(&s->fstack, n2 - n1);
  break;
}


case OP_F_MUL: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  fpush(&s->fstack, n1 * n2);
  break;
}


case OP_F_DIV: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  fpush(&s->fstack, n2 / n1);
  break;
}


case OP_F_SUP: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  PUSH1(n2 > n1);
  break;
}


case OP_F_INF: {
  const number_t n1 = fpop(&s->fstack);
  const number_t n2 = fpop(&s->fstack);

  PUSH1(n2 < n1);
  break;
}


case OP_F_LOAD: {
  POP1();
  fpush(&s->fstack, *(number_t*)p1);
  break;
}


case OP_F_STORE: {
  POP1();
  number_t *ptr = (number_t*)p1;
  number_t n = fpop(&s->fstack);
  *ptr = n;
  break;
}


case OP_F_INLINE: {
  number_t *ptr = cf_calloc(s, 1, sizeof(number_t), F_LITERAL_ERROR);
  *ptr = fpop(&s->fstack);

  compile_literal(s, (cell)ptr);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

void
init_fstack(struct fstack *stack, int len)
{
  stack->cells = cf_calloc(NULL, len, sizeof(number_t), F_STACK_ERROR);
  stack->sp = 0;
  stack->lim = len;
}

void
fpush(struct fstack *stack, const number_t n)
{
#ifndef UNSAFE_MODE
  if (stack->sp >= stack->lim)
  {
    cf_printf(NULL, "ES>!\n");
    return;
  }
#endif

  stack->cells[stack->sp] = n;
  stack->sp += 1;
}

number_t
fpop(struct fstack *stack)
{
#ifndef UNSAFE_MODE
  if (stack->sp == 0)
  {
    cf_printf(NULL, "ES<!\n");
    return 0;
  }
#endif

  stack->sp -= 1;
  return stack->cells[stack->sp];
}

void
define_float(struct state *s)
{
  char *ptr;
  const number_t n = strtod(s->tib.buf, &ptr);
  fpush(&s->fstack, n);
}

#endif /* __SECTION_FUNCTION */
