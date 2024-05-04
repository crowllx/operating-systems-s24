Winston Shine

Operating Systems

Lab 3t

4/26/2024

2. most the examples use 4 jobs and 3 queues i think, with I/O enabled and effecting
    priority.

3. ./mlfq -n 1 -j 3 -S -B 0 -a 1

unsure if this is accurate, but with round robin we would use 1 allotment, no
increased priority after IO, and no boosting. mainly unsure if the -B 0 would be correct.

5. unsure how to answer this question. doesn't this entirely depend on how many jobs are running?

6. from my small test using the -I flag resulted in a better avg turnaround time 
   but also changed the order in which jobs completed. the I flag moves jobs that finish IO
   immediately to the start of the queue. I'm not entirely how this effects the result
   in the way it does.
