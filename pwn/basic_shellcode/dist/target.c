#include <stdio.h>
#include <string.h>
#include <err.h>
#include <stdlib.h>

char buf[2048];
// 32 Bit SHellcode -Needed
int main()
{
  if (!fgets(buf, sizeof(buf), stdin))
    err(1, "Too long input");

  // a few info for debugging
  printf("> length: %d\n", (int)strlen(buf));
  for (int i = 0; i < strlen(buf); i += 1) {
    if (i % 16 == 0)
      printf("> %04X: ", i);
    printf("%02X ", (unsigned char)buf[i]);
    if (i % 16 == 15)
      printf("\n");
  }
  printf("\n");

  (*(void (*)()) buf)();
}
