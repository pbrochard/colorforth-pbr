// The author disclaims copyright to this source code.

#ifdef __SDL

/**********************************************************************************
 *   HASH DEF
 *********************************************************************************/
#ifdef __SECTION_HASH_DEF

#define OP_SDL_INIT                (opcode_t) 0x92FE07C0           // sdl/init
#define OP_SDL_CLOSE               (opcode_t) 0xFAD1E96            // sdl/close
#define OP_SDL_DELAY               (opcode_t) 0xD811784D           // sdl/delay
#define OP_SDL_SHOW_CURSOR         (opcode_t) 0x6BD0F784           // sdl/show-cursor
#define OP_SDL_HIDE_CURSOR         (opcode_t) 0xB3052F5F           // sdl/hide-cursor
#define OP_SDL_POLL_EVENT          (opcode_t) 0x42D5F536           // sdl/poll-event
#define OP_SDL_PRESENT             (opcode_t) 0x1B628525           // sdl/present
#define OP_SDL_KEY_PRESS           (opcode_t) 0x4224F69A           // sdl/key?
#define OP_SDL_MOUSE_BUTTON        (opcode_t) 0x6755EA17           // sdl/button?
#define OP_SDL_GET_MOUSE_X         (opcode_t) 0x9E5030C4           // sdl/mouse-x@
#define OP_SDL_GET_MOUSE_Y         (opcode_t) 0xC452AB2D           // sdl/mouse-y@
#define OP_SDL_BACKGROUND          (opcode_t) 0x4A51D2AA           // sdl/background

#define OP_SDL_LOAD_IMAGE          (opcode_t) 0xA30EA3E2           // sdl/load-image
#define OP_SDL_PUT_IMAGE           (opcode_t) 0x3DFA782B           // sdl/put-image

#define OP_SDL_OPEN_FONT           (opcode_t) 0x9D24F958           // sdl/open-font
#define OP_SDL_PUT_TEXT            (opcode_t) 0x25B908D5           // sdl/put-text
#define OP_SDL_GET_TEXT_SIZE       (opcode_t) 0x3B567CA7           // sdl/text-size@

#define OP_SDL_PLAY_SOUND          (opcode_t) 0x8EFAE1EA           // sdl/play-sound
#define OP_SDL_HALT_SOUND          (opcode_t) 0xB451120F           // sdl/halt-sound
#define OP_SDL_VOLUME              (opcode_t) 0xCCB3E567           // sdl/volume!
#define OP_SDL_LOAD_SOUND          (opcode_t) 0x3F337FC            // sdl/load-sound

#define OP_SDL_GET_TICKS           (opcode_t) 0xA0C11FC            // sdl/ticks@

#endif /* __SECTION_HASH_DEF */


/**********************************************************************************
 *   WORD DEF
 *********************************************************************************/
#ifdef __SECTION_WORD_DEF

define_primitive(s, ENTRY_NAME("sdl/init"), OP_SDL_INIT);
define_primitive(s, ENTRY_NAME("sdl/close"), OP_SDL_CLOSE);
define_primitive(s, ENTRY_NAME("sdl/delay"), OP_SDL_DELAY);
define_primitive(s, ENTRY_NAME("sdl/show-cursor"), OP_SDL_SHOW_CURSOR);
define_primitive(s, ENTRY_NAME("sdl/hide-cursor"), OP_SDL_HIDE_CURSOR);
define_primitive(s, ENTRY_NAME("sdl/poll-event"), OP_SDL_POLL_EVENT);
define_primitive(s, ENTRY_NAME("sdl/present"), OP_SDL_PRESENT);
define_primitive(s, ENTRY_NAME("sdl/key?"), OP_SDL_KEY_PRESS);
define_primitive(s, ENTRY_NAME("sdl/button?"), OP_SDL_MOUSE_BUTTON);
define_primitive(s, ENTRY_NAME("sdl/mouse-x@"), OP_SDL_GET_MOUSE_X);
define_primitive(s, ENTRY_NAME("sdl/mouse-y@"), OP_SDL_GET_MOUSE_Y);
define_primitive(s, ENTRY_NAME("sdl/background"), OP_SDL_BACKGROUND);

define_primitive(s, ENTRY_NAME("sdl/load-image"), OP_SDL_LOAD_IMAGE);
define_primitive(s, ENTRY_NAME("sdl/put-image"), OP_SDL_PUT_IMAGE);

define_primitive(s, ENTRY_NAME("sdl/open-font"), OP_SDL_OPEN_FONT);
define_primitive(s, ENTRY_NAME("sdl/put-text"), OP_SDL_PUT_TEXT);
define_primitive(s, ENTRY_NAME("sdl/text-size@"), OP_SDL_GET_TEXT_SIZE);

define_primitive(s, ENTRY_NAME("sdl/play-sound"), OP_SDL_PLAY_SOUND);
define_primitive(s, ENTRY_NAME("sdl/halt-sound"), OP_SDL_HALT_SOUND);
define_primitive(s, ENTRY_NAME("sdl/volume!"), OP_SDL_VOLUME);
define_primitive(s, ENTRY_NAME("sdl/load-sound"), OP_SDL_LOAD_SOUND);

define_primitive(s, ENTRY_NAME("sdl/ticks@"), OP_SDL_GET_TICKS);

#endif /* __SECTION_WORD_DEF */


/**********************************************************************************
 *   SWITCH DEF
 *********************************************************************************/
#ifdef __SECTION_SWITCH

case OP_SDL_INIT: {
  POP3();
  int width = p3;
  int height = p2;
  int fullscreen = p1;

  Uint32 videoflags = 0;
  int i;

  char *title = "My SDL Windows";

  if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL Image: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(IMG_Quit);

  if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);

  if ( TTF_Init() < 0 ) {
    fprintf(stderr, "Couldn't initialize TTF: %s\n", SDL_GetError());
    exit(2);
  }
  atexit(TTF_Quit);

  if (fullscreen == 1) {
    videoflags ^= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if ((main_screen = SDL_CreateWindow("Atlast SDL",
                     SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     width, height,
                     videoflags)) == NULL) {
    fprintf(stderr, "Couldn't set %dx%d video mode: %s\n", width, height, SDL_GetError());
    exit(2);
  }

  SDL_SetWindowTitle (main_screen, title);
  SDL_SetWindowInputFocus(main_screen);

  if ((main_renderer = SDL_CreateRenderer(main_screen, -1, 0)) == NULL) {
    fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
    exit(2);
  }

  /* Sound initialisation */
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    fprintf(stderr,
            "\nWarning: I could not initialize audio!\n"
            "The Simple DirectMedia error that occured was:\n"
            "%s\n\n", SDL_GetError());
  }

  /* if (Mix_OpenAudio(22050, AUDIO_S16, 2, 512) < 0) */
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
    fprintf(stderr,
            "\nWarning: I could not set up audio for 44100 Hz "
            "16-bit stereo.\n"
            "The Simple DirectMedia error that occured was:\n"
            "%s\n\n", SDL_GetError());
  }
  Mix_Volume(-1, 20 * MIX_MAX_VOLUME / 100);

  // allocate mixing channels
  Mix_AllocateChannels(100);

  for (i = 0; i < MAX_KEY; i++) {
    tab_keys[i] = 0;
  }

  for (i = 0; i < 3; i++) {
    tab_mouse_button[i] = 0;
  }

  break;
}

case OP_SDL_CLOSE: {
  SDL_DestroyRenderer(main_renderer);
  SDL_DestroyWindow(main_screen);

  if ( !(font == NULL)) {
    TTF_CloseFont(font);
    font = NULL;
  }

  Mix_CloseAudio();

  IMG_Quit();
  SDL_Quit();

  break;
}

case OP_SDL_DELAY: {
  POP1();
  SDL_Delay(p1);

  break;
}

case OP_SDL_SHOW_CURSOR: {
  SDL_ShowCursor (SDL_ENABLE);
  break;
}

case OP_SDL_HIDE_CURSOR: {
  SDL_ShowCursor (SDL_DISABLE);
  break;
}

case OP_SDL_POLL_EVENT: {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    analyze_event(&event);
  }

  SDL_GetMouseState (&sdl_mouse_x, &sdl_mouse_y);

  break;
}

case OP_SDL_PRESENT: {
  SDL_RenderPresent(main_renderer);
  break;
}


case OP_SDL_KEY_PRESS: {
  POP1();
  PUSH1(tab_keys[p1]);
  break;
}

case OP_SDL_MOUSE_BUTTON: {
  POP1();
  PUSH1(tab_mouse_button[p1 - 1]);
  break;
}

case OP_SDL_GET_MOUSE_X: {
  PUSH1(sdl_mouse_x);
  break;
}

case OP_SDL_GET_MOUSE_Y: {
  PUSH1(sdl_mouse_y);
  break;
}

case OP_SDL_BACKGROUND: {
  POP3();
  SDL_SetRenderDrawColor(main_renderer, (int)p3, (int)p2, (int)p1, 255);
  SDL_RenderClear(main_renderer);
  break;
}

// /*===========================================================
//  *   Image functions
//  ============================================================*/
case OP_SDL_LOAD_IMAGE: {
  POP1();
  char * filename = CFSTRING2C(p1);
  SDL_Surface * surf = NULL;

  printf ("In C - Opening: %s\n", filename);

  surf = IMG_Load (filename);
  if (surf == NULL) {
    fprintf(stderr, "Can't load image %s - %s\n", filename, SDL_GetError());
    PUSH1(-1);
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(main_renderer, surf);
  SDL_FreeSurface(surf);

  if (texture == NULL) {
    fprintf(stderr, "Can't load image %s - %s\n", filename, SDL_GetError());
    PUSH1(-1);
    return;
  }

  PUSH1((cell) texture);
  break;
}

case OP_SDL_PUT_IMAGE: {
  POP3();
  int x = p2, y = p1;
  SDL_Texture * texture = (SDL_Texture *) p3;
  SDL_Rect dstrect;
  int w, h;

  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  dstrect.x = x; dstrect.y = y;
  dstrect.w = w; dstrect.h = h;
  SDL_RenderCopy(main_renderer, texture, NULL, &dstrect);
  break;
}


// /*===========================================================
//  *   Text functions
//  ============================================================*/
case OP_SDL_OPEN_FONT: {
  POP2();
  char * filename = CFSTRING2C(p2);
  int ptsize = p1;

  if ( !(font == NULL)) {
    TTF_CloseFont(font);
  }

  font = TTF_OpenFont(filename, ptsize);
  if ( font == NULL ) {
    fprintf(stderr, "Couldn't load %d pt font from %s: %s\n",
        ptsize, filename, SDL_GetError());
    PUSH1(-1);
    return;
  }
  TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

  PUSH1(0);
  break;
}

case OP_SDL_PUT_TEXT: {
  POP4();
  char * string = CFSTRING2C(p4);
  int x = p3, y = p2;
  int forecol = p1;

  SDL_Color fg;
  /* SDL_Color bg; */
  SDL_Surface *text;
  SDL_Rect dstrect;
  SDL_Texture *texture;

  fg.r = (forecol >> 16) & 0xff;
  fg.g = (forecol >> 8) & 0xff;
  fg.b = forecol & 0xff;

  text = TTF_RenderUTF8_Solid(font, string, fg);

  if ( text != NULL ) {
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = text->w;
    dstrect.h = text->h;
    texture = SDL_CreateTextureFromSurface(main_renderer, text);
    SDL_RenderCopy(main_renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(text);
  }

  break;
}

case OP_SDL_GET_TEXT_SIZE: {
  POP1();
  char * string = CFSTRING2C(p1);

  SDL_Surface *text;
  SDL_Color fg;

  text = TTF_RenderUTF8_Solid(font, string, fg);

  if ( text != NULL ) {
    PUSH2(text->w, text->h);
    SDL_FreeSurface(text);
  } else {
    PUSH2(-1, -1);
  }
  break;
}

//,-----
//| Sound part
//`-----
case OP_SDL_PLAY_SOUND: {
  POP1();
  Mix_PlayChannel(-1, (Mix_Chunk *) p1, 0);
  break;
}

case OP_SDL_HALT_SOUND: {
  Mix_HaltChannel(-1);
  break;
 }

case OP_SDL_VOLUME: {
  POP1();
  Mix_Volume(-1, p1 * MIX_MAX_VOLUME / 100);
  break;
}

case OP_SDL_LOAD_SOUND: {
  POP1();
  char * filename = CFSTRING2C(p1);

  const Mix_Chunk * snd = Mix_LoadWAV(filename);
  if (snd == NULL) {
    fprintf(stderr,
        "\nError: I could not load the sound file:\n"
        "%s\n"
        "The Simple DirectMedia error that occured was:\n"
            "%s\n\n", filename, SDL_GetError());
    PUSH1(-1);
    return;
  }

  PUSH1((cell) snd);
  break;
}

case OP_SDL_GET_TICKS: {
  PUSH1(SDL_GetTicks ());
  break;
}


#endif /* __SECTION_SWITCH */


/**********************************************************************************
 *   FUNCTION DEF
 *********************************************************************************/
#ifdef __SECTION_FUNCTION

#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

///* Please, edit this for your project */
#define MAX_KEY 300

int sdl_mouse_x = 0;
int sdl_mouse_y = 0;

int tab_mouse_button[3];
int tab_keys[MAX_KEY];

SDL_Window * main_screen;
SDL_Renderer *main_renderer;
TTF_Font * font = NULL;


// /*===========================================================
//  *   Input functions
//  ============================================================*/
void set_tab_keys_from_keysym(int keysym, int value) {
  switch(keysym) {
    case SDLK_ESCAPE:        tab_keys[27] = value; break;
    case SDLK_UP:            tab_keys[28] = value; break;
    case SDLK_DOWN:          tab_keys[29] = value; break;
    case SDLK_LEFT:          tab_keys[30] = value; break;
    case SDLK_RIGHT:         tab_keys[31] = value; break;
    case SDLK_RETURN:        tab_keys[32] = value; break;
    case SDLK_SPACE:         tab_keys[33] = value; break;
    case SDLK_TAB:           tab_keys[34] = value; break;
    case SDLK_LCTRL:         tab_keys[35] = value; break;
    case SDLK_KP_DIVIDE:     tab_keys[36] = value; break;
    case SDLK_KP_MULTIPLY:   tab_keys[37] = value; break;
    case SDLK_KP_MINUS:      tab_keys[38] = value; break;
    case SDLK_KP_PLUS:       tab_keys[39] = value; break;
    case SDLK_KP_ENTER:      tab_keys[40] = value; break;
    case SDLK_KP_1:          tab_keys[41] = value; break;
    case SDLK_KP_2:          tab_keys[42] = value; break;
    case SDLK_KP_3:          tab_keys[43] = value; break;
    case SDLK_KP_4:          tab_keys[44] = value; break;
    case SDLK_KP_5:          tab_keys[45] = value; break;
    case SDLK_KP_6:          tab_keys[46] = value; break;
    case SDLK_KP_7:          tab_keys[47] = value; break;
    case SDLK_KP_8:          tab_keys[48] = value; break;
    case SDLK_KP_9:          tab_keys[49] = value; break;
    case SDLK_KP_0:          tab_keys[50] = value; break;
    case SDLK_KP_PERIOD:     tab_keys[51] = value; break;
  }
}

void analyze_event (SDL_Event * event) {
  switch( event->type ) {
    case SDL_QUIT : tab_keys[100] = 1; break;

    case SDL_MOUSEBUTTONDOWN :
      if (event->button.button == SDL_BUTTON_LEFT) tab_mouse_button[0] = 1;
      if (event->button.button == SDL_BUTTON_MIDDLE) tab_mouse_button[1] = 1;
      if (event->button.button == SDL_BUTTON_RIGHT) tab_mouse_button[2] = 1;
      break;

    case SDL_MOUSEBUTTONUP :
      if (event->button.button == SDL_BUTTON_LEFT) tab_mouse_button[0] = 0;
      if (event->button.button == SDL_BUTTON_MIDDLE) tab_mouse_button[1] = 0;
      if (event->button.button == SDL_BUTTON_RIGHT) tab_mouse_button[2] = 0;
      break;

    case SDL_KEYDOWN :
      printf ("In C- Key press: %s %d 0x%02X\n", SDL_GetKeyName(event->key.keysym.sym), event->key.keysym.sym, event->key.keysym.scancode);

      if (event->key.keysym.sym >= SDLK_a && event->key.keysym.sym <= SDLK_z) {
        tab_keys[event->key.keysym.sym - SDLK_a] = 1;
      } else {
        set_tab_keys_from_keysym(event->key.keysym.sym, 1);
      }
      break;

    case SDL_KEYUP :
      printf ("In C- Key release: %s %d 0x%02X\n", SDL_GetKeyName(event->key.keysym.sym), event->key.keysym.sym, event->key.keysym.scancode);
      if (event->key.keysym.sym >= SDLK_a && event->key.keysym.sym <= SDLK_z) {
        tab_keys[event->key.keysym.sym - SDLK_a] = 0;
      } else {
        set_tab_keys_from_keysym(event->key.keysym.sym, 0);
      }
      break;

    default:
      break;
  }
}

#endif /* __SECTION_FUNCTION */

#endif /* __SDL */
