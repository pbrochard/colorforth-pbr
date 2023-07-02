case OP_PARSE: {
  POP1();
  parse_colorforth(s, p1);
  break;
}

case OP_CLEAR_TIB: {
  clear_tib(s);
  break;
}
