#ifndef __HASH_DEF
#define __HASH_DEF

#include <stdint.h>

typedef uint32_t hash_t;
typedef hash_t opcode_t;

#ifdef __KEEP_ENTRY_NAMES
#define ENTRY_NAME(x) (x)
#else
#define ENTRY_NAME(x) (NULL)
#endif

// Define __SHOW_MISSING_HASH in conf.h to display name <-> hash relationship
//
// Use `.hash" <string to hash>"` to find them in colorForth

// Internal OP
#define OP_CALL                      (opcode_t) 0xF85D926E                // __OP_CALL
#define OP_TAIL_CALL                 (opcode_t) 0x1A03DDDD                // __OP_TAIL_CALL
#define OP_NUMBER                    (opcode_t) 0xA2AB56D7                // __OP_NUMBER
#define OP_TICK_NUMBER               (opcode_t) 0x544A7A21                // __OP_TICK_NUMBER

// <-- BEGIN AUTOGEN PART -->

// src/colorforth.c
#define OP_NOP                       (opcode_t) 0x5964713D                // nop
#define OP_PRINT_TOS                 (opcode_t) 0x2E00486A                // .
#define OP_DUP                       (opcode_t) 0xF500DB1                 // dup
#define OP_OVER                      (opcode_t) 0x38C2FE2A                // over
#define OP_SWAP                      (opcode_t) 0xD902F543                // swap
#define OP_DROP                      (opcode_t) 0x1940D1AD                // drop
#define OP_ROT                       (opcode_t) 0x7D519FD                 // rot
#define OP_MINUS_ROT                 (opcode_t) 0xE8E1884C                // -rot
#define OP_NIP                       (opcode_t) 0x4D5E4E2B                // nip
#define OP_ADD                       (opcode_t) 0x2B0043B1                // +
#define OP_SUB                       (opcode_t) 0x2D0046D7                // -
#define OP_MUL                       (opcode_t) 0x2A00421E                // *
#define OP_EQUAL                     (opcode_t) 0x3D006007                // =
#define OP_LESS                      (opcode_t) 0x3C005E74                // <
#define OP_BYE                       (opcode_t) 0x253F7458                // bye
#define OP_WORDS                     (opcode_t) 0x30E76679                // words
#define OP_EMIT                      (opcode_t) 0x9B01D09B                // emit
#define OP_KEY                       (opcode_t) 0x485BCDF                 // key
#define OP_LOAD                      (opcode_t) 0x400064C0                // @
#define OP_STORE                     (opcode_t) 0x210033F3                // !
#define OP_CLOAD                     (opcode_t) 0x72F4F1DB                // c@
#define OP_CSTORE                    (opcode_t) 0xD1F58768                // c!
#define OP_CELL                      (opcode_t) 0x1415DDAC                // cell
#define OP_HERE                      (opcode_t) 0xD786E25E                // here
#define OP_HERE_ADDR                 (opcode_t) 0xAE504314                // &here
#define OP_HEAP_ADDR                 (opcode_t) 0x89705C80                // &heap
#define OP_HEAP_SIZE                 (opcode_t) 0xC2A05C60                // heap-size
#define OP_LATEST                    (opcode_t) 0xA307AFAB                // latest
#define OP_COMPILE                   (opcode_t) 0x12AD19B0                // [^]
#define OP_COMPILE_LITERAL           (opcode_t) 0x176F15FE                // [,]
#define OP_GET_ENTRY_CODE            (opcode_t) 0xC0F56CA5                // c>
#define OP_EXECUTE                   (opcode_t) 0x61A52EA0                // call
#define OP_EXECUTE_STAR              (opcode_t) 0x4108433E                // call*
#define OP_IF                        (opcode_t) 0x790405D7                // if
#define OP_IF_TAIL_CALL              (opcode_t) 0x7E556D47                // if*
#define OP_IF_EXIT                   (opcode_t) 0x6D555284                // if;
#define OP_IF_NOT                    (opcode_t) 0x1A0E810B                // if-not
#define OP_IF_NOT_TAIL_CALL          (opcode_t) 0x25D546F3                // if-not*
#define OP_IF_NOT_EXIT               (opcode_t) 0x34D55E90                // if-not;
#define OP_IF_ELSE                   (opcode_t) 0xD59EAA1B                // if-else
#define OP_DOT_S                     (opcode_t) 0x83717F5B                // .s
#define OP_RETURN                    (opcode_t) 0x3B005CE1                // ;
#define OP_R_PUSH                    (opcode_t) 0x6299EDD8                // >R
#define OP_R_POP                     (opcode_t) 0x3ECB51F8                // R>
#define OP_R_FETCH                   (opcode_t) 0x6CCB9A62                // R@
#define OP_CLEAR                     (opcode_t) 0x93C5A06D                // clear

// src/lib.c
#define OP_HASH                      (opcode_t) 0x3475B2F0                // hash
#define OP_BASE                      (opcode_t) 0x7D3CE245                // base
#define OP_ENTRY_IS                  (opcode_t) 0x84041728                // is
#define OP_ENTRY_C_IS                (opcode_t) 0x6F1B27F5                // c>is
#define OP_ENTRY_HIDE                (opcode_t) 0x7C95E439                // entry/hide
#define OP_ROOM                      (opcode_t) 0xE48409A3                // room
#define OP_DROP_ROOM                 (opcode_t) 0xC57E1E23                // drop-room

// Register A
#define OP_REG_A_LOAD                (opcode_t) 0x66A0AFE9                // A@
#define OP_REG_A_STORE               (opcode_t) 0xC5A14576                // A!
#define OP_REG_A_ADD                 (opcode_t) 0x57EF066B                // A+!
#define OP_REG_A_INC                 (opcode_t) 0x51EEFCF9                // A++
#define OP_REG_A_DEC                 (opcode_t) 0x77FE4355                // A--
#define OP_REG_A_TO_R                (opcode_t) 0x2D43D1F                 // A>R
#define OP_REG_R_TO_A_               (opcode_t) 0x9311A63B                // R>A

// Register B
#define OP_REG_B_LOAD                (opcode_t) 0x8CA32A52                // B@
#define OP_REG_B_STORE               (opcode_t) 0xADA35E45                // B!
#define OP_REG_B_ADD                 (opcode_t) 0x603C1122                // B+!
#define OP_REG_B_INC                 (opcode_t) 0x663C1A94                // B++
#define OP_REG_B_DEC                 (opcode_t) 0x603793F4                // B--
#define OP_REG_B_TO_R                (opcode_t) 0x755808AE                // B>R
#define OP_REG_R_TO_B_               (opcode_t) 0x9411A7CE                // R>B

// Register C
#define OP_REG_C_LOAD                (opcode_t) 0xB2A5A4BB                // C@
#define OP_REG_C_STORE               (opcode_t) 0xD1A5D588                // C!
#define OP_REG_C_ADD                 (opcode_t) 0xCD007A95                // C+!
#define OP_REG_C_INC                 (opcode_t) 0xD3008407                // C++
#define OP_REG_C_DEC                 (opcode_t) 0xCD04F7C3                // C--
#define OP_REG_C_TO_R                (opcode_t) 0xDBE4BBB5                // C>R
#define OP_REG_R_TO_C_               (opcode_t) 0x9511A961                // R>C

// Register I
#define OP_REG_I_LOAD                (opcode_t) 0x96B48331                // I@
#define OP_REG_I_STORE               (opcode_t) 0xB5B4B3FE                // I!
#define OP_REG_I_ADD                 (opcode_t) 0xAE5EC4B3                // I+!
#define OP_REG_I_INC                 (opcode_t) 0xB85ED471                // I++
#define OP_REG_I_DEC                 (opcode_t) 0x5E6D514D                // I--
#define OP_REG_I_TO_R                (opcode_t) 0x79924CA7                // I>R
#define OP_REG_R_TO_I_               (opcode_t) 0x8B1199A3                // R>I

// Register J
#define OP_REG_J_LOAD                (opcode_t) 0xBCB6FD9A                // J@
#define OP_REG_J_STORE               (opcode_t) 0xDDB7318D                // J!
#define OP_REG_J_ADD                 (opcode_t) 0x374A69AA                // J+!
#define OP_REG_J_INC                 (opcode_t) 0x2D4A59EC                // J++
#define OP_REG_J_DEC                 (opcode_t) 0xA74509CC                // J--
#define OP_REG_J_TO_R                (opcode_t) 0xCC15E5D6                // J>R
#define OP_REG_R_TO_J_               (opcode_t) 0x8C119B36                // R>J

// Register K
#define OP_REG_K_LOAD                (opcode_t) 0x62BA4183 // K@
#define OP_REG_K_STORE               (opcode_t) 0x41BA0D90 // K!
#define OP_REG_K_ADD                 (opcode_t) 0xA4FC55BD // K+!
#define OP_REG_K_INC                 (opcode_t) 0x9AFC45FF // K++
#define OP_REG_K_DEC                 (opcode_t) 0xB500EC1B // K--
#define OP_REG_K_TO_R                (opcode_t) 0x93E0647D // K>R
#define OP_REG_R_TO_K_               (opcode_t) 0x8D119CC9 // R>K

#define OP_IJK_TO_R                  (opcode_t) 0x1B91C8D0 // IJK>R
#define OP_R_TO_KJI                  (opcode_t) 0x22D5F650 // R>KJI
// <-- END AUTOGEN PART -->

#include "ext-hash_def.h"

#endif /* __HASH_DEF */
