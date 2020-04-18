/**
 * malloc accepts a size request without checking its plausability; free
 * believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pains with error checking.
 */

#include <unistd.h>

#define NULL 0
#define MAX_UNITS 10240

typedef long Align;         // For alignment to long boundary

typedef union header {      // Block header
    struct {
        union header *next;  // Next block if on free list
        unsigned size;      // Size of this block
    } data;
    Align x;                // Force alignment of blocks
} Header;

void free(void *block);

static Header base;                 // Empty list to get started
static Header *free_start = NULL;   // Start of free list
static unsigned free_units = 0;     // Total free units in the current pool
static unsigned used_units = 0;     // Total occupied units from the pool
static unsigned max_alloc = 0;      // Largest object allocated

// General-purpose storage allocator
void *malloc(unsigned nbytes) {
    Header *current, *prev;
    Header *morecore(unsigned nunits);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((long) nunits - free_units + used_units > MAX_UNITS) {
        // Maximum memory exceeded
        return NULL;
    }

    if ((prev = free_start) == NULL) {  // No free list yet
        base.data.next = free_start = prev = &base;
        base.data.size = 0;
    }

    for (current = prev->data.next; ; prev = current, current = current->data.next) {
        if (current->data.size >= nunits) {         // Big enough
            if (current->data.size == nunits) {     // Exactly the right size
                prev->data.next = current->data.next;
            } else {
                current->data.size -= nunits;
                current += current->data.size;
                current->data.size = nunits;
            }

            free_start = prev;
            free_units -= nunits;
            used_units += nunits;
            return (void *) (current + 1);
        }

        if (current == free_start) {    // Wrapped around the free list
            if ((current = morecore(nunits)) == NULL) {
                return NULL;    // None left
            }
        }
    }
}

#define NALLOC 1024     // Minimum units to request

// Ask system for more memory
static Header *morecore(unsigned nunits) {
    char *null_check_ptr;
    Header *header_ptr;

    if (nunits < NALLOC) {
        nunits = NALLOC;
    }

    null_check_ptr = sbrk(nunits * sizeof(Header));
    if (null_check_ptr == (char *) -1) {   // No space at all
        return NULL;
    }
    max_alloc = (nunits > max_alloc) ? nunits : max_alloc;

    header_ptr = (Header *) null_check_ptr;
    header_ptr->data.size = nunits;
    free((void *) (header_ptr + 1));    // Add the block to the program pool
    free_units += nunits;
    return free_start;
}

void free(void *block) {
    Header *block_header, *current;
    unsigned original_size;

    block_header = (Header *) block - 1;
    if ((original_size = block_header->data.size) > max_alloc || original_size == 0 ) {
        // Asked to free more memory than the largest allocd object, or nothing
        return NULL;
    }

    for (
        current = free_start;
        !(block_header > current && block_header < current->data.next);
        current = current->data.next
    ) {
        if (
            current >= current->data.next
            && (block_header > current || block_header < current->data.next)
        ) {
            break;  // Freed block should go at start or end of free list
        }
    }

    if (block_header + block_header->data.size == current->data.next) {
        // Join to the start of current->data.next
        block_header->data.size += current->data.next->data.size;
        block_header->data.next = current->data.next->data.next;
    } else {
        block_header->data.next = current->data.next; 
    }

    if (current + current->data.size == block_header) {
        // Join to the end of current
        current->data.size += block_header->data.size;
        current->data.next = block_header->data.next;
    } else {
        current->data.next = block_header;
    }

    free_start = current;
    used_units -= original_size;
    free_units += original_size;
}