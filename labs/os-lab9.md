Winston Shine

Operating Systems

Lab 9

5/28/2024

The reader writer problem occurs handling read/write access to some object for multiple threads, (maybe a file
I think the book used an example of a linked-list data structure). writers have to wait for readers
to finish to ensure that readers don't get inconsistent resultsm, but if there are many readers
this can lead to starvation for for writers that are stuck waiting for there to be no readers.

Semaphores can be used here as a lock to ensure writers do not write while readers are reading.
I'm not entirely sure how to approach the problem or if I fully understand it but I think we need to use a second 
semaphore in order for readers to check if there are writers waiting first before reading.
Not just ensure that the writer is not currently writing but there are no writers waiting in the queue.

I'm unsure what is best to use to track waiting writers. I guess a semaphore?
