
# Threads, Mutexes, and Condition Variables

Two ways to execute parallel code:

 - fork() - create process
 - pthread_create() - create thread

Threads:

 - Advantage: Shared memory
 - Disadvantage: Shared memory

# History

1975: Programs execute sequentially, computers execute one
      program at a time.

1979: Multi-user machines require multitasking.

 - Multiple users mean multiple different simultaenous programs.
 - This leads to processes as we've been using them on Linux.
 - Single users can use multiple concurrent processes, e.g. the UNIX
   pipe operator.
 - Pre-emptive multi-tasking. Every tick (maybe 10ms), the hardware
   generates an interrupt, stopping the current program and letting 
   the OS kernel give anothre program a turn.

1987: Personal computers and GUIs

 - Graphic User Interfaces are logically concurrent.
 - You naturally run multiple programs, and you never know
   what's going to happen next.
 - Co-operative multitasking. Programs would run until they did
   blocking I/O or called a "yield()" function.
 - These systems have cooperative threads to handle logical concurrency:
   - e.g. A work thread, a network thread, a UI thread

1995: Windows 95 does pre-emptive multitasking.

Late 90's: Multiprocessor machines show up

 - Windows and Solaris had decent parallel thread support.
 - Linux didn't have parallel threads in the 90's.

Late 90's: Webservers are crazy popular.

Sequential:

```
loop() {
    sock = accept(network)
    req = read_req(sock)
    data = read_file(req)
    send_resp(sock, data)
}
```

Standard Linux webserver:

```
loop() {
    sock = accept(network)
    if ((cpid == fork())) {  // fork got super optimized
       // do nothing
    }
    else {
      req = read_req(sock)
      data = read_file(req)
      send_resp(sock, data)
      exit(0)
    }
}
```

Standard Windows webserver:

```
main() {
  spawn 10 threads of loop()
}

loop() {
    sock = accept(network)
    req = read_req(sock)
    data = read_file(req)
    send_resp(sock, data)
}

```


 - Fork on Linux is drastically faster than 
   processes spawning on Windows.
 - Threads on Linux became parallel in ~2002, evolved from fork().
 - Spawning threads on Windows is slightly faster than on Linux.

2005: Multi-core processors become available.

 - If you're CPU intensive programs today, parallel code is required.









