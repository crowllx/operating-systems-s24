Winston Shine

Operating Systems

Lab 1F

4/5/2024

1. the variable is copied for the child and not updated when the parent modifies it

2. yes both the parent and child can read from the file descriptor. the seek pointer to 
whats been read seems to be the same, so if the parent reads all the contents,
then the child process reads it will just read an EOF. writing concurrently seems to work fine. although i didn't expect this and am unsure
if my test case was accurate

3. yes, I did this using sleep(1)
4. from what I can tell the main reason is to allow for multiple input formats for
arguments to command. Althought I only tried two variants and i dont fully understand
the difference in expected input for args.
```
execv:

Parameters:  
 const char * __path
 char *const * __argv

execl:

Parameters:  
 const char * __path
 const char * __arg
```
