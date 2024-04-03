Winston Shine
Operating Systems
Reading Week 1
4/1/2024


1.  What is a system call?
   
    API's to OS operations (file operations, memory allocation, and more)
    
2.  What are the 3 main themes in the OSTEP book?
    
    virtualization, concurrency, and persistence
    
3.  What does it mean to say that the OS virtualizes the CPU?
    
    the OS allows many processes to run simultaneously on a single cpu.
    This is done by `virtualizing` the cpu to make it seem as if there were multiple cpus available
    
4.  What does it mean to say that the OS virtualizes the memory?
   
    The OS manages physical memory and allocates `virtual address spaces` to processes. This allows 
    multiple processes to use this shared resource without conflict. to a process, its `address space`
    is it's own memory, when really the address space is a mapping to physical memory managed by the OS.
    
5.  Why does the program in figure 2.5 give the wrong answer for large iterations of the loop but not small ones?
    
    a mutex lock isn't being used so the two threads can attempt to increment the counter at the same time.
    thread 1 loads counter -> thread 1 increments it -> thread 2 loads counter -> thread 1 stores new count ->
    thread 2 increments count -> thread 2 stores new count
