// The author disclaims copyright to this source code.
//
// Extensions system: include only what you need

// parser
define_primitive(s, ENTRY_NAME("parse"), OP_PARSE);
define_primitive(s, ENTRY_NAME("clear-tib"), OP_CLEAR_TIB);

// io
define_primitive(s, ENTRY_NAME("getchar"), OP_GETCHAR);
define_primitive(s, ENTRY_NAME("echo"), OP_ECHO_ADDR);
