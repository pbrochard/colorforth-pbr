// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_TIME                      (opcode_t) 0xA16F62B9                // time
#define OP_UTIME                     (opcode_t) 0x9592595E                // utime
#define OP_SLEEP                     (opcode_t) 0xD91187F3                // sleep
#define OP_MSSLEEP                   (opcode_t) 0xBAD535EF                // mssleep

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("time"),    OP_TIME);    // t ime_fn);
define_primitive(s, ENTRY_NAME("utime"),   OP_UTIME);   // utime_fn);
define_primitive(s, ENTRY_NAME("sleep"),   OP_SLEEP);   // sleep_fn);
define_primitive(s, ENTRY_NAME("mssleep"), OP_MSSLEEP); // mssleep_fn);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH


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

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#endif /* __SECTION_FUNCTION */
