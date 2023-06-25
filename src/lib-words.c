case OP_BASE: {
  ENSURE_STACK_MAX(1);
  PUSH((cell) &s->base);
  break;
}
