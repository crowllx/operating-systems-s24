Winston Shine

Operating Systems

Reading 3

4/25/2024

1. What is limited direct execution?

running a process directly on the cpu. the process is running in `user mode` and
has is `restricted` in what it can do. system calls are ways for a process running in user mode, to request (or execute?)
restricted operations.

2. What is the difference between user mode and kernel mode?

in user mode a process cannot issue I/O requests or other restricted actions.
I believe only the operating system can run in Kernel mode and it is unrestricted. 
it can issue I/O and other `restricted` operations.

3. What is a MLFQ?

multi level feedback queue: 
* optimizes turnaround time
* make a system feel responsive to users (optimize response time)
* has multiple queues with different priority levels
* varies jobs priority based on observed behaviour. Two of these behaviours are if a 
  job uses of it's alloted time, or gives up the cpu before it's alloted time is up.

if priority(a) > priority(b) -> a runs
if a == b -> Round Robin

4. What is starvation for processes?

processes that don't get enough run time on the cpu because they're priority is kept low.
this happens for long running jobs since their priority is decreased when they've used
up a time slice, while short jobs or jobs with a lot of I/O operations will reset
their priority every time they give up control of the cpu.

5. What is decay-usage in computing priority?

computing priority based on cpu usage, but having the value decay over time.
I think this means the effects cpu usage have on a jobs priority decay over time, 
a job will lower in priority when using a lot of cpu but slowing recover priority when
they start using less.

6. What is turnaround time?

time of completion - time of arrival

7. What is time to completion?

current amount of time a job needs to complete.

8. Explain SJF and STCF

sjf (shortest job first): prioritizes jobs by how how quickly they can be completed.

stcf (shortest time to completion first): like sjf but prioritizes by time to completion
and will re-evaluate any time a job joins the queue.
