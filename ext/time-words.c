// The author disclaims copyright to this source code.

case OP_TIME: {
  time_t t;
  PUSH1((unsigned) time(&t));
  break;
}

case OP_UTIME: {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  PUSH1(tv.tv_sec * 1000000 + tv.tv_usec);
  break;
}

case OP_SLEEP: {
  POP1();
  sleep(p1);
  break;
}

case OP_MSSLEEP: {
  POP1();

  struct timespec ts;
  ts.tv_sec = p1 / 1000;
  ts.tv_nsec = (p1 % 1000) * 1000000;

  nanosleep(&ts, NULL);
  break;
}
