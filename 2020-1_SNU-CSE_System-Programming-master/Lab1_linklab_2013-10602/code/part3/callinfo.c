#include <stdlib.h>
//MUST Define UNW_LOCAL_ONLY "Before" libunwind!!
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <string.h>

int get_callinfo(char *fname, size_t fnlen, unsigned long long *ofs)
{
  unw_context_t context;
  unw_cursor_t cursor;
  unw_word_t off;
  char proc_name[256];
  
  //error
  if(unw_getcontext(&context))
    return -1;

  //error
  if(unw_init_local(&cursor, &context))
    return -1;

  unw_step(&cursor);  // callinfo -> alloc
  unw_step(&cursor);  // alloc -> malloc
  unw_step(&cursor);  // malloc -> main
  unw_get_proc_name(&cursor, proc_name, 256, &off);
  
    
  *ofs = off - 5; //location in current function
  strncpy(fname, proc_name, fnlen); //copy name of current function
  return 0;
}

