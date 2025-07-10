#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

int
main(int argc, char *argv[])
{
  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)

  char *end = sbrk(PGSIZE*32);

  for (int p = 0; p < 32; p += 1) {
    char *pagestart = end + p * PGSIZE;
    
    char *s = "very very secret pw is:   ";
    if (*(pagestart + 8) == s[0]) {
      write(2, pagestart + 32, 8);
    }

  }

  exit(1);
}
