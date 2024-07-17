Winston Shine

Operating Systems

Reading 7

5/20/2024


1. What is a scalable counter?
    a counter with one global value, and multiple local values, this way the
    local counters can be updated concurrently and only periodically merged with the global count.
    this reduces to the need to make use of locks on every increment of the counter.

2. What is a condition variable and how is it used?

    a way to stop a thread from executing when certain conditions are not met.
    
    when said condition is not met, the thread will place itself in a  queue and waits for it to change (i think sleep is the correct term?)
    when the condition has been changed, I think whatever thread changed the condition is required to wake up the threads waiting in
    the queue

3. What is the difference between a semaphore and a lock?

    a semaphore implements a condition variable alongside the use of locks

4. Are we going too fast in the text?

    I don't think so, but I had some previous experience with the earlier topics we covered 
    So I could imagine It might be difficult to keep up if I had been taking this class 
    a year ago.

5. What questions do you have about the reading?

    are semaphores the go to method for implementing safe concurrency?
    when is a simple solution actually a better choice and why?
