all: kernel-i386.bin

start32.o: start32.asm
	fasm start32.asm

kernel.o: kernel.c
	tcc -m32 -c kernel.c

kernel-i386.elf: start32.o kernel.o
	tcc -m32 -nostdlib -Wl,-Ttext,0x100000 start32.o kernel.o -o kernel-i386.elf

kernel-i386.bin: start32.o kernel.o
	tcc -m32 -nostdlib -Wl,-Ttext,0x100000 -Wl,--oformat,binary -static start32.o kernel.o -o kernel-i386.bin

run: kernel-i386.elf
	qemu-system-i386 -kernel kernel-i386.elf

clean:
	rm -f *.o *.bin *.elf
