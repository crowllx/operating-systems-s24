Winston Shine

Operating Systems

OS Lab 6

05/07/2024

I worked with Lohen and Jonah for this lab.

I managed to get cd working by chdir()

```c
if (!strcmp(buf, "cd") && args != NULL) {
    chdir(args);
    continue;
}
```
