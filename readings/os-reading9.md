Winston Shine

Operating Systems

Reading 9

6/4/2024

1. What is an inode?

    a low level name for a file. A number that can be used to determine where
    on disk a file is located.

2. what does strace do?

    trace every system call made by a process
    
3. what does lseek() do?

    positions at an offset in the file, so you can read/write
    from a specific portion

4. What does dup do?

    creates a new file descriptor that refers to an already open file.
    duplicates a file descriptor.

5. What does mmap do?

    loads a file into memory so a process can access it persistently.
    I believe this mainly means creating a mapping of virtual addresses
    to byte offsets in the file.
    
    
6. What is ln -s (el-en)?

    symbolic link. it creates a file that points/links to another file at a specified path.

7. What is a multi-level file index?

    to support large files. we can have inodes that contain direct and indirect pointers,
    the indirect pointers lead to an indirect block. the books example says gives these blocks as 4kb in size.

8. What questions do you have about the reading?

    with an indirect block, is the size always 4KB?
    how is it determined when to use multiple indirect pointers? is there a set
    amount or are they added to an inode dynamically?
