Winston Shine

Operating Systems
 
Reading 4

4/26/2024

1. When you print an address in C, is it possible to get the physical address?

no, just the address in the process's virtual address space.

2. What are some common errors related to malloc() and free()?

not including space for the null characters when allocating space for a string. not
using the sizeof operator to have compile-time size arguments passed to malloc.
not correctly casting the return type of malloc.

forgetting to allocate memory. not allocating enough memory. forgetting to initialize
memory after calling malloc(). Memory leaks (forgetting to free). freeing memory
too soon and then attempting to read it.attempting to free memory twice 
(calling free on an address that has already been freed). and invalid frees (passing 
it the wrong argument, something thats not an address).


3. What is a simple scheme to translate from virtual to physical addresses?

hardware based address-translation. os assigns virtual memory, hardware is able to
map virtual addresses to physical addresses.

in dynamic relocation this is: `physical address = virtual address + base`

4. What is a segment, and why how would it be more efficient that allocating a block for 

one piece of the address space. it's more efficient since when allocating a block there
could be a large amount of unused memory, cutting the address space into logical segments
allows the system to allocate address spaces in a way that is less wasteful.

5. What questions do you have about the reading? 

is fine-grained segmentation used often or is it more common to use a small number
of specific segments? ie: code segment, stack, heap.
I sort of understand how segmentation is more efficient but I don't think I quite get it
since it seems to still be assigning the same amount of total address space.
