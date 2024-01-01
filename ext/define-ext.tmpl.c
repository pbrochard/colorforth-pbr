// The author disclaims copyright to this source code.
//
// Extensions system: include only what you need

// io
define_primitive(s, ENTRY_NAME("getchar"), OP_GETCHAR);
define_primitive(s, ENTRY_NAME("echo"), OP_ECHO_ADDR);

// time
define_primitive(s, ENTRY_NAME("time"),    OP_TIME);    // t ime_fn);
define_primitive(s, ENTRY_NAME("utime"),   OP_UTIME);   // utime_fn);
define_primitive(s, ENTRY_NAME("sleep"),   OP_SLEEP);   // sleep_fn);
define_primitive(s, ENTRY_NAME("mssleep"), OP_MSSLEEP); // mssleep_fn);

// math
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
