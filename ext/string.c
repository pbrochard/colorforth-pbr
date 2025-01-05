// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_SN_PLUS                      (opcode_t) 0x1F8B590A                // sn+

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("sn+"), OP_SN_PLUS);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_SN_PLUS:
{
  POP2();

  char *str = (char *) p2 + sizeof(cell);
  cell *len_addr = (cell *) p2;
  char *base = str + *len_addr;

  switch (s->base)
  {
    case 16:
      sprintf(base, "0x%02lX", p1);
      break;
    case 2:
      sprintf(base++, "b");
      if (p1 == 0)
      {
        sprintf(base++, "0");
      } else {
        int i = CF_CHAR_BIT * sizeof p1;
        char output = 0;
        while(i--)
        {
          const char n = ((p1 >> i) & 1);
          if (n) output = 1;
          if (output) sprintf(base++, "%c", '0' + n);
        }
      }
      break;
    default:
      sprintf(base, CELL_FMT, p1);
      break;
  }

  *len_addr = strlen(str);

  PUSH(p2);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#define CFSTRING2C(str) ((char *)(str + sizeof(cell)))
#define CFSTRINGLEN(str) (str)

#endif /* __SECTION_FUNCTION */
