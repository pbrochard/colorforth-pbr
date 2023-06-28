// The author disclaims copyright to this source code.

case OP_BASE: {
  ENSURE_STACK_MAX(1);
  PUSH((cell) &s->base);
  break;
}

case OP_ENTRY_IS: {
  POP2();
  ENTRY(p2)->offset = ENTRY(p1)->offset;
  break;
}

case OP_ENTRY_C_IS: {
  POP2();
  ENTRY(p2)->offset = p1;
  break;
}
