// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_GETCHAR                   (opcode_t) 0x151AFB78                // getchar
#define OP_ECHO_ADDR                 (opcode_t) 0xE63F83C1                // echo
#define OP_FILE_SUBSIZE              (opcode_t) 0xD4DD4B30                // file-size
#define OP_FILE_LOAD                 (opcode_t) 0xDE8C953C                // load
#define OP_FILE_SAVE                 (opcode_t) 0x84B337FD                // save
#define OP_INCLUDED                  (opcode_t) 0x7916FE10                // included

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("getchar"), OP_GETCHAR);
define_primitive(s, ENTRY_NAME("echo"), OP_ECHO_ADDR);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_GETCHAR: {
  PUSH1(getchar());
  break;
}

case OP_ECHO_ADDR: {
  PUSH1((cell) &s->echo_on);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

int
file_size(char *filename)
{
  FILE *fp = fopen(filename, "r");

  if (!fp) return -1;

  fseek(fp, 0L, SEEK_END);
  int size=ftell(fp);
  fclose(fp);

  return size;
}

//void
//file_size_fn(struct state *s)
//{
//  POP1();
//  char *filename = CFSTRING2C(p1);
//
//  int size = file_size(filename);
//
//  if (size == -1) cf_printf(s, "Unable to read '%s'\n", filename);
//
//  PUSH1(file_size(filename));
//}

//void
//load_file(struct state *s)
//{
//  POP2();
//  char *filename = CFSTRING2C(p1);
//  char *buf = (char *) (p2);
//  int size = file_size(filename);
//
//  if (size == -1)
//  {
//    cf_printf(s, "Unable to read '%s'\n", filename);
//    PUSH1(-1);
//    return;
//  }
//
//  FILE *fp = fopen(filename, "r");
//
//  if (!fp)
//  {
//    cf_printf(s, "Unable to read '%s'\n", filename);
//    PUSH1(-1);
//    return;
//  }
//
//  int len = fread(buf + sizeof(cell), 1, size, fp);
//  if (len != size)
//  {
//    free(buf);
//    cf_printf(s, "Unable to read '%s'\n", filename);
//    PUSH1(-1);
//    return;
//  }
//
//  cell *cbuf = (cell *)buf;
//  *cbuf = (cell)size;
//
//  fclose(fp);
//}

//void
//save_file(struct state *s)
//{
//  POP2();
//  char *filename = CFSTRING2C(p1);
//  char *str = CFSTRING2C(p2);
//
//  FILE *fp = fopen(filename, "w");
//
//  if (!fp)
//  {
//    cf_printf(s, "Unable to read '%s'\n", filename);
//    PUSH1(-1);
//    return;
//  }
//
//  fwrite(str, 1, *(cell *)p2, fp);
//
//  fclose(fp);
//}
//
//void
//included_file(struct state *s)
//{
//  POP1();
//  char *filename = CFSTRING2C(p1);
//  parse_from_file(s, filename);
//}
//
//void
//require_io_fn(struct state *state)
//{
//  if (initialized) return;
//
//  define_primitive_extension(state, FILE_SUBSIZE_HASH,   ENTRY_NAME("file-size"), file_size_fn);
//  define_primitive_extension(state, FILE_LOAD_HASH,      ENTRY_NAME("load"), load_file);
//  define_primitive_extension(state, FILE_SAVE_HASH,      ENTRY_NAME("save"), save_file);
//  define_primitive_extension(state, INCLUDED_HASH,       ENTRY_NAME("included"), included_file);
//
//  initialized = 1;
//}

#endif /* __SECTION_FUNCTION */
