// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_DIV                       (opcode_t) 0x2F0049FD                // /
#define OP_MOD                       (opcode_t) 0xD32A27E4                // mod
#define OP_DIVMOD                    (opcode_t) 0x465A474B                // /mod
#define OP_MUL_DIV                   (opcode_t) 0x4F683323                // */
#define OP_LSHIFT                    (opcode_t) 0x346A9A70                // lshift
#define OP_RSHIFT                    (opcode_t) 0xB6A4D846                // rshift
#define OP_SUP                       (opcode_t) 0x3E00619A                // >
#define OP_INF_EQUAL                 (opcode_t) 0xBD946CEB                // <=
#define OP_SUP_EQUAL                 (opcode_t) 0x4199B9E5                // >=
#define OP_INFSUP                    (opcode_t) 0xBE946E7E                // <>
#define OP_OR                        (opcode_t) 0x8D132FDD                // or
#define OP_AND                       (opcode_t) 0xADD16739                // and
#define OP_MIN                       (opcode_t) 0xED395B5C                // min
#define OP_MAX                       (opcode_t) 0xDB25B74E                // max
#define OP_ABS                       (opcode_t) 0xB6B4F350                // abs
#define OP_RAND                      (opcode_t) 0xE4758C3F                // rand
#define OP_SRAND                     (opcode_t) 0x69BDC0A                 // srand
#define OP_RANDOM                    (opcode_t) 0x5EB42A27                // random

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("/"),      OP_DIV); //, div_fn);
define_primitive(s, ENTRY_NAME("mod"),    OP_MOD); //, mod_fn);
define_primitive(s, ENTRY_NAME("/mod"),   OP_DIVMOD); //, slash_mod_fn);
define_primitive(s, ENTRY_NAME("*/"),     OP_MUL_DIV); //, start_slash_fn);
define_primitive(s, ENTRY_NAME("lshift"), OP_LSHIFT); //, lshift_fn);
define_primitive(s, ENTRY_NAME("rshift"), OP_RSHIFT); //, rshift_fn);
define_primitive(s, ENTRY_NAME(">"),      OP_SUP); //, sup_fn);
define_primitive(s, ENTRY_NAME("<="),     OP_INF_EQUAL); //, inf_equal_fn);
define_primitive(s, ENTRY_NAME(">="),     OP_SUP_EQUAL); //, sup_equal_fn);
define_primitive(s, ENTRY_NAME("<>"),     OP_INFSUP); //, not_equal_fn);
define_primitive(s, ENTRY_NAME("or"),     OP_OR); //, or_fn);
define_primitive(s, ENTRY_NAME("and"),    OP_AND); //, and_fn);
define_primitive(s, ENTRY_NAME("min"),    OP_MIN); //, min_fn);
define_primitive(s, ENTRY_NAME("max"),    OP_MAX); //, max_fn);
define_primitive(s, ENTRY_NAME("abs"),    OP_ABS); //, abs_fn);
define_primitive(s, ENTRY_NAME("rand"),   OP_RAND); //, rand_fn);
define_primitive(s, ENTRY_NAME("srand"),  OP_SRAND); //, srand_fn);
define_primitive(s, ENTRY_NAME("random"), OP_RANDOM); //, random_fn);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH


#define modulo(n2, n1) ((n2 < 0) ? (n2 % n1 + n1) : (n2 % n1))

case OP_DIV: {
  POP2();
  PUSH1(p2 / p1);
  break;
}

case OP_MOD: {
  POP2();
  PUSH1(modulo(p2, p1));
  break;
}

case OP_DIVMOD: {
  POP2();
  PUSH2(p2 / p1, modulo(p2, p1));
  break;
}

case OP_MUL_DIV: {
  POP3();
  PUSH1(p3 * p2 / p1);
  break;
}

case OP_LSHIFT: {
  POP2();
  PUSH1(p2 << p1);
  break;
}

case OP_RSHIFT: {
  POP2();
  PUSH1(p2 >> p1);
  break;
}

case OP_SUP: {
  POP2();
  PUSH1(p2 > p1);
  break;
}

case OP_INF_EQUAL: {
  POP2();
  PUSH1(p2 <= p1);
  break;
}

case OP_SUP_EQUAL: {
  POP2();
  PUSH1(p2 >= p1);
  break;
}

case OP_INFSUP: {
  POP2();
  PUSH1(p2 != p1);
  break;
}

case OP_OR: {
  POP2();
  PUSH1(p2 || p1);
  break;
}

case OP_AND: {
  POP2();
  PUSH1(p2 && p1);
  break;
}

case OP_MIN: {
  POP2();
  PUSH1(p1 < p2 ? p1 : p2);
  break;
}

case OP_MAX: {
  POP2();
  PUSH1(p1 > p2 ? p1 : p2);
  break;
}

case OP_ABS: {
  POP1();
  PUSH1(labs(p1));
  break;
}

case OP_RAND: {
  PUSH1(rand());
  break;
}

case OP_SRAND: {
  POP1();
  srand(p1);
  break;
}

case OP_RANDOM: {
  POP1();
  PUSH1(p1 != 0 ? rand() % p1 : 0);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#endif /* __SECTION_FUNCTION */
