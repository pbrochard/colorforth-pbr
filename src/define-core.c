// The author disclaims copyright to this source code.

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
define_primitive(s, ENTRY_NAME("@"), OP_LOAD);
define_primitive(s, ENTRY_NAME("!"), OP_STORE);
define_primitive(s, ENTRY_NAME("c@"), OP_CLOAD);
define_primitive(s, ENTRY_NAME("c!"), OP_CSTORE);
define_primitive(s, ENTRY_NAME("cell"), OP_CELL);
define_primitive(s, ENTRY_NAME("here"), OP_HERE);
define_primitive(s, ENTRY_NAME("&here"), OP_HERE_ADDR);
define_primitive(s, ENTRY_NAME("&heap"), OP_HEAP_ADDR);
define_primitive(s, ENTRY_NAME("heap-size"), OP_HEAP_SIZE);
define_primitive(s, ENTRY_NAME("latest"), OP_LATEST);

define_primitive(s, ENTRY_NAME("[^]"), OP_COMPILE);
define_primitive(s, ENTRY_NAME("[,]"), OP_COMPILE_LITERAL);

define_primitive(s, ENTRY_NAME("c>"), OP_GET_ENTRY_CODE);
define_primitive(s, ENTRY_NAME("call"), OP_EXECUTE);
define_primitive(s, ENTRY_NAME("call*"), OP_EXECUTE_STAR);

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

define_primitive(s, ENTRY_NAME("clear"), OP_CLEAR);

// init_lib(s);

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
define_register_primitive(C);
define_register_primitive(I);
define_register_primitive(J);
define_register_primitive(K);

define_primitive(s, ENTRY_NAME("IJK>R"), OP_IJK_TO_R);
define_primitive(s, ENTRY_NAME("R>KJI"), OP_R_TO_KJI);
#endif

//#ifdef __USE_EXTENSIONS
//  load_extensions(s);
//#endif
