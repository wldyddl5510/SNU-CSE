#include <stdlib.h>


int main(void)
{
  void *p1;
  void *p2;

  p1 = malloc(1);
  p2 = realloc(p1, 1000000);
  //free(p1);

  return 0;
}
