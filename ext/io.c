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

define_primitive(s, ENTRY_NAME("getchar"),      OP_GETCHAR);
define_primitive(s, ENTRY_NAME("echo"),         OP_ECHO_ADDR);
define_primitive(s, ENTRY_NAME("file-size"),    OP_FILE_SUBSIZE);
define_primitive(s, ENTRY_NAME("load"),         OP_FILE_LOAD);
define_primitive(s, ENTRY_NAME("save"),         OP_FILE_SAVE);

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

case OP_FILE_SUBSIZE: {
  POP1();
  char *filename = CFSTRING2C(p1);

  int size = file_size(filename);

  if (size == -1) {
    cf_printf(s, "Unable to read '%s'\n", filename);
    PUSH1(-1);
    break;
  }

  PUSH1((cell)size);
  PUSH1(0);
  break;
}

case OP_FILE_LOAD: {
  load_file(s);
  break;
}

case OP_FILE_SAVE: {
  save_file(s);
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

void
load_file(struct state *s)
{
  POP2();
  char *filename = CFSTRING2C(p1);
  char *buf = (char *) p2;

  int size = file_size(filename);

  if (size == -1)
  {
    cf_printf(s, "Unable to read '%s'\n", filename);
    PUSH1(-1);
    return;
  }

  FILE *fp = fopen(filename, "r");

  if (!fp)
  {
    cf_printf(s, "Unable to read '%s'\n", filename);
    PUSH1(-1);
    return;
  }

  int len = fread(buf, 1, size, fp);
  if (len != size)
  {
    free(buf);
    cf_printf(s, "Unable to read '%s'\n", filename);
    PUSH1(-1);
    return;
  }

  PUSH1(1);

  fclose(fp);
}

void
save_file(struct state *s)
{
  POP3();
  char *filename = CFSTRING2C(p1);
  cell len = p2;
  char *buf = (char *) p3;

  FILE *fp = fopen(filename, "w");

  if (!fp)
  {
    cf_printf(s, "Unable to read '%s'\n", filename);
    PUSH1(-1);
    return;
  }

  fwrite(buf, 1, len, fp);

  fclose(fp);

  PUSH(1);
}

//void
//included_file(struct state *s)
//{
//  POP1();
//  char *filename = CFSTRING2C(p1);
//  parse_from_file(s, filename);
//}

#endif /* __SECTION_FUNCTION */
