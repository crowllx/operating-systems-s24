Winston Shine

Operating Systems

4/23/2024


1. What does the pipe() function do?

    opens two files, using the lowest available file descriptor for each,
    one is used to write to, and the other is used to read from.
    
2. Why can you read and write to a pipe but you can't open it?

    it's already been opened from the pipe() call.
    
3. How is that different from files, even though they both use file descriptors?

    files generally aren't linked to other files but a path on the filesystem or a stream ie: stdin/stdout
    is two connected files).
    
4. What questions do you have?
    
    if you close stdout, then create a pipe. is stdout open again? or is the fd
    assigned to fd 1 from creating the pipe not the same as re-opening stdout?

