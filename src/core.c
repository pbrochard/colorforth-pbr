// The author disclaims copyright to this source code.

/**********************************************************************************
 *   PREFIX DEF
 *********************************************************************************/
#ifdef __SECTION_PREFIX_DEF

case ':': { s->color = define; echo_color(s, c, COLOR_RED); return; }

case '^': { s->color = compile; echo_color(s, c, COLOR_GREEN); return; }

case '~': { s->color = execute; echo_color(s, c, COLOR_YELLOW); return; }

case '\'': {
  s->color = (s->color == execute || s->color == tick || s->color == tick_entry) ? tick : compile_tick;
  echo_color(s, c, COLOR_BLUE);
  return;
}

case '`': {
  s->color = (s->color == execute || s->color == tick || s->color == tick_entry) ? tick_entry : compile_tick_entry;
  echo_color(s, c, COLOR_BLUE);
  return;
}

case '(': {
  char count = 0;
  echo_color(s, c, COLOR_WHITE);
  while ((c = cf_getchar(s)) != ')' || count > 0) {
    echo_color(s, c, COLOR_WHITE);
    if (c == '(') count += 1;
    else if (c == ')') count -= 1;
  }
  echo_color(s, c, COLOR_WHITE);
  return;
}

#endif /* __SECTION_PREFIX_DEF */


/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

// Define __SHOW_MISSING_HASH in conf.h to display name <-> hash relationship
//
// Use `.hash" <string to hash>"` to find them in colorForth

// Internal OP
#define OP_CALL                      (opcode_t) 0xF85D926E                // __OP_CALL
#define OP_TAIL_CALL                 (opcode_t) 0x1A03DDDD                // __OP_TAIL_CALL
#define OP_NUMBER                    (opcode_t) 0xA2AB56D7                // __OP_NUMBER
#define OP_TICK_NUMBER               (opcode_t) 0x544A7A21                // __OP_TICK_NUMBER

// src/cf.c
#define OP_NOP                       (opcode_t) 0x5964713D                // nop
#define OP_PRINT_TOS                 (opcode_t) 0x2E00486A                // .
#define OP_DUP                       (opcode_t) 0xF500DB1                 // dup
#define OP_OVER                      (opcode_t) 0x38C2FE2A                // over
#define OP_SWAP                      (opcode_t) 0xD902F543                // swap
#define OP_DROP                      (opcode_t) 0x1940D1AD                // drop
#define OP_ROT                       (opcode_t) 0x7D519FD                 // rot
#define OP_MINUS_ROT                 (opcode_t) 0xE8E1884C                // -rot
#define OP_NIP                       (opcode_t) 0x4D5E4E2B                // nip
#define OP_ADD                       (opcode_t) 0x2B0043B1                // +
#define OP_SUB                       (opcode_t) 0x2D0046D7                // -
#define OP_MUL                       (opcode_t) 0x2A00421E                // *
#define OP_EQUAL                     (opcode_t) 0x3D006007                // =
#define OP_LESS                      (opcode_t) 0x3C005E74                // <
#define OP_BYE                       (opcode_t) 0x253F7458                // bye
#define OP_WORDS                     (opcode_t) 0x30E76679                // words
#define OP_EMIT                      (opcode_t) 0x9B01D09B                // emit
#define OP_KEY                       (opcode_t) 0x485BCDF                 // key
#define OP_LOAD                      (opcode_t) 0x61152930                // p@
#define OP_STORE                     (opcode_t) 0xC215C1E3                // p!
#define OP_CLOAD                     (opcode_t) 0xF6A62E2B                // pc@
#define OP_CSTORE                    (opcode_t) 0x55A6C3B8                // pc!
#define OP_HEAP_LOAD                 (opcode_t) 0x400064C0                // @
#define OP_HEAP_STORE                (opcode_t) 0x210033F3                // !
#define OP_HEAP_CLOAD                (opcode_t) 0x72F4F1DB                // c@
#define OP_HEAP_CSTORE               (opcode_t) 0xD1F58768                // c!
#define OP_CELL                      (opcode_t) 0x1415DDAC                // cell
#define OP_HERE                      (opcode_t) 0xD786E25E                // here
#define OP_HERE_ADDR                 (opcode_t) 0xAE504314                // &here
#define OP_HEAP                      (opcode_t) 0x89705C80                // &heap
#define OP_HEAP_SIZE                 (opcode_t) 0xC2A05C60                // heap-size
#define OP_LATEST                    (opcode_t) 0xA307AFAB                // latest
#define OP_COMPILE                   (opcode_t) 0x6B6CDC65                // ,c
#define OP_COMPILE_LITERAL           (opcode_t) 0x6C6CDDF8                // ,l
#define OP_GET_ENTRY_CODE            (opcode_t) 0xC0F56CA5                // c>
#define OP_EXECUTE                   (opcode_t) 0x54DA4CCF                // execute
#define OP_EXECUTE_STAR              (opcode_t) 0x78A70C7F                // execute*
#define OP_IF                        (opcode_t) 0x790405D7                // if
#define OP_IF_TAIL_CALL              (opcode_t) 0x7E556D47                // if*
#define OP_IF_EXIT                   (opcode_t) 0x6D555284                // if;
#define OP_IF_NOT                    (opcode_t) 0x1A0E810B                // if-not
#define OP_IF_NOT_TAIL_CALL          (opcode_t) 0x25D546F3                // if-not*
#define OP_IF_NOT_EXIT               (opcode_t) 0x34D55E90                // if-not;
#define OP_IF_ELSE                   (opcode_t) 0xD59EAA1B                // if-else
#define OP_DOT_S                     (opcode_t) 0x83717F5B                // .s
#define OP_RETURN                    (opcode_t) 0x3B005CE1                // ;
#define OP_R_PUSH                    (opcode_t) 0x6299EDD8                // >R
#define OP_R_POP                     (opcode_t) 0x3ECB51F8                // R>
#define OP_R_FETCH                   (opcode_t) 0x6CCB9A62                // R@

// Register A
#define OP_REG_A_LOAD                (opcode_t) 0x66A0AFE9                // A@
#define OP_REG_A_STORE               (opcode_t) 0xC5A14576                // A!
#define OP_REG_A_ADD                 (opcode_t) 0x57EF066B                // A+!
#define OP_REG_A_INC                 (opcode_t) 0x51EEFCF9                // A++
#define OP_REG_A_DEC                 (opcode_t) 0x77FE4355                // A--
#define OP_REG_A_TO_R                (opcode_t) 0x2D43D1F                 // A>R
#define OP_REG_R_TO_A_               (opcode_t) 0x9311A63B                // R>A

// Register B
#define OP_REG_B_LOAD                (opcode_t) 0x8CA32A52                // B@
#define OP_REG_B_STORE               (opcode_t) 0xADA35E45                // B!
#define OP_REG_B_ADD                 (opcode_t) 0x603C1122                // B+!
#define OP_REG_B_INC                 (opcode_t) 0x663C1A94                // B++
#define OP_REG_B_DEC                 (opcode_t) 0x603793F4                // B--
#define OP_REG_B_TO_R                (opcode_t) 0x755808AE                // B>R
#define OP_REG_R_TO_B_               (opcode_t) 0x9411A7CE                // R>B

// Register I
#define OP_REG_I_LOAD                (opcode_t) 0x96B48331                // I@
#define OP_REG_I_STORE               (opcode_t) 0xB5B4B3FE                // I!
#define OP_REG_I_ADD                 (opcode_t) 0xAE5EC4B3                // I+!
#define OP_REG_I_INC                 (opcode_t) 0xB85ED471                // I++
#define OP_REG_I_DEC                 (opcode_t) 0x5E6D514D                // I--
#define OP_REG_I_TO_R                (opcode_t) 0x79924CA7                // I>R
#define OP_REG_R_TO_I_               (opcode_t) 0x8B1199A3                // R>I

// Register J
#define OP_REG_J_LOAD                (opcode_t) 0xBCB6FD9A                // J@
#define OP_REG_J_STORE               (opcode_t) 0xDDB7318D                // J!
#define OP_REG_J_ADD                 (opcode_t) 0x374A69AA                // J+!
#define OP_REG_J_INC                 (opcode_t) 0x2D4A59EC                // J++
#define OP_REG_J_DEC                 (opcode_t) 0xA74509CC                // J--
#define OP_REG_J_TO_R                (opcode_t) 0xCC15E5D6                // J>R
#define OP_REG_R_TO_J_               (opcode_t) 0x8C119B36                // R>J

// Register K
#define OP_REG_K_LOAD                (opcode_t) 0x62BA4183 // K@
#define OP_REG_K_STORE               (opcode_t) 0x41BA0D90 // K!
#define OP_REG_K_ADD                 (opcode_t) 0xA4FC55BD // K+!
#define OP_REG_K_INC                 (opcode_t) 0x9AFC45FF // K++
#define OP_REG_K_DEC                 (opcode_t) 0xB500EC1B // K--
#define OP_REG_K_TO_R                (opcode_t) 0x93E0647D // K>R
#define OP_REG_R_TO_K_               (opcode_t) 0x8D119CC9 // R>K

#define OP_IJK_TO_R                  (opcode_t) 0x1B91C8D0 // IJK>R
#define OP_R_TO_KJI                  (opcode_t) 0x22D5F650 // R>KJI

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("nop"), OP_NOP);
define_primitive(s, ENTRY_NAME("."), OP_PRINT_TOS);
define_primitive(s, ENTRY_NAME("dup"), OP_DUP);
define_primitive(s, ENTRY_NAME("drop"), OP_DROP);
define_primitive(s, ENTRY_NAME("swap"), OP_SWAP);
define_primitive(s, ENTRY_NAME("over"), OP_OVER);
define_primitive(s, ENTRY_NAME("rot"), OP_ROT);
define_primitive(s, ENTRY_NAME("-rot"), OP_MINUS_ROT);
define_primitive(s, ENTRY_NAME("nip"), OP_NIP);
define_primitive(s, ENTRY_NAME("+"), OP_ADD);
define_primitive(s, ENTRY_NAME("-"), OP_SUB);
define_primitive(s, ENTRY_NAME("*"), OP_MUL);
define_primitive(s, ENTRY_NAME("="), OP_EQUAL);
define_primitive(s, ENTRY_NAME("<"), OP_LESS);
define_primitive(s, ENTRY_NAME("bye"), OP_BYE);
define_primitive(s, ENTRY_NAME("words"), OP_WORDS);
define_primitive(s, ENTRY_NAME("emit"), OP_EMIT);
define_primitive(s, ENTRY_NAME("key"), OP_KEY);
define_primitive(s, ENTRY_NAME("p@"), OP_LOAD);
define_primitive(s, ENTRY_NAME("p!"), OP_STORE);
define_primitive(s, ENTRY_NAME("pc@"), OP_CLOAD);
define_primitive(s, ENTRY_NAME("pc!"), OP_CSTORE);
define_primitive(s, ENTRY_NAME("@"), OP_HEAP_LOAD);
define_primitive(s, ENTRY_NAME("!"), OP_HEAP_STORE);
define_primitive(s, ENTRY_NAME("c@"), OP_HEAP_CLOAD);
define_primitive(s, ENTRY_NAME("c!"), OP_HEAP_CSTORE);
define_primitive(s, ENTRY_NAME("cell"), OP_CELL);
define_primitive(s, ENTRY_NAME("here"), OP_HERE);
define_primitive(s, ENTRY_NAME("&here"), OP_HERE_ADDR);
define_primitive(s, ENTRY_NAME("&heap"), OP_HEAP);
define_primitive(s, ENTRY_NAME("heap-size"), OP_HEAP_SIZE);
define_primitive(s, ENTRY_NAME("latest"), OP_LATEST);

define_primitive(s, ENTRY_NAME(",c"), OP_COMPILE);
define_primitive(s, ENTRY_NAME(",l"), OP_COMPILE_LITERAL);

define_primitive(s, ENTRY_NAME("c>"), OP_GET_ENTRY_CODE);
define_primitive(s, ENTRY_NAME("execute"), OP_EXECUTE);
define_primitive(s, ENTRY_NAME("execute*"), OP_EXECUTE_STAR);

define_primitive(s, ENTRY_NAME("if"), OP_IF);
define_primitive(s, ENTRY_NAME("if*"), OP_IF_TAIL_CALL);
define_primitive(s, ENTRY_NAME("if;"), OP_IF_EXIT);
define_primitive(s, ENTRY_NAME("if-not"), OP_IF_NOT);
define_primitive(s, ENTRY_NAME("if-not*"), OP_IF_NOT_TAIL_CALL);
define_primitive(s, ENTRY_NAME("if-not;"), OP_IF_NOT_EXIT);

define_primitive(s, ENTRY_NAME("if-else"), OP_IF_ELSE);

define_primitive(s, ENTRY_NAME(".s"), OP_DOT_S);

define_primitive(s, ENTRY_NAME(";"), OP_RETURN);

define_primitive(s, ENTRY_NAME(">R"), OP_R_PUSH);
define_primitive(s, ENTRY_NAME("R>"), OP_R_POP);
define_primitive(s, ENTRY_NAME("R@"), OP_R_FETCH);

#ifdef __USE_REGISTER

#define define_register_primitive(N)                              \
  define_primitive(s, ENTRY_NAME(#N"@"), OP_REG_##N##_LOAD);      \
  define_primitive(s, ENTRY_NAME(#N"!"), OP_REG_##N##_STORE);     \
  define_primitive(s, ENTRY_NAME(#N"+!"), OP_REG_##N##_ADD);      \
  define_primitive(s, ENTRY_NAME(#N"++"), OP_REG_##N##_INC);      \
  define_primitive(s, ENTRY_NAME(#N"--"), OP_REG_##N##_DEC);      \
  define_primitive(s, ENTRY_NAME(#N">R"), OP_REG_##N##_TO_R);   \
  define_primitive(s, ENTRY_NAME("R>"#N), OP_REG_R_TO_##N##_);

//
// //  // A, B, C, I, J and K registers are state global
define_register_primitive(A);
define_register_primitive(B);
define_register_primitive(I);
define_register_primitive(J);
define_register_primitive(K);

define_primitive(s, ENTRY_NAME("IJK>R"), OP_IJK_TO_R);
define_primitive(s, ENTRY_NAME("R>KJI"), OP_R_TO_KJI);
#endif

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH
case OP_R_PUSH:
{
  ENSURE_STACK_MIN(1); ENSURE_R_STACK_MAX(1);
  const cell n = POP();
  R_PUSH(n);
  break;
}

case OP_R_POP:
{
  ENSURE_R_STACK_MIN(1); ENSURE_STACK_MAX(1);
  const cell n = R_POP();
  PUSH(n);
  break;
}

case OP_R_FETCH:
{
  ENSURE_R_STACK_MIN(1);
  ENSURE_STACK_MAX(1);
  PUSH(R_CELLS[R_SP]);
  break;
}

#ifdef __USE_REGISTER
define_register(A);
define_register(B);
define_register(I);
define_register(J);
define_register(K);
#endif

case OP_DUP:
{
  ENSURE_STACK_MIN(1);
  ENSURE_STACK_MAX(1);
  PUSH(CELLS[SP - 1]);
  break;
}

case OP_DROP:
{
  ENSURE_STACK_MIN(1);
  SP -= 1;
  break;
}

case OP_SWAP:
{
  ENSURE_STACK_MIN(2);
  const cell n = CELLS[SP];
  CELLS[SP] = CELLS[SP - 1];
  CELLS[SP - 1] = n;
  break;
}

case OP_OVER:
{
  ENSURE_STACK_MIN(2);
  ENSURE_STACK_MAX(1);
  PUSH(CELLS[SP - 2]);
  break;
}

case OP_ROT:
{
  ENSURE_STACK_MIN(3);
  const cell n = CELLS[SP - 2];
  CELLS[SP - 2] = CELLS[SP - 1];
  CELLS[SP - 1] = CELLS[SP];
  CELLS[SP] = n;
  break;
}

case OP_MINUS_ROT:
{
  ENSURE_STACK_MIN(3);
  const cell n = CELLS[SP];
  CELLS[SP] = CELLS[SP - 1];
  CELLS[SP - 1] = CELLS[SP - 2];
  CELLS[SP - 2] = n;
  break;
}

case OP_NIP:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP + 1];
  break;
}

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

case OP_HEAP_LOAD:
{
  ENSURE_STACK_MIN(1);
  CELLS[SP] = HEAP(CELLS[SP], cell);
  break;
}

case OP_HEAP_STORE:
{
  ENSURE_STACK_MIN(2);
  HEAP(CELLS[SP], cell) = CELLS[SP - 1];
  SP -= 2;
  break;
}

case OP_HEAP_CLOAD:
{
  ENSURE_STACK_MIN(1);
  CELLS[SP] = HEAP(CELLS[SP], char);
  break;
}

case OP_HEAP_CSTORE:
{
  ENSURE_STACK_MIN(2);
  HEAP(CELLS[SP], char) = (char) CELLS[SP - 1];
  SP -= 2;
  break;
}

case OP_CALL:
{
  PC += sizeof(opcode_t);
  ENSURE_STACK_MAX(1);
  R_PUSH(PC + sizeof(cell));
  PC = ENTRY(HEAP(PC, cell))->offset;
  continue;
}

case OP_TAIL_CALL:
{
  PC += sizeof(opcode_t);
  PC = ENTRY(HEAP(PC, cell))->offset;
  continue;
}

case OP_NUMBER:
case OP_TICK_NUMBER:
{
  ENSURE_STACK_MAX(1);
  SP += 1;
  PC += sizeof(opcode_t);
  CELLS[SP] = HEAP(PC, cell);
  PC += sizeof(cell);
  continue;
}

case OP_ADD:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP] + CELLS[SP + 1];
  break;
}

case OP_SUB:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP] - CELLS[SP + 1];
  break;
}

case OP_MUL:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP] * CELLS[SP + 1];
  break;
}

case OP_EQUAL:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP] == CELLS[SP + 1];
  break;
}

case OP_LESS:
{
  ENSURE_STACK_MIN(2);
  SP -= 1;
  CELLS[SP] = CELLS[SP] < CELLS[SP + 1];
  break;
}

// Conditions: p2=flag p1=offset
case OP_IF:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2) {
    R_PUSH(PC);
    PC = p1;
  }
  continue;
}

// Tail call optimized if (to be used with the latest entry)
case OP_IF_TAIL_CALL:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2) PC = p1;
  continue;
}

case OP_IF_EXIT:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2) {
    R_PUSH(PC);
    PC = p1;
    R_SP -= 1;
  }
  continue;
}

case OP_IF_NOT:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2 == 0) {
    R_PUSH(PC);
    PC = p1;
  }
  continue;
}

// Tail call optimized if-not
case OP_IF_NOT_TAIL_CALL:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2 == 0) PC = p1;
  continue;
}

case OP_IF_NOT_EXIT:
{
  ENSURE_STACK_MIN(2);
  POP2();

  PC += sizeof(opcode_t);

  if (p2 == 0) {
    R_PUSH(PC);
    PC = p1;
    R_SP -= 1;
  }
  continue;
}

// Conditions: p3=flag p2=true_offset p1=false_offset
case OP_IF_ELSE:
{
  ENSURE_STACK_MIN(3);
  POP3();

  PC += sizeof(opcode_t);
  R_PUSH(PC);
  PC = p3 ? p2 : p1;
  continue;
}

case OP_EMIT:
{
  ENSURE_STACK_MIN(1);
  cf_putchar(s, (char)CELLS[SP]);
  SP -= 1;
  break;
}

case OP_KEY:
{
  ENSURE_STACK_MAX(1);
  PUSH((char)cf_getchar(s));
  break;
}

case OP_CELL:
{
  ENSURE_STACK_MAX(1);
  PUSH(sizeof(cell));
  break;
}

case OP_GET_ENTRY_CODE:
{
  POP1();
  PUSH(ENTRY(p1)->offset);
  break;
}

case OP_EXECUTE:
{
  ENSURE_STACK_MIN(1);
  ENSURE_R_STACK_MAX(1);
  const cell offset = POP();
  R_PUSH(PC + sizeof(opcode_t));
  PC = offset;
  continue;
}

case OP_EXECUTE_STAR:
{
  ENSURE_STACK_MIN(1);
  ENSURE_R_STACK_MAX(1);
  const cell offset = CELLS[SP];
  R_PUSH(PC + sizeof(opcode_t));
  PC = offset;
  continue;
}

case OP_HERE:
{
  ENSURE_STACK_MAX(1);
  PUSH(s->here);
  break;
}

case OP_HERE_ADDR:
{
  ENSURE_STACK_MAX(1);
  PUSH((cell)&s->here);
  break;
}

case OP_HEAP:
{
  ENSURE_STACK_MIN(1);
  CELLS[SP] = (cell) (s->heap + CELLS[SP]);
  break;
}

case OP_HEAP_SIZE:
{
  ENSURE_STACK_MAX(1);
  PUSH((cell)HEAP_SIZE);
  break;
}

case OP_LATEST:
{
  ENSURE_STACK_MAX(1);
  PUSH(s->dict.latest);
  break;
}

case OP_COMPILE:
{
  ENSURE_STACK_MIN(1);
  cell offset = POP();
  cell entry_index = find_entry_by_offset(&s->dict, offset);
  compile_entry(s, entry_index);
  break;
}

case OP_COMPILE_LITERAL:
{
  ENSURE_STACK_MIN(1);
  cell n = POP();
  compile_literal(s, n);
  break;
}

case OP_BYE:
{
  quit(s);
  return;
}

case OP_WORDS:
{
  words(s);
  break;
}

case OP_NOP: {
  break;
}

case OP_PRINT_TOS:
{
  ENSURE_STACK_MIN(1);
  const cell n = POP();
  cf_print_cell(s, n);
  cf_printf(s, " ");
  cf_fflush();
  break;
}

case OP_DOT_S:
{
  dot_s(s, s->stack);
  break;
}

#ifdef __USE_REGISTER
case OP_IJK_TO_R: {
  ENSURE_R_STACK_MAX(1);
  R_PUSH(K);
  K = J;
  J = I;
  break;
}

case OP_R_TO_KJI: {
  ENSURE_R_STACK_MIN(1);
  I = J;
  J = K;
  K = R_POP();
  break;
}
#endif

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#endif /* __SECTION_FUNCTION */
