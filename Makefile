SRC=src/main.c src/colorforth.c \
	src/cf-stdio.c \
	ext/os.c \
	ext/dict.c \
	ext/io.c \
	ext/color.c

SRC_H=src/colorforth.h \
	conf.h \
	src/lib.cf.h \
	src/cf-stdio.h \
	ext/color.h

unix: Makefile build/Makefile $(SRC) $(SRC_H)
	make -f build/Makefile

dos:
	make -f build/Makefile.dos patch4dos
	make -f build/Makefile.dos

conf.h: src/conf.tmpl.h
	make -f build/Makefile conf.h

clean:
	rm -f colorforth

mrproper: clean
	rm -f conf.h
