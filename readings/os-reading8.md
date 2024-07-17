Winston Shine

Operating Systems

Reading 8

5/27/2024

1. What is the difference between a scalable counter and a global counter?

  a scalable counter can be incremented in multiple threads in parallel and then only
  brought back to global scope at certain times. A global counter is shared by all threads
  so if a thread needs to increment it, It will have to use a lock in order to
  not create race conditions.

2. What is a semaphore variable and how is it used?

    a semaphore is an object that holds an integer value.
    there are two actions used by this object (sem_wait and sem_post).
    based on how you assign the inital value of the integer a semaphore can be used
    in multiple different ways.


3. What is the difference between a binary semaphore and a lock?

    I think just the way that they are implemented. a binary semaphore is a specific
    way to use a semaphore in order to create a lock. A semaphore can be used as 
    a condition variable while a lock cannot.


4. What is polling a device and programmed I/O?

    polling a device is checking the status of the status, basically seeing 
    whether it's busy with a task before trying to give it a command.
    programmed I/O is when the main cpu is doing the data movement.

5. What is interrupt-based I/O?

    rather than polling the device until it is ready the os puts the process to sleep
    and when the device is finished it will trigger a hardware interrupt that switches
    CPU to the OS and runs a specific interrupt handler.

6. What is two-phased I/O handling?

    the OS starts by polling for a little while and if the device is still not finished resort 
    to an interrupt-based approach.
    polling is faster for fast devices - while interrupt-based is more efficient for slow devices.
    so using a hybrid approach can work best for cases where the speed of the device is unreliable
    or unkown


can the I/O strategy change for a device at run time? for example are there ways 
an OS can tell if an interrupt strategy approach used on a device is causing a livelock
and decide to switch back to polling? or does the device have to be configured to use either a coalescing
or two-phased approach beforehand?
