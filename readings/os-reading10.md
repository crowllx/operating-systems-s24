Winston Shine

Operating Systems

Reading 10

6/7/2024

1. what is fsck?
    
    file system checker. A crash consistency solution that allows inconsistencies to happen
    and then fixes then at boot.
    
2. What is a superblock (ch 40)?

    a block on disk that is reserved to store information about the filesystem itself.


3. What is write-ahead logging?

    also known as journaling, this method takes notes of operations and writes 
    them to disk before performing that way if a crash takes place it is documented and
    can be fixed.
    
4. What is data journaling?

    type of journaling where more detailed transactions are written to the journal first so they can be replayed.
    
    Does this actually perform the transcations twice or is it just documenting what transactions should occur?

5. What is a reference monitor?

    code that runs an algorithm to determine access control.

6. What is capability access control? How does it differ from ACLs?
    
    ACLs use a list of permissions for each user, while capability access control
    functions more like locks and keys. I don't understand yet how those locks/keys
    are implemented
    
7. What is mandatory access control?

    access control system where some 'authority' is always involved in 
    access control decisions and I believe this authority has more say in these decisions
    than even the owner of the data.


