
# Computer Systems Lecture 10: Shell Background Info

 - IO: FILE* for stdc, int fd for syscalls

## Creating New Processes

 - A "process" is a running instance of a program.
 - To get a new process, you use the "fork" syscall.
   - fork() copies the current running process
 - To run a new program in an existing process, call "exec".
   - This deletes the innards of the process and replaces them
     with new data read from an executable file on disk.




