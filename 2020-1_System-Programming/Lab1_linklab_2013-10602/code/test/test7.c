#include <stdlib.h>

int main(void)
{
  void *a;
  void *b;
  void *c;

  a = malloc(1024);
  a = realloc(a, 1024);
  a = realloc(a, 1025);
  a = realloc(a, 1026);
  b = realloc(a, 100);

  return 0;
}
