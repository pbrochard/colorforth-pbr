// The author disclaims copyright to this source code.

case OP_GETCHAR: {
  PUSH1(getchar());
  break;
}

case OP_ECHO_ADDR: {
  PUSH1((cell) &s->echo_on);
  break;
}
