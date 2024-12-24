#ifndef __EXT_HASH_DEF
#define __EXT_HASH_DEF

// ext/ext-math.c

// ext/mp-math.c
#define OP_MPZ                       (opcode_t) 0xE300F30D                // mpz
#define OP_M_DOTS                    (opcode_t) 0xE18EAD58                // m.s
#define OP_M_DOT                     (opcode_t) 0x510E543B                // m.
#define OP_MDROP                     (opcode_t) 0x864B7ACE                // mdrop
#define OP_MDUP                      (opcode_t) 0xE0DC5F8C                // mdup
#define OP_MSWAP                     (opcode_t) 0x967583F0                // mswap
#define OP_MOVER                     (opcode_t) 0x37AA046D                // mover
#define OP_MROT                      (opcode_t) 0xE60E870C                // mrot
#define OP_M_SUBROT                  (opcode_t) 0xDC31BA2F                // m-rot
#define OP_MNIP                      (opcode_t) 0x7022FC52                // mnip
#define OP_M_ADD                     (opcode_t) 0x540E58F4                // m+
#define OP_M_SUB                     (opcode_t) 0x520E55CE                // m-
#define OP_M_MUL                     (opcode_t) 0x550E5A87                // m*
#define OP_M_DIV                     (opcode_t) 0x500E52A8                // m/
#define OP_M_TO_                     (opcode_t) 0x410E3B0B                // m>
#define OP_M_FROM                    (opcode_t) 0x430E3E31                // m<
#define OP_M_EQUAL                   (opcode_t) 0x420E3C9E                // m=
#define OP_M_LOAD                    (opcode_t) 0x6F0E8375                // m@
#define OP_M_STORE                   (opcode_t) 0x4E0E4F82                // m!
#define OP_M_INLINE                  (opcode_t) 0xDC27337F                // [m,]

// ext/network.c
#define OP_SERVER_START              (opcode_t) 0x3F90A4AA                // server-start
#define OP_CLIENT_START              (opcode_t) 0x54C4D466                // client-start
#define OP_SERVER_STOP               (opcode_t) 0x73F7E84A                // server-stop
#define OP_SERVER_NONBLOCKING        (opcode_t) 0x3A7FBA86                // server-nonblocking
#define OP_SERVER_ACCEPT             (opcode_t) 0xA66BDA62                // server-accept
#define OP_SOCKET_SEND               (opcode_t) 0xB830ECB2                // socket-send
#define OP_SOCKET_SEND_CHAR          (opcode_t) 0x49DA8E15                // socket-send-char
#define OP_SOCKET_RECV               (opcode_t) 0x9897D554                // socket-recv

// ext/os.c
#define OP_SYSTEM                    (opcode_t) 0x7BB8F701                // system
#define OP_C_SUBALLOC                (opcode_t) 0xF25B6721                // c-alloc
#define OP_C_SUBFREE                 (opcode_t) 0x318C2312                // c-free

// ext/sdl.c
#define OP_SDL_INIT                  (opcode_t) 0x92FE07C0                // sdl/init
#define OP_SDL_CLOSE                 (opcode_t) 0xFAD1E96                 // sdl/close
#define OP_SDL_DELAY                 (opcode_t) 0xD811784D                // sdl/delay
#define OP_SDL_SHOW_CURSOR           (opcode_t) 0x6BD0F784                // sdl/show-cursor
#define OP_SDL_HIDE_CURSOR           (opcode_t) 0xB3052F5F                // sdl/hide-cursor
#define OP_SDL_POLL_EVENT            (opcode_t) 0x42D5F536                // sdl/poll-event
#define OP_SDL_PRESENT               (opcode_t) 0x1B628525                // sdl/present
#define OP_SDL_KEY_PRESS             (opcode_t) 0x4224F69A                // sdl/key?
#define OP_SDL_MOUSE_BUTTON          (opcode_t) 0x6755EA17                // sdl/button?
#define OP_SDL_GET_MOUSE_X           (opcode_t) 0x9E5030C4                // sdl/mouse-x@
#define OP_SDL_GET_MOUSE_Y           (opcode_t) 0xC452AB2D                // sdl/mouse-y@
#define OP_SDL_BACKGROUND            (opcode_t) 0x4A51D2AA                // sdl/background
#define OP_SDL_OPEN_FONT             (opcode_t) 0x9D24F958                // sdl/open-font
#define OP_SDL_PUT_TEXT              (opcode_t) 0x25B908D5                // sdl/put-text
#define OP_SDL_GET_TEXT_SIZE         (opcode_t) 0x3B567CA7                // sdl/text-size@
#define OP_SDL_LOAD_IMAGE            (opcode_t) 0xA30EA3E2                // sdl/load-image
#define OP_SDL_PUT_IMAGE             (opcode_t) 0x3DFA782B                // sdl/put-image
#define OP_SDL_PLAY_SOUND            (opcode_t) 0x8EFAE1EA                // sdl/play-sound
#define OP_SDL_HALT_SOUND            (opcode_t) 0xB451120F                // sdl/halt-sound
#define OP_SDL_VOLUME                (opcode_t) 0xCCB3E567                // sdl/volume!
#define OP_SDL_LOAD_SOUND            (opcode_t) 0x3F337FC                 // sdl/load-sound
#define OP_SDL_GET_TICKS             (opcode_t) 0xA0C11FC                 // sdl/ticks@

// ext/threads.c
#define OP_THREAD__RUN               (opcode_t) 0xE47BB892                // thread/run
#define OP_THREAD__JOIN_SUBALL       (opcode_t) 0x9B920C1F                // thread/join-all
#define OP_THREAD__JOIN              (opcode_t) 0x37303F01                // thread/join
#define OP_THREAD__KILL              (opcode_t) 0x6B3D7E01                // thread/kill
#define OP_THREAD__LOCK              (opcode_t) 0x91795D9A                // thread/lock
#define OP_THREAD__UNLOCK            (opcode_t) 0xE4DECEBD                // thread/unlock

#endif /* __EXT_HASH_DEF */
