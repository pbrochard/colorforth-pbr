// The author disclaims copyright to this source code.

#define modulo(n2, n1) ((n2 < 0) ? (n2 % n1 + n1) : (n2 % n1))

case OP_DIV: {
  POP2();
  PUSH1(p2 / p1);
  break;
}

case OP_MOD: {
  POP2();
  PUSH1(modulo(p2, p1));
  break;
}

case OP_DIVMOD: {
  POP2();
  PUSH2(p2 / p1, modulo(p2, p1));
  break;
}

case OP_MUL_DIV: {
  POP3();
  PUSH1(p3 * p2 / p1);
  break;
}

case OP_LSHIFT: {
  POP2();
  PUSH1(p2 << p1);
  break;
}

case OP_RSHIFT: {
  POP2();
  PUSH1(p2 >> p1);
  break;
}

case OP_SUP: {
  POP2();
  PUSH1(p2 > p1);
  break;
}

case OP_INF_EQUAL: {
  POP2();
  PUSH1(p2 <= p1);
  break;
}

case OP_SUP_EQUAL: {
  POP2();
  PUSH1(p2 >= p1);
  break;
}

case OP_INFSUP: {
  POP2();
  PUSH1(p2 != p1);
  break;
}

case OP_OR: {
  POP2();
  PUSH1(p2 || p1);
  break;
}

case OP_AND: {
  POP2();
  PUSH1(p2 && p1);
  break;
}

case OP_MIN: {
  POP2();
  PUSH1(p1 < p2 ? p1 : p2);
  break;
}

case OP_MAX: {
  POP2();
  PUSH1(p1 > p2 ? p1 : p2);
  break;
}

case OP_ABS: {
  POP1();
  PUSH1(labs(p1));
  break;
}

case OP_RAND: {
  PUSH1(rand());
  break;
}

case OP_SRAND: {
  POP1();
  srand(p1);
  break;
}

case OP_RANDOM: {
  POP1();
  PUSH1(p1 != 0 ? rand() % p1 : 0);
  break;
}
