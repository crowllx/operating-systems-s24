Winston Shine

Operating Systems

Reading 5

05/03/2024


1. Define internal and external fragmentation.
    external fragmentation is when free space is divided into small pieces of 
    variable sizes, making new requests to allocate space more difficult because 
    there needs to be a continguous space to allocate.

    internal fragmentation is when more memory then needed or requested is handed out,
    causing large portions of memory to go unused and wasted.

2. How does free() know the size of an allocated region?

    a header block used by malloc/free and stored in memory just before the region that was allocated.
    the header contains the size of the allocated region.

3. What is the free list?

    a list of free memory regions on the heap.
    when memeory is freed the header of that region is changed to store a pointer
    to the next block of memory (i think).
    this address is calculated by <address freed> + size of previous chunk + size of header (8 byte)

4. What is the TLB? What is a TLB miss?

    Translation-lookaside buffer
    a hardware cache of frequent virtual to physical address translations
    a tlb miss is when the cpu doesn't find the address in the translation table.

5. What questions do you have about the reading? 
    
    the reading mentions database management systems being able to make use of
    large page sizes for increased efficiency. How common are larger page tables actually used?
    It was discussed briefly that there are non-standard (larger) page sizses, but
    how/when does the system decide to use these?
