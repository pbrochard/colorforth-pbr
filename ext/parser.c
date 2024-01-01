// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_PARSE                     (opcode_t) 0x9555EDEF                // parse
#define OP_CLEAR_TIB                 (opcode_t) 0xDE5DBC77                // clear-tib

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("parse"), OP_PARSE);
define_primitive(s, ENTRY_NAME("clear-tib"), OP_CLEAR_TIB);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_PARSE: {
  POP1();
  parse_colorforth(s, p1);
  break;
}

case OP_CLEAR_TIB: {
  clear_tib(s);
  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#endif /* __SECTION_FUNCTION */
