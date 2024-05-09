Winston Shine

Operating Systems

Lab 5f

05/07/2024


1. I wasn't able to kill or find 'init'. I believe this is because the vm i had setup
was using systemd.

2. when trying to kill all, most systemd and 'kworker' processes weren't affected at all
    I know some processes were killed such as journald, cron, and my ssh session.
    but the vm was still running and I could still ssh back in so the sshd server was still fine.
3. the vm didn't stop, I got alot of errors that files like ones under /proc couldn't be deleted.
    but alot of commands were no longer availabe such as ls or getcwd.
    
```
rm: cannot remove '/proc/3018/projid_map': Operation not permitted
rm: cannot remove '/proc/3018/setgroups': Operation not permitted
rm: cannot remove '/proc/3018/timers': Operation not permitted
rm: cannot remove '/proc/3018/timerslack_ns': Operation not permitted
rm: cannot remove '/proc/3018/patch_state': Operation not permitted
rm: cannot remove '/proc/3018/arch_status': Operation not permitted
crowll@exploit:~$ ll /
ls: command not found
crowll@exploit:~$ ls /
ls: command not found
crowll@exploit:~$ ls
ls: command not found
crowll@exploit:~$ ls -la
ls: command not found
crowll@exploit:~$ cd
-bash: cd: /home/crowll: No such file or directory
crowll@exploit:~$ ls
ls: command not found
crowll@exploit:~$ cd ..
cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
crowll@exploit:~/..$
```

What was the correct way to kill init? is this something I was unable to do with systemd or was I
using the incorrect flags with ps to actually see it?

after restoring the vm after removing all files I now do see /sbin/init as process 1 
but I am unable to kill it with the command `sudo kill -9 1`. 
