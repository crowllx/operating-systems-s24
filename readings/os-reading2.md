Winston Shine

Operating Systems

Reading 2

4/9/2024


1.    What does fork() do?
    
      creates a new process, that is a copy of the current process.
      
2.    When a process calls fork(), what value is returned to the child? What value is returned to the parent?

      0 is returned to the child, and the childs PID is returned to the parent.

3.    Which process runs first, the child or the parent?

      The parent

4.    What does exec() do?

      executes a new process given the name of an executable and some arguments.
      a succesful call to exec does not return. it essentially transforms a
      process into another. the original memory space of the process is re-initialized
      for the new process.

5.    What does pipe() do?

      connects the standard ouput of one process, to the standard input of another process.

6.    What is SIGINT?
      
      signal used to interrupt/terminate a process ( ctrl-c ).

