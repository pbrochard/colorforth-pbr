/*  Tutorial: A small kernel with Fasm & TCC
 *  By Tommy.
 */

/*
 * Main kernel function.
 */
void
kmain (void)
{
    *((unsigned char *) 0xB8000) = 'H';
    *((unsigned char *) 0xB8001) = 0x1F;
    *((unsigned char *) 0xB8002) = 'E';
    *((unsigned char *) 0xB8003) = 0x1F;
    *((unsigned char *) 0xB8004) = 'L';
    *((unsigned char *) 0xB8005) = 0x1F;
    *((unsigned char *) 0xB8006) = 'L';
    *((unsigned char *) 0xB8007) = 0x1F;
    *((unsigned char *) 0xB8008) = 'O';
    *((unsigned char *) 0xB8009) = 0x1F;

   // const char ch = 'A';
   //
   // __asm__ __volatile__ (
   //   "movb 0x0e, %%ah\n"
   //   "movb %[c], %%al\n"
   //   "int $0x10\n"
   //   :
   //   : [c] "r" (ch)
   //   : "ax"
   // ;
}
