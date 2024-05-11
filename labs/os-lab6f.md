Winston Shine

Operating Systems

Lab 6f

05/10/2024


1. Yes it points out the exact lines of code where the race conditions occured
    It additionally gives information about what locks are held, what how many threads
    are created, whether the race condition came from a read/write and how many bytes
2. 0 errors reported, when removing one of the offending lines. with only one lock helgrind reports 2 errors still.
    when adding locks around both no errors are reported.
3. I believe the issue on dead lock is that thread one lock m1 and thread 2 will lock m2,
    then both threads try to lock the alternative and results in both threads stuck waiting because neither will
    unlock the mutex.:w
    
4. helgrind reports an incorrect lock order. It seems like once thread1 creates a lock,
    there becomes a 'required order' that mutexs are used in. 
```
==27339== Thread #3: lock order "0x10C040 before 0x10C080" violated
==27339==
==27339== Observed (incorrect) order is: acquisition of lock at 0x10C080
==27339==    at 0x48512DC: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x109288: worker (main-deadlock.c:13)
==27339==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x4911A93: start_thread (pthread_create.c:447)
==27339==    by 0x499EA33: clone (clone.S:100)
==27339==
==27339==  followed by a later acquisition of lock at 0x10C040
==27339==    at 0x48512DC: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x1092C3: worker (main-deadlock.c:14)
==27339==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x4911A93: start_thread (pthread_create.c:447)
==27339==    by 0x499EA33: clone (clone.S:100)
==27339==
==27339== Required order was established by acquisition of lock at 0x10C040
==27339==    at 0x48512DC: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x10920E: worker (main-deadlock.c:10)
==27339==    by 0x4854B7A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==27339==    by 0x4911A93: start_thread (pthread_create.c:447)
==27339==    by 0x499EA33: clone (clone.S:100)
```

5. Yes it has the same problem, the lock order is different for each thread. Helgrind does report
    the same error as well. I'm not sure if this question is suggesting the error should be different.
