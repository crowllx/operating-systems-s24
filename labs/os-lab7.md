Winston Shine

Operating Systems

Lab 7

5/14/2024

I worked with Duck on this lab.

Yes threads can give increased performance on a single core if a lot of
IO operations are being done. One thread could be blocked doing IO and another
thread could run.


### lab questions

1. using a basic concurrent counter didn't result in any difference in time
    time spent when using multiple threads. This was expected since the function 
    incrementing the counter uses locks.


2. I can see how a counter that makes use of multiple local counters to have the threads
    not need to update the global counter as often would result in less blocking
    due to not having to use locks as often.
