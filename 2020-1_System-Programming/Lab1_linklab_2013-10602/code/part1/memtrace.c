//------------------------------------------------------------------------------
//
// memtrace
//
// trace calls to the dynamic memory manager
//
#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memlog.h>
#include <memlist.h>
#include "callinfo.h"

//
// function pointers to stdlib's memory management functions
//
// This wil work as  function pointer
static void *(*mallocp)(size_t size) = NULL;
static void (*freep)(void *ptr) = NULL;
static void *(*callocp)(size_t nmemb, size_t size);
static void *(*reallocp)(void *ptr, size_t size);

//
// statistics & other global variables
//
// This will save statistics and will be used in logging
static unsigned long n_malloc  = 0;
static unsigned long n_calloc  = 0;
static unsigned long n_realloc = 0;
static unsigned long n_allocb  = 0;
static unsigned long n_freeb   = 0;

// This list manages total mem
static item *list = NULL;

// This ist stores freed mem
static item *freed_mem_list = NULL;

//
// init - this function is called once when the shared library is loaded
//

/*
   Initializer.
   Init mallocp, callocp, reallocp, freep
*/

__attribute__((constructor))
void init(void)
{
	char *error;
	LOG_START();

	// initialize a new list to keep track of all memory (de-)allocations
	// (not needed for part 1)
	list = new_list();

	freed_mem_list = new_list();

	// Initialize function pointers
	// Initialize here since we can handle error easily in init since error is defined in this block
	
	// malloc function pointer to original malloc
	mallocp = dlsym(RTLD_NEXT, "malloc");
	
	// check error
	if((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}
	
	// calloc function pointer to original calloc
	callocp = dlsym(RTLD_NEXT, "calloc");
	
	// check error
	if((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}

	// realloc function pointer to original realloc
	reallocp = dlsym(RTLD_NEXT, "realloc");

	// check error
	if((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}

	//free function pointer to original free
	
	freep = dlsym(RTLD_NEXT, "free");
	if((error = dlerror()) != NULL) {
		fputs(error, stderr);
		exit(1);
	}
}

//
// fini - this function is called once when the shared library is unloaded
//
/*
   This part manages logging.
   Alternate LOG_STATISTICS Part to log desired value, instead of 0
*/

int is_list_empty(item* list) {
	if((list -> next) == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

__attribute__((destructor))
void fini(void)
{
  // ...

	// Convert this part to properly log alloc_total and alloc_avg

	if(is_list_empty(list) && is_list_empty(freed_mem_list)) {
		LOG_STATISTICS(0L, 0L, 0L);
	}
	else {
		LOG_STATISTICS(n_allocb, (n_allocb / (n_malloc + n_calloc + n_realloc)), 0L);

	}
	//unsigned long n_total = n_malloc + n_calloc + n_realloc;
	//LOG_STATISTICS(n_allocb, n_allocb / n_total, 0L);
	LOG_STOP();

  // free list (not needed for part 1)
	free_list(list);

	// free freed_mem_list
	free_list(freed_mem_list);

}

// ...
/*
	Function pointer to malloc
*/
void *malloc(size_t size) {
	// receive original malloc pointer
	void *malloc_ptr = mallocp(size);

	// increase mem
	n_allocb += size;

	// increase number of malloc -> for avg
	n_malloc++;

	// add current information into mem list
	// use alloc in memlist.c
	alloc(list, malloc_ptr, size);

	// logging
	// use LOG_MALLOC in memlog.h
	LOG_MALLOC(size, malloc_ptr); 

	return malloc_ptr;
}

void *calloc(size_t nmemb, size_t size) {

	//load original calloc pointer
	void *calloc_ptr = callocp(nmemb, size);

	// count total mem for each block
	unsigned long block_mem_size = size * nmemb;

	//count mem
	n_allocb += block_mem_size;

	// increase num of calloc -> for avg
	n_calloc++;

	// add current information into mem list
	alloc(list, calloc_ptr, block_mem_size);

	// logging calloc info
	LOG_CALLOC(nmemb, size, calloc_ptr);

	return calloc_ptr;
}

void *realloc(void *ptr, size_t size) {

	// retrieve ptr_before
	//item *ptr_before_item = find(list, ptr);

	// check whether before is in current mem
	// if successfully retrieved

	void *realloc_ptr;

	if((find(list, ptr)) != NULL) {
		unsigned long size_before = find(list, ptr) -> size;
		n_freeb += size_before;
		// compare new size with old size
		//size_t before_minus_new = size_before - size;
		
		// rest of the size_before should be freed
		//if(size_before > size) 
		//	n_freeb += (size_before - size);

		// remove input_ptr
		dealloc(list, ptr);

		// insert freed one
		alloc(freed_mem_list, ptr, size_before);

		// insert new ptr
		// use realloc in original
		realloc_ptr = reallocp(ptr, size);
		
		// insert into current mem
		alloc(list, realloc_ptr, size);

		// logging
		LOG_REALLOC(ptr, size, realloc_ptr);
	}

	// if not exist
	else {
		// NULL realloc
		realloc_ptr = reallocp(NULL, size);

		// alloc new
		alloc(list, realloc_ptr, size);
		LOG_REALLOC(ptr, size, realloc_ptr);
		// check for nested free
		//if(find(freed_mem_list, ptr) != NULL) 
		//	LOG_DOUBLE_FREE();
		//else
		//	LOG_ILL_FREE();

		// logging
		//LOG_REALLOC(ptr, size, realloc_ptr);
	
	}

	// Note that do not adjust the n_allocb, just add when realloc
	n_allocb += size;
	n_realloc++;

	return realloc_ptr;
}

void free(void *ptr) {

	if(!ptr)
		return;

	unsigned long freeing_size = find(list, ptr) -> size;
	n_freeb += freeing_size;
	dealloc(list, ptr);

	alloc(freed_mem_list, ptr, freeing_size);

	LOG_FREE(ptr);
	freep(ptr);
}
