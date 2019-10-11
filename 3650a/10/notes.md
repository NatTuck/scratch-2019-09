# Computer Systems Lecture 10: Shell Background

Starting a new process on POSIX:

 - fork system call
 - Fork copies the current process.
   - The full contents of the address space.
   - Open file descriptors
   - A bunch of other stuff.

Running a program:

 - exec system call
 - Replaces the contents of the current process by
   loading an executable from disk and running the
   main function.
 - Exec does not create a new process.





