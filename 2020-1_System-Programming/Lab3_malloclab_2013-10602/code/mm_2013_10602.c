/*
 * 2013-10602 Jiyoung Park
 *
 * This Lab assignment implemented heap structure, malloc, and free, especially focusing on the free list management.
 * This code is based on Segregated Free list, Bsed on the first-fit search.
 * This code is constructed in 4 parts.
 *
 * (a). Macros
 * (b). mm_functions, which includes init, malloc, free, and realloc.
 * (c). Actual Implementation of Free list management.
 * (d). Supplements for Heap Consistency checker, which is commented because it yields warnings that the program does not use the declared function.
 *
 * For (a) and (b), most of implementation was based on the textbook CSAPP, with some slight difference.
 * Therefore, I will omit comments for (a).
 * 
 * For (b), Since there was a restriction that we cannot declare an type of struct or array, I used segregated free list method, 
 * which is easy to use only with pointer.
 * Below explanation is how I designed the task.
 * For mm_init:
 * I declared only one global pointer variable, which points the heap, and assigned segregated list in the prologue part of the heap, as suggested in ETL QnA.
 * Note that assigning in prologue is better than middle or epilogue since those part varies a lot by freeing and extending, while seglist is relatively stable.
 * Therefore, Heap is consisted with padding, and then seg_list roots in prologue, then regular blocks in middle, and at last epilogue.
 * All blocks have header and footer, which store allocation bit that tells whether the block is allocated, and size of the block.
 * Allocated blocks additionally have payload inside, and free blocks pointers to next block and previous block, besides header and footer.
 * 
 * For mm_malloc, mm_free, and mm_realloc, while there are some things to consider, overall flow is similar with textbook and does not vary much by designing scheme.
 * Accordingly, I will omit the explanation for this part in this code, and will explain in the report.
 *
 * Part (c) is where core design schemes are declared. 
 * In fact, part (c) can be divided into 3 parts again. 
 * For (c)-1, I declared extend_heap(), place(), find_fit(), and coalesce(), which serves core architectures. 
 *	When malloc or realloc is called, it will first find the space available by find_fit(). find_fit() is implemented by first_fit,
 *	meaning it will greedly find the space, without considering optimal allocation. I choose this implementation because it is easy.
 *	If the space is not sufficient, extend_heap() will extend the total amount of the heap.
 *	After finding the proper space, place() allocate the memory in the heap. If we have sufficient free space, place will split the space and keep remaining freed.
 *  And coalesce will manage the free blocks, by integrating free blocks if possibble.
 *	
 * For (c)-2, delete_from_seglist() and insert_to_seglist both serves management for seglist. 
 *	Seglist is composed by n classes (16 for this code), and they are classified by their size. 
 *	delete_from_seglist() and insert_to_seglist() enables to traverse the seglist. They are basically same with common linked list except for classes.
 * 
 * For (d), heap consistency check is done by mm_check, which calls several functions to check each of the error.
 * Errors that mm_check detect includes 
 *		* out of heap error, 
 *		* free but not in seglist error,
 *		* in seglist but not free error, 
 *		* free blocks not coalesced error, 
 *		* and blocks that have different information in head and footer error.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/

// single word (4) or double word (8) alignment 
#define ALIGNMENT 8

// rounds up to the nearest multiple of ALIGNMENT
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

// basic macro -> from textbook
#define WSIZE           4               // Single word
#define DSIZE           8               // Double word
#define CHUNKSIZE       (1<<12)         // Extend heap by this size (emprically optimized)
#define MIN_BLOCK_SIZE  16              // Minimum block size (header + footer + next + prev)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))


#define PACK(size, alloc)   ((size) | (alloc))

// Read and write for addr p
#define GET(p)              (*(unsigned int *)(p))
#define PUT(p, val)         (*(unsigned int *)(p) = (val))

// Read the size and verify allocation for address p
#define GET_SIZE(p)         (GET(p) & ~0x7) 
#define GET_ALLOC(p)        (GET(p) & 0x1)

// compute header / footer addr
#define HDRP(bp)        ((char *)(bp) - WSIZE)
#define FTRP(bp)        ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// compute addr for adjacent blocks in heap
#define NEXT_BLKP(bp)       ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)       ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

////////////////////Above Macros are from textbook//////////////////////////

// addr: next and previous free blocks from segregated freelist
//Type Casting is Important!!
#define NEXT_FP(bp)      ((int *)((char *)(bp)))
#define PREV_FP(bp)      ((int *)((char *)(bp) + WSIZE))

// Segregated list MACRO
//num of SEGLIST CLass
#define NUM_SEGLIST_CLASS  16
// obtain seglist root for each class
#define GET_SEGLIST_PTR(class) (heap_listp + (class * 2 * DSIZE))
//#define SET_SEGLIST_PTR(class, ptr) ((*GET_SEGLIST_PTR(class)) = ptr)

// Extra Macro
#define EVENIZE(size) (size % 2) ? ((size + 1) * WSIZE) : ((size) * WSIZE)
#define PUT_ADDR(p, val)    (*(int *)(p) = (int)(long)(val))        // write address

// Global functions
// Essential functions for heap management
static void *extend_heap(size_t size);
static void place(void *ptr, size_t size);
static void *find_fit(size_t size);
static void *coalesce(void *ptr);

// Segregated list management
static void delete_from_seglist(void *ptr);
static void insert_to_seglist(void *ptr);

// Utils (optional)
static int get_class(size_t size);
static void *nbd_free_block(void *ptr, int indicator);
static int most_significant_bit(int size);

// Heap Consistency debugging
/*
static int mm_check(void);
static int check_heap_addr();
static int all_free_blocks_are_in_seglist();
static int all_seglist_elements_are_free();
static int all_blocks_are_valid();
static int all_coalesced();
static int valid_block(char *ptr);
*/
// global variable
// heap head pointer
char *heap_listp;


/*
 * mm_init - Initialize the memory manager
 * implemented by segregated list
 */

// almost identical with textbook except initializing heap
int mm_init(void)
{
    // initial heap -> large enough to contain seglist
    if((heap_listp = mem_sbrk(DSIZE + (NUM_SEGLIST_CLASS * DSIZE * 2))) == (void *)-1) {
        return -1;
	}
	//alignment padding
    PUT(heap_listp, 0);

	// padding
    heap_listp += DSIZE;

    // at the beginning of the heap - > seglist: According to ETL QnA 
	// Loop the seglist and init by NULL
    for(int class = 0; class < NUM_SEGLIST_CLASS; class++) {
        // root of the each seglist
		char *root_seg = GET_SEGLIST_PTR(class);
		PUT(root_seg - WSIZE, PACK(MIN_BLOCK_SIZE, 1));        
		PUT_ADDR(root_seg, NULL);                           

        //SET_SEGLIST_PTR(class, NULL);
		PUT(root_seg + DSIZE, PACK(MIN_BLOCK_SIZE, 1));
    }

    PUT(heap_listp + (2 * NUM_SEGLIST_CLASS * DSIZE) + WSIZE, PACK(0, 1));            /* Epilogue header */

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if(extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;

    return 0;
}

//Malloc
//Code is almost identical with textbook, so omit the explanation
void *mm_malloc(size_t size)
{
	//mm_check();
    size_t asize;       
    size_t extend_size;
    char *ptr;

    // ignore supurious 
    if(size == 0)
        return NULL;

    //Adjust block size -> large enough
    asize = MAX(ALIGN(size + SIZE_T_SIZE), MIN_BLOCK_SIZE);

    // search for the space
    if((ptr = find_fit(asize)) != NULL) {
        //allocate
		place(ptr, asize);      
        return ptr;
    } // found

	// not found
	// expand heap
    extend_size = MAX(asize, CHUNKSIZE);         // select and extend the larger size between asize and CHUNKSIZE
    if((ptr = extend_heap(extend_size / WSIZE)) == (void *)-1) {
        return NULL;
	}

	// allocate in expanded area
    place(ptr, asize);
    return ptr;
}

// free
// need to coalesce if free occur
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *new_ptr = ptr;
    size_t new_size;
    size_t old_size;

    /* If reallc(ptr, 0), free(ptr) and return NULL */
    if(size == 0) {
        mm_free(ptr);
        return NULL;
    }
    /* If realloc(NULL, size), same with malloc(size) */
    if(ptr == NULL) {
        return mm_malloc(size);
    }

    old_size = GET_SIZE(HDRP(ptr));
    new_size = MAX(ALIGN(size + SIZE_T_SIZE), MIN_BLOCK_SIZE);

	// new < old
    if(new_size <= old_size) {    // just place it
        place(ptr, new_size);
        return ptr;
    }

	// new > old
    else {                     

        // Can use next block?
        if(!GET_ALLOC(HDRP(NEXT_BLKP(ptr)))) {
            
			// merge
            size_t extend_size = GET_SIZE(HDRP(NEXT_BLKP(ptr))) + old_size;

			// merge possible?
            if(extend_size > new_size) {
				//fill that place
                delete_from_seglist(NEXT_BLKP(ptr));
                PUT(HDRP(ptr), PACK(extend_size, 1));
                PUT(FTRP(ptr), PACK(extend_size, 1));
                place(ptr, extend_size);
                return ptr;
            }
        }
    }
	// if not possible to use adjacent blocks
    new_ptr = mm_malloc(size);
    if (new_ptr == NULL)
      return NULL;

    memcpy(new_ptr, ptr, MIN(size, old_size));
    mm_free(ptr);
    return new_ptr;
}

static void *extend_heap(size_t size)
{
    char *ptr;

    /* Allocate an even number of words to maintain alignment */
	size_t asize = EVENIZE(size);
	if((ptr = mem_sbrk(asize)) == (void *) -1)
        return NULL;

    // Initialize
	// Free header
    PUT(HDRP(ptr), PACK(asize, 0));          
    // Free footer
	PUT(FTRP(ptr), PACK(asize, 0));          
    // Epilog header
	PUT(HDRP(NEXT_BLKP(ptr)), PACK(0, 1));  

    // coalesce since it might overrlap with prev ones.
    return coalesce(ptr);
}

// integrating scattered free blocks if available
static void *coalesce(void *ptr)
{
	// check prev block alloc
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(ptr)));         
    // check next block alloc
	size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));         
    // current block size
	size_t size = GET_SIZE(HDRP(ptr));

	// 1. full ____ full -> Just inserting
    if(prev_alloc && next_alloc) {            
		insert_to_seglist(ptr);
        return ptr;
    }

	// 2. full ____ ____ -> combine cur + next
    else if(prev_alloc && !next_alloc) {       
		// total size = current + next
		size += GET_SIZE(HDRP(NEXT_BLKP(ptr)));
		
		// next is not indep element anymore
        delete_from_seglist(NEXT_BLKP(ptr));       
        
		// cur's next & next's prev
		PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
        
		// current ptr is now integrated
		insert_to_seglist(ptr);                   
    }

	// 3. ____ ____ full -> combine prev + cur
    else if(!prev_alloc && next_alloc) { 
		// total size = cur + prev
        size += GET_SIZE(HDRP(PREV_BLKP(ptr)));

		// prev is not independent element anymore
        delete_from_seglist(PREV_BLKP(ptr));       
        
		// cur's prev & prev's next
		PUT(FTRP(ptr), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        
		// cur is now part of prev
		insert_to_seglist(PREV_BLKP(ptr));   
        // prev now contains cur and cur is not exist anymore
		ptr = PREV_BLKP(ptr);
    }

	// 4. ___ ___ ___ -> integrate all together
    else {  
		// size sum
        size += (GET_SIZE(HDRP(PREV_BLKP(ptr))) + GET_SIZE(FTRP(NEXT_BLKP(ptr))));
        
		// deleteting 
		delete_from_seglist(PREV_BLKP(ptr));
        delete_from_seglist(NEXT_BLKP(ptr));
        
		// integrating
		PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(ptr)), PACK(size, 0));
        
		// into one and insert again
		insert_to_seglist(PREV_BLKP(ptr));
        ptr = PREV_BLKP(ptr);
    }

    return ptr;
}

// First-fit based finding free block
static void *find_fit(size_t size)
{
    void *ptr;
    int seg_class = get_class(size);
	// From minimal size that can hold this ptr -> iterate seglist
    for(int class = seg_class; class < NUM_SEGLIST_CLASS; class++) {
		void *root = GET_SEGLIST_PTR(class);

        // for each seglist, find available space
        for(ptr = nbd_free_block(root, 1) ; ptr != NULL ; ptr = nbd_free_block(ptr, 1)) {
            if(size <= GET_SIZE(HDRP(ptr))) {
                return ptr;
            }
        }
    }
	// Not able to fit
    return NULL;
}

// actual allocation
static void place(void* ptr, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(ptr));

	// if the space is large to hold both allocated and free -> split the current block and save the rest
    if((csize - asize) >= (2*DSIZE)) {
		// if malloc -> delete free block ( not needed in realloc)
        if(GET_ALLOC(HDRP(ptr)) == 0) {
            delete_from_seglist(ptr);
        }
        PUT(HDRP(ptr), PACK(asize, 1));
        PUT(FTRP(ptr), PACK(asize, 1));

        /* split the block */
        ptr = NEXT_BLKP(ptr);
        PUT(HDRP(ptr), PACK(csize-asize, 0));
        PUT(FTRP(ptr), PACK(csize-asize, 0));
		// new free block -> append
        insert_to_seglist(ptr);
    }
    else { // use the whole block
        if(GET_ALLOC(HDRP(ptr)) == 0) {
            delete_from_seglist(ptr);
        }

        PUT(HDRP(ptr), PACK(csize, 1));
        PUT(FTRP(ptr), PACK(csize, 1));
    }
}

// list segregate by 2^n, as suggested in lecture note
// using msb calculation
int get_class(size_t size) {
	if(size == 0) {
		return 0;
	}
			
	int msb = most_significant_bit(size);
				
	if(msb >=  NUM_SEGLIST_CLASS) {
		return (NUM_SEGLIST_CLASS - 1);
	}
					
	return (most_significant_bit(size) - 1);
}

// Calculating most significant bit
// From geeksforgeeks.com
int most_significant_bit(int size){
	int mask = (1 << 31);
	for(int bit_index = 31; bit_index >= 0; bit_index--) {
		if((size & mask) != 0){
			return bit_index;
		}
		mask = (mask >> 1);
	}
	return -1;
}

// insertion
static void insert_to_seglist(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));
	int seg_class = get_class(size);
	
	// current segclass
	void *root_seg = GET_SEGLIST_PTR(seg_class);
    void *next_ptr = nbd_free_block(root_seg, 1);
	void *prev_ptr = root_seg;

    // loop inside seglist
	while(next_ptr != NULL && GET_SIZE(HDRP(next_ptr)) < size) {
        prev_ptr = next_ptr;
		next_ptr = (char *) nbd_free_block(next_ptr, 1);
    }
	// if hit
	// insert!
    PUT_ADDR(NEXT_FP(ptr), next_ptr);
    PUT_ADDR(PREV_FP(ptr), prev_ptr);
    PUT_ADDR(NEXT_FP(prev_ptr), ptr);

	// connect if not NULL
    if (next_ptr != NULL) {
        PUT_ADDR(PREV_FP(next_ptr), ptr);
    }
}

/*
 * delete the free block from the seglist
 */
static void delete_from_seglist(void *ptr)
{
	// disconnect current ptr
	void *next_ptr = (void *)nbd_free_block(ptr, 1);
    void *prev_ptr = (void *) nbd_free_block(ptr, 0);
	PUT_ADDR(NEXT_FP(prev_ptr), next_ptr);

	// connect prev and next if both exist
    if(next_ptr != NULL) {
        PUT_ADDR(PREV_FP(next_ptr), prev_ptr);
    }
}

// Indicator == 1 -> next
// Indicator == 0 -> prev
// find neighboring free blocks
static void *nbd_free_block(void *ptr, int indicator) {
	int offset;
	if (indicator == 0) {
		offset = *PREV_FP(ptr);
	}
	else {
		offset = *NEXT_FP(ptr);
	}

	if(offset) {
		return (void *)(offset | 0x80000000);
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////
////////////////// Heap Consistency Checker///////////////////////
//////////////////////////////////////////////////////////////////

/*
static int mm_check() {
	printf("\nActivate mm checker\n");
	
	// result = 0 if well functioned, -1 if mal functioned.
	int result = 0;

	result = check_heap_addr();
	result += all_free_blocks_are_in_seglist();
	result += all_seglist_elements_are_free();
	result += all_blocks_are_valid();
	result += all_coalesced();

	printf("\nCheck Completed\n");
	
	// exist at least one error
	// sum of result == num of problems
	if(result != 0) {
		printf("ERROR: There are %d problems\n", result);
		return -1;
	}
	return 0;
}

// Checking whether all dynamic memeories are in heap addr
static int check_heap_addr() {
	int result = 0;
	void *heap_lo = mem_heap_lo();
	void *heap_hi = mem_heap_hi();

	char *temp_ptr;

	// loop heap
	for(temp_ptr = heap_lo ; GET_SIZE(HDRP(temp_ptr)) > 0; temp_ptr = NEXT_BLKP(temp_ptr)) {
		
		// properly in heap
		if(((int)(heap_lo) <= (int)(temp_ptr)) && ((int)(temp_ptr) <= (int)(heap_hi))) {
			continue;
		}

		// out of heap
		else {
			printf("ERROR : %x is not in range %x ~ %x\n", temp_ptr, heap_lo, heap_hi);
			result = 1;
		}
	}

	return result;
}

// all free blocks are really in seglist?
static int all_free_blocks_are_in_seglist() {
	int result = 0;
	//record whether the ptr is in free_list
	int found_in_freelist = 0;
	void *heap_lo = mem_heap_lo();
	void *heap_hi = mem_heap_hi();

	char *temp_ptr;
	// loop all heap
	for(temp_ptr = heap_lo ; GET_SIZE(HDRP(temp_ptr)) > 0 ; temp_ptr = NEXT_BLKP(temp_ptr)) {
		// check whether it is free block
		if(GET_ALLOC(HDRP(temp_ptr))) {
			continue;
		}
		//reset -> each time check whethere this ptr was found in the list
		found_in_freelist = 0;
		// if it is free, find where it should be in
		int size = GET_SIZE(HDRP(temp_ptr));
		int seg_class = get_class(size);

		void *root_seg = GET_SEGLIST_PTR(seg_class);
		
		if(root_seg == temp_ptr) {
			//it is in the list
			found_in_freelist = 1;
			continue;
		}

		// if not root, search whether it is in this class
		void *next_ptr = nbd_free_block(root_seg, 1);
		void *prev_ptr = root_seg;

		// loop seglist
		while(next_ptr != NULL && GET_SIZE(HDRP(next_ptr)) < size) {
			//found in fre_list
			if(next_ptr == temp_ptr) {
				found_in_freelist = 1;
				break;
			}
			next_ptr = (char *) nbd_free_block(next_ptr, 1);
		}
		// not in seglist -> invalid
		if(found_in_freelist == 0) {
			printf("ERROR: NON-FREE-EXIST\n");
			result = 1;
		}
	}
	//result is -1 if at least 1 non-listed free exist
	return result;
}

// all element in seglist is free?
static int all_seglist_elements_are_free() {
	int result = 0;
	// all seglist
	for(int class = 0 ; class < NUM_SEGLIST_CLASS ; class++) {
		//loop each seglist -> same as insertion
		void *root_seg = GET_SEGLIST_PTR(class);
		void *next_ptr = nbd_free_block(root_seg, 1);
		void *prev_ptr = root_seg;
		do {
			// ERROR
			if(GET_ALLOC(prev_ptr) == 1) {
				printf("ERROR : Non-Free element %x in free list\n", prev_ptr);
				result = 1;
			}
			prev_ptr = next_ptr;
			next_ptr = (char *) nbd_free_block(next_ptr, 1);
		} while(next_ptr != NULL && GET_SIZE(HDRP(next_ptr)) > 0);
	}
	return result;
}

//check all blocks are validly saving information
static int all_blocks_are_valid() {
		
	void *heap_lo = mem_heap_lo();
	void *heap_hi = mem_heap_hi();
	char *temp_ptr;

	int result = 0;

	// loop heap
	for(temp_ptr = heap_lo ; GET_SIZE(HDRP(temp_ptr)) > 0 ; temp_ptr = NEXT_BLKP(temp_ptr)) {
		// check individual node
		result = valid_block(temp_ptr);
	}

	return result;
}

static int all_coalesced() {
	int result = 0;

	void *heap_hi = mem_heap_hi();
	void *heap_lo = mem_heap_lo();

	char *temp_ptr;

	// loop heap
	for(temp_ptr = heap_lo; GET_SIZE(HDRP(temp_ptr)) > 0 ; temp_ptr = NEXT_BLKP(temp_ptr)) {
		if((GET_ALLOC((HDRP(temp_ptr))) == 0) && (GET_ALLOC((HDRP(NEXT_BLKP(temp_ptr)))))) {
			printf("ERROR: %x and %x are not coalesced\n", temp_ptr, NEXT_BLKP(temp_ptr));
			result = 1;
		}
	}
	return result;
}

//checking each block is valid
// i.e. pointer in footer and header conicide
//return -1 if error
static int valid_block(char *ptr) {
	int result = 0;
	int alloc_in_hd = GET_ALLOC(HDRP(ptr));
	int alloc_in_ft = GET_ALLOC(FTRP(ptr));

	if (alloc_in_hd != alloc_in_ft) {
		printf("ERROR : alloc: %d != %d \n", alloc_in_hd, alloc_in_ft);
		result = 1;
	}
	return result;
}
*/
