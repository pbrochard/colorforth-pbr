// The author disclaims copyright to this source code.

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_THREAD__RUN            (opcode_t) 0xE47BB892    // thread/run
#define OP_THREAD__JOIN_SUBALL    (opcode_t) 0x9B920C1F    // thread/join-all
#define OP_THREAD__JOIN           (opcode_t) 0x37303F01    // thread/join
#define OP_THREAD__KILL           (opcode_t) 0x6B3D7E01    // thread/kill
#define OP_THREAD__LOCK           (opcode_t) 0x91795D9A    // thread/lock
#define OP_THREAD__UNLOCK         (opcode_t) 0xE4DECEBD    // thread/unlock



#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("thread/run"),      OP_THREAD__RUN);
define_primitive(s, ENTRY_NAME("thread/join-all"), OP_THREAD__JOIN_SUBALL);
define_primitive(s, ENTRY_NAME("thread/join"),     OP_THREAD__JOIN);
define_primitive(s, ENTRY_NAME("thread/kill"),     OP_THREAD__KILL);
define_primitive(s, ENTRY_NAME("thread/lock"),     OP_THREAD__LOCK);
define_primitive(s, ENTRY_NAME("thread/unlock"),   OP_THREAD__UNLOCK);


#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_THREAD__RUN:
{
  POP2();
  cell n = p1;
  struct entry *entry = ENTRY(p2);

  if (n >= MAX_THREAD) {
    cf_printf(s, "Too many threads. At most %d allowed\n", MAX_THREAD);
    PUSH1(-1);
    return;
  }

  if (!initialized) {
    for (int i = 0; i < MAX_LOCK; i++)
    {
      sem_init(&locks[i], 0, 1);
    }
    initialized = 1;
  }

  struct state *clone = clone_state(s);

  thread_args[p1].clone = clone;
  thread_args[p1].entry = entry;

  pthread_create(&thread_args[p1].pthread, NULL, perform_thread, (void *) &thread_args[p1]);

  PUSH1(n);

  break;
}

case OP_THREAD__JOIN_SUBALL:
{
  for (int i = 0; i < MAX_THREAD; i++)
  {
    pthread_join(thread_args[i].pthread, NULL);
  }
  break;
}

case OP_THREAD__JOIN:
{
  POP1();

  pthread_join(thread_args[p1].pthread, NULL);

  break;
}

case OP_THREAD__KILL:
{
  POP1();

  pthread_kill(thread_args[p1].pthread, SIGUSR1);
  pthread_join(thread_args[p1].pthread, NULL);

  pthread_kill(thread_args[p1].pthread, 0);
  pthread_join(thread_args[p1].pthread, NULL);

  free_clone_state(thread_args[p1].clone);

  break;
}

case OP_THREAD__LOCK:
{
  POP1();

  sem_wait(&locks[p1]);

  break;
}

case OP_THREAD__UNLOCK:
{
  POP1();

  sem_post(&locks[p1]);

  break;
}


#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#ifdef __THREADS

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>

static char initialized = 0;

#ifdef __EXTENDED_MATH
extern void init_fstack(struct fstack *stack, int len);
#endif

#ifdef __MP_MATH
extern void init_mpstack(struct mpstack *stack, int len);
#endif

struct thread_args
{
  pthread_t pthread;
  struct state *clone;
  struct entry *entry;
};

struct thread_args thread_args[MAX_THREAD];
sem_t locks[MAX_LOCK];

extern void init_stack(struct stack *stack, int len, unsigned char id);
extern void execute(struct state *s);
extern void execute_(struct state *s, struct entry *entry);

struct state *
clone_state(struct state *s)
{
  struct state *clone = cf_calloc(s, 1, sizeof(*s), THREAD_CLONE_STATE_ERROR);
  clone->color = execute;

  clone->base = 10;

  clone->dict.entries = s->dict.entries;
  clone->dict.latest = s->dict.latest;

  clone->stack = cf_calloc(s, 1, sizeof(struct stack), THREAD_STACK_ERROR);
  init_stack(clone->stack, STACK_SIZE, THREAD_INIT_STACK_ERROR);

  clone->r_stack = cf_calloc(s, 1, sizeof(struct stack), THREAD_RSTACK_ERROR);
  init_stack(clone->r_stack, R_STACK_SIZE, THREAD_INIT_RSTACK_ERROR);

  clone->heap = s->heap;
  clone->here = s->here;

  clone->done = 0;
  clone->echo_on = 0;

  clone->str_stream = NULL;
  clone->file_stream = NULL;

#ifdef __EXTENDED_MATH
  init_fstack(&clone->fstack, FSTACK_SIZE);
#endif

#ifdef __MP_MATH
  init_mpstack(&clone->mpstack, MPSTACK_SIZE);
#endif

  return clone;
}

void
free_clone_state(struct state *clone)
{
  free(clone->stack);
  free(clone->r_stack);

#ifdef __EXTENDED_MATH
  free(clone->fstack.cells);
#endif

#ifdef __MP_MATH
  free(clone->mpstack.cells);
#endif

  free(clone);
}

void
thread_exit_handler(int sig)
{
  pthread_exit(0);
}

void *
perform_thread(void *arg)
{
  struct thread_args *thread_args = (struct thread_args *) arg;

  struct sigaction actions;
  memset(&actions, 0, sizeof(actions));
  sigemptyset(&actions.sa_mask);
  actions.sa_flags = 0;
  actions.sa_handler = thread_exit_handler;
  sigaction(SIGUSR1,&actions,NULL);

  execute_(thread_args->clone, thread_args->entry);

  free_clone_state(thread_args->clone);

  return NULL;
}

#endif /* __THREADS */

#endif /* __SECTION_FUNCTION */
