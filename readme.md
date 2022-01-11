[Example](https://pbrochard.github.io/colorforth-pbr/wasm/colorforth.html)

![](doc/screenshot.png?raw=true)
![](doc/screenshot-colorize.png?raw=true)

### Minimal version
![](doc/screenshot-minimal.png?raw=true)

### 2 + 2 = 5 joke
[![asciicast](https://asciinema.org/a/442906.svg)](https://asciinema.org/a/442906)

###On Linux Ubuntu, the makefile.unix file not working with gnu make, and I compilated using these:

apt-get install libgmp3-dev
 
cp conf.tmpl.h conf.h
  
gcc -fPIE -std=gnu99 -O3 -Wall -Werror -Wextra -pedantic -s -Wno-missing-bra
Wno-missing-field-initializers -Wno-unused-parameter -I. -Isrc -Iext -o colorforth src/main.c src/colorforth.c src/
dio.c src/color.c src/lib.c ext/os.c ext/dict.c ext/io.c ext/parser.c ext/time.c ext/math.c ext/ext-math.c ext/mp-m
 ext/threads.c -lgmp -lpthread
 
