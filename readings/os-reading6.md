Winston Shine

Operating Systems

Reading 6

5/12/2024

1. What is a thread?

    a separate point of execution in a single process, executing its own instructions
    but sharing the same address space and accessing the same data. 

2. What is a race condition?

    multiple threads/processes accessing the same data simultaneously.
    causing the output to not be deterministic, thread 1 could read  a value, and
    thread 2 could write to and now thread 1 doesn't have the 'correct' value anymore but
    will continue as is.

3. What is a critical section of code?

    a section of code that multiple threads are executing and accessing shared
    data leading to potential race conditions.
    
4. Define atomic operation.


    grouping actions together so that if the task is succcessful all them executed, and if
    something fails, none of them were executed. It is grouping sub tasks together
    in a way that does not allow for some inbetween state where. ex: sub task 1 modified something,
    but the larger task it was a part of failed and did not finish, yet 'things'
    were still modified by sub task 1.
    

5. What is a mutex?

   a way to lock segments of code so that only a thread that has acquired 
   the mutex lock can execute it, thus preventing race conditions.

6. What questions do you have about the reading?

    the code presented in the book used two different types for initializing locks,
    `lock_t` and `pthread_mutexlock_t`. How are these different and why would I use one over the other?
