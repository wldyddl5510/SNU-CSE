#include <stdlib.h>

int main(){

  void* p = malloc(100);

  free(p);

  p = realloc(p, 10);

  p = realloc(p, 50);

  return 0;

}
