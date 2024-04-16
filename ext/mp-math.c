// The author disclaims copyright to this source code.

#ifdef __MP_MATH

/**********************************************************************************
 *   PREFIX DEF
 *********************************************************************************/
#ifdef __SECTION_PREFIX_DEF

case '#': { s->color = define_mpz; echo_color(s, c, COLOR_MAGENTA); return; }

#endif /* __SECTION_PREFIX_DEF */


/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_MPZ               (opcode_t) 0xE300F30D      // mpz

#define OP_M_DOTS            (opcode_t) 0xE18EAD58      // m.s
#define OP_M_DOT             (opcode_t) 0x510E543B      // m.

#define OP_MDROP             (opcode_t) 0x864B7ACE      // mdrop
#define OP_MDUP              (opcode_t) 0xE0DC5F8C      // mdup
#define OP_MSWAP             (opcode_t) 0x967583F0      // mswap
#define OP_MOVER             (opcode_t) 0x37AA046D      // mover
#define OP_MROT              (opcode_t) 0xE60E870C      // mrot
#define OP_M_SUBROT          (opcode_t) 0xDC31BA2F      // m-rot
#define OP_MNIP              (opcode_t) 0x7022FC52      // mnip

#define OP_M_ADD             (opcode_t) 0x540E58F4      // m+
#define OP_M_SUB             (opcode_t) 0x520E55CE      // m-
#define OP_M_MUL             (opcode_t) 0x550E5A87      // m*
#define OP_M_DIV             (opcode_t) 0x500E52A8      // m/

#define OP_M_SUP             (opcode_t) 0x410E3B0B      // m>
#define OP_M_INF             (opcode_t) 0x430E3E31      // m<
#define OP_M_EQUAL           (opcode_t) 0x420E3C9E      // m=

#define OP_M_LOAD            (opcode_t) 0x6F0E8375      // m@
#define OP_M_STORE           (opcode_t) 0x4E0E4F82      // m!
#define OP_M_INLINE          (opcode_t) 0xDC27337F      // [m,]


#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("mpz"),    OP_MPZ);

define_primitive(s, ENTRY_NAME("m.s"),    OP_M_DOTS);
define_primitive(s, ENTRY_NAME("m."),     OP_M_DOT);

define_primitive(s, ENTRY_NAME("mdrop"),  OP_MDROP);
define_primitive(s, ENTRY_NAME("mdup"),   OP_MDUP);
define_primitive(s, ENTRY_NAME("mswap"),  OP_MSWAP);
define_primitive(s, ENTRY_NAME("mover"),  OP_MOVER);
define_primitive(s, ENTRY_NAME("mrot"),   OP_MROT);
define_primitive(s, ENTRY_NAME("m-rot"),  OP_M_SUBROT);
define_primitive(s, ENTRY_NAME("mnip"),   OP_MNIP);

define_primitive(s, ENTRY_NAME("m+"),     OP_M_ADD);
define_primitive(s, ENTRY_NAME("m-"),     OP_M_SUB);
define_primitive(s, ENTRY_NAME("m*"),     OP_M_MUL);
define_primitive(s, ENTRY_NAME("m/"),     OP_M_DIV);

define_primitive(s, ENTRY_NAME("m>"),     OP_M_SUP);
define_primitive(s, ENTRY_NAME("m<"),     OP_M_INF);
define_primitive(s, ENTRY_NAME("m="),     OP_M_EQUAL);

define_primitive(s, ENTRY_NAME("m@"),     OP_M_LOAD);
define_primitive(s, ENTRY_NAME("m!"),     OP_M_STORE );

define_primitive(s, ENTRY_NAME("[m,]"),   OP_M_INLINE);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_MPZ: {
  PUSH1(sizeof(mpz_t));
  break;
}

case OP_M_DOTS: {
  char *out;

  for (int i = 0, p = s->mpstack.sp + 1; i <= s->mpstack.lim; i++, p++)
  {
    if (p > s->mpstack.lim) p = 0;

    if (i <= s->mpstack.lim - 8) continue;

    gmp_asprintf(&out, "%Zd", s->mpstack.cells[p]);
    cf_printf(s, "%s ", out);
    free(out);
  }
  cf_printf(s, " <mtos\n");

  break;
}

case OP_M_DOT: {
  char *out;

  const int psp = get_s_psp(s);
  gmp_asprintf(&out, "%Zd", s_cells(s, s_sp(s)));
  cf_printf(s, "%s ", out);
  cf_fflush();
  free(out);
  s_sp(s) = psp;

  break;
}

case OP_MDROP: {
  const int psp = get_s_psp(s);
  s_sp(s) = psp;

  break;
}

case OP_MDUP: {
  const int nsp = get_s_nsp(s);
  mpz_set(s_cells(s, nsp), s_cells(s, s_sp(s)));
  s_sp(s) = nsp;

  break;
}

case OP_MSWAP: {
  const int psp = get_s_psp(s);
  mpz_swap(s_cells(s, psp), s_cells(s, s_sp(s)));

  break;
}

case OP_MOVER: {
  const int psp = get_s_psp(s);
  const int nsp = get_s_nsp(s);

  mpz_set(s_cells(s, nsp), s_cells(s, psp));

  s_sp(s) = nsp;

  break;
}

case OP_MROT: {
  const int psp = get_s_psp(s);
  const int ppsp = get_psp(psp, s_lim(s));

  mpz_t n;
  mpz_init(n);

  mpz_set(n, s_cells(s, s_sp(s)));
  mpz_set(s_cells(s, s_sp(s)), s_cells(s, ppsp));
  mpz_set(s_cells(s, ppsp), s_cells(s, psp));
  mpz_set(s_cells(s, psp), n);

  mpz_clear(n);

  break;
}

case OP_M_SUBROT: {
  const int psp = get_s_psp(s);
  const int ppsp = get_psp(psp, s_lim(s));

  mpz_t n;
  mpz_init(n);

  mpz_set(n, s_cells(s, s_sp(s)));
  mpz_set(s_cells(s, s_sp(s)), s_cells(s, psp));
  mpz_set(s_cells(s, psp), s_cells(s, ppsp));
  mpz_set(s_cells(s, ppsp), n);

  mpz_clear(n);

  break;
}

case OP_MNIP: {
  const int psp = get_s_psp(s);
  mpz_set(s_cells(s, psp), s_cells(s, s_sp(s)));
  s_sp(s) = psp;

  break;
}

case OP_M_ADD: {
  const int psp = get_s_psp(s);

  mpz_add(s_cells(s, psp), s_cells(s, s_sp(s)), s_cells(s, psp));

  s_sp(s) = psp;

  break;
}

case OP_M_SUB: {
  const int psp = get_s_psp(s);

  mpz_sub(s_cells(s, psp), s_cells(s, psp), s_cells(s, s_sp(s)));

  s_sp(s) = psp;

  break;
}

case OP_M_MUL: {
  const int psp = get_s_psp(s);

  mpz_mul(s_cells(s, psp), s_cells(s, psp), s_cells(s, s_sp(s)));

  s_sp(s) = psp;

  break;
}

case OP_M_DIV: {
  const int psp = get_s_psp(s);

  mpz_fdiv_q(s_cells(s, psp), s_cells(s, psp), s_cells(s, s_sp(s)));

  s_sp(s) = psp;

  break;
}

case OP_M_SUP: {
  const int psp = get_s_psp(s);
  PUSH1(mpz_cmp(s_cells(s, psp), s_cells(s, s_sp(s))) > 0);
  s_sp(s) = get_psp(psp, s_lim(s));

  break;
}

case OP_M_INF: {
  const int psp = get_s_psp(s);
  PUSH1(mpz_cmp(s_cells(s, psp), s_cells(s, s_sp(s))) < 0);
  s_sp(s) = get_psp(psp, s_lim(s));

  break;
}

case OP_M_EQUAL: {
  const int psp = get_s_psp(s);
  PUSH1(mpz_cmp(s_cells(s, psp), s_cells(s, s_sp(s))) == 0);
  s_sp(s) = get_psp(psp, s_lim(s));

  break;
}

case OP_M_LOAD: {
  POP1();
  s_sp(s) = get_s_nsp(s);
  mpz_set(s_cells(s, s_sp(s)), *(mpz_t*)p1);

  break;
}

case OP_M_STORE : {
  POP1();
  mpz_t *ptr = (mpz_t*)p1;
  mpz_init(*ptr);
  mpz_set(*ptr, s_cells(s, s_sp(s)));
  s_sp(s) = get_s_psp(s);

  break;
}

case OP_M_INLINE: {
  mpz_t *ptr = cf_calloc(s, 1, sizeof(mpz_t), MP_LITERAL_ERROR);
  mpz_init(*ptr);
  mpz_set(*ptr, s_cells(s, s_sp(s)));;
  s_sp(s) = get_s_psp(s);

  STORE(OP_NUMBER, opcode_t);
  STORE((cell)ptr, cell);

  break;
}

#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#define s_sp(s) s->mpstack.sp
#define s_lim(s) s->mpstack.lim
#define s_cells(s, sp) s->mpstack.cells[sp]

#define get_psp(sp, lim) (sp == 0 ? lim : sp - 1)
#define get_nsp(sp, lim) (sp == lim ? 0 : sp + 1)

#define get_s_psp(s) get_psp(s_sp(s), s_lim(s))
#define get_s_nsp(s) get_nsp(s_sp(s), s_lim(s))

static char mp_initialized = 0;

void
init_mpstack(struct mpstack *stack, int len)
{
  stack->cells = cf_calloc(NULL, len, sizeof(mpz_t), MP_STACK_INIT_ERROR);
  for (int i = 0; i < MPSTACK_SIZE; i++)
  {
    mpz_init(stack->cells[i]);
  }
  stack->sp = 0;
  stack->lim = len - 1;
}


void
define_mpz(struct state *s)
{
  if (!mp_initialized) {
    init_mpstack(&s->mpstack, MPSTACK_SIZE);
    mp_initialized = 1;
  }

  const int nsp = get_s_nsp(s);
  s_sp(s) = nsp;
  mpz_set_str(s_cells(s, s_sp(s)), s->tib.buf, 10);
}

#endif /* __MP_MATH */

#endif /* __SECTION_FUNCTION */
