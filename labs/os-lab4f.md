Winston Shine

Operating Systems

Lab 4F

4/26/2024


`Ostep Questions`

i can see a difference when making a large allocation, changing the format
of the output helps here, its much easier to notice the difference 
with the default listing of kilobytes.

pmap of my program for this lab
```
9938:   ./mem 10
0000000000400000      4K r---- mem
0000000000401000      4K r-x-- mem
0000000000402000      4K r---- mem
0000000000403000      4K r---- mem
0000000000404000      4K rw--- mem
0000000001379000    132K rw---   [ anon ]
00007fceb9800000 901896K rw---   [ anon ]
00007fcef0a29000     12K rw---   [ anon ]
00007fcef0a2c000    160K r---- libc.so.6
00007fcef0a54000   1392K r-x-- libc.so.6
00007fcef0bb0000    344K r---- libc.so.6
00007fcef0c06000     16K r---- libc.so.6
00007fcef0c0a000      8K rw--- libc.so.6
00007fcef0c0c000     60K rw---   [ anon ]
00007fcef0c1b000      4K r---- ld-linux-x86-64.so.2
00007fcef0c1c000    152K r-x-- ld-linux-x86-64.so.2
00007fcef0c42000     44K r---- ld-linux-x86-64.so.2
00007fcef0c4d000      8K r---- ld-linux-x86-64.so.2
00007fcef0c4f000      8K rw--- ld-linux-x86-64.so.2
00007ffd370a1000    136K rw---   [ stack ]
00007ffd3711d000     16K r----   [ anon ]
00007ffd37121000      8K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total           904420K
```

`Lab Questions` 

1. What does the command free do?

displays information about memory usage on the system.
how much is free/available. memory used by kernel buffers. memory
used by the page cache etc.

2. What does pmap do?

lists out the memory maps of processes.
very interesting to see how many segments there are.
there seems to be multiple segments for each library among various
anonymous segments. for example:

[vsyscall]

[vdso]

[vvar]

[stack] (I expected this)


Is it correct that each listing in pmap is a different segment?

What are [vsyscall] [vdso] [vvar] and [anon]?
