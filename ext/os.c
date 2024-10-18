// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_LOAD                      (opcode_t) 0x61152930                // p@
#define OP_STORE                     (opcode_t) 0xC215C1E3                // p!
#define OP_CLOAD                     (opcode_t) 0xF6A62E2B                // pc@
#define OP_CSTORE                    (opcode_t) 0x55A6C3B8                // pc!

#define OP_SYSTEM                     (opcode_t) 0x7BB8F701                // system
#define OP_C_SUBALLOC                 (opcode_t) 0xF25B6721                // c-alloc
#define OP_C_SUBFREE                  (opcode_t) 0x318C2312                // c-free

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("p@"), OP_LOAD);
define_primitive(s, ENTRY_NAME("p!"), OP_STORE);
define_primitive(s, ENTRY_NAME("pc@"), OP_CLOAD);
define_primitive(s, ENTRY_NAME("pc!"), OP_CSTORE);

define_primitive(s, ENTRY_NAME("system"),  OP_SYSTEM);
define_primitive(s, ENTRY_NAME("c-alloc"), OP_C_SUBALLOC);
define_primitive(s, ENTRY_NAME("c-free"),  OP_C_SUBFREE);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_LOAD:
{
  ENSURE_STACK_MIN(1);
  CELLS[SP] = *(cell*) CELLS[SP];
  break;
}

case OP_STORE:
{
  ENSURE_STACK_MIN(2);
  cell *ptr = (cell*) CELLS[SP];
  *ptr = CELLS[SP - 1];
  SP -= 2;
  break;
}

case OP_CLOAD:
{
  ENSURE_STACK_MIN(1);
  CELLS[SP] = *(char*) CELLS[SP];
  break;
}

case OP_CSTORE:
{
  ENSURE_STACK_MIN(2);
  char *ptr = (char*) CELLS[SP];
  *ptr = CELLS[SP - 1];
  SP -= 2;
  break;
}

case OP_SYSTEM: {
  POP1();
  PUSH1(system(CFSTRING2C(p1)));
  break;
}

case OP_C_SUBALLOC: {
  POP1();
  const unsigned int size = (unsigned int)p1;
  PUSH1((cell)cf_calloc(s, 1, size, CALLOC_ERROR));
  break;
}

case OP_C_SUBFREE: {
  POP1();
  free((char *)p1);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#endif /* __SECTION_FUNCTION */
