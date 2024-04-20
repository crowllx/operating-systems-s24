Winston Shine

Operating Systems

Lab 2f

4/12/2024

I worked by myself for this lab. I think I was close to getting question 8 but did
not quite finish. The solution I used was to use dup2 to close and duplicate stdout
or stdin rather than close and replace them manually.

5. wait(): on success, returns the process ID of the terminated child;
    on error, -1 is returned. Nothing happened when calling wait in the child
    process. I believe this is because the child hasn't made any fork calls.
6. waitpid would be useful if a process has forked multiple times, but is only interested
    in waiting for a select number of children but not all.
7. nothing is printed to standard out since the child inherits stdin, stdout, stderr from the parent.
    and stdout has been closed
8.
