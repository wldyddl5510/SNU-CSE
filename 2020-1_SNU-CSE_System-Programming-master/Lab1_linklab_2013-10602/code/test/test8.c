#include <stdlib.h>

int main(void)
{
  void *a;
  void *b;
  a = calloc(1,3);
  b = realloc(a, 0);

  return 0;
}
