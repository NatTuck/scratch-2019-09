
# Threads

 - Advantage: Shared memory.
 - Disadvantage: Shared memory.


## History

 - 70's all programs are sequential
 - Late 70's: Multiple users
   - This requires multitasking
   - This lead to UNIX-style process model
   - Multiple sequential programs running concurrently.
   - Same user wants to run multiple programs, and have them
     communicate.
   - Multi-user systems had pre-emptive multitasking. Every tick
     (maybe 10ms) the OS pauses the active process and gives another
     process a turn.
 - Mid 80's: Personal computers and GUIs
   - Multiple windows implies multitasking
   - Background processes work by cooperative multitasking.
     - Programs execute while they have stuff to do.
     - When they're done, they call yield(), which gives othre
       programs a turn.
   - GUIs are innately concurrent, so these systems added threads.
   - With Windows 95, desktop PCs adopted pre-emptive scheduling,
     including for threads.

Late 90's: Multiprocessors
 
 - Windows and Solaris had good parallel thread support. 
 - Linux and other UNIX type systems just used processes.
 - A singificant use for multi-processor machines in the late 90's
   was web servers.


## Web Server

Sequential:

```
     loop() {
        req = get_request(network)
        data = read_file(req)
        send_file(network, data) 
     }
```

Fork:

```
     loop() {
        req = wait_for_req(network)
        if ((cpid = fork())) {
          //skip 
        } else {
          full_req = get_request(req)
          data = read_file(req)
          send_file(network, data) 
        }
     }
```

Thread:


 ```
    main() {
       10 times:
         spawn thread_loop();
    }
    
    thread_loop() {
        req = get_request(network)
        data = read_file(req)
        send_file(network, data) 
     }
```

 * Linux didn't get decent parallel thread support until 2002.
 * Result: fork() on Linux is drastically faster than creating new
   processes on Windows.
 * Threading is slightly faster on Windows than Linux. 
 * Multi-core desktop processors showed up around 2005, and since then
   parallelism is nessiary for CPU-heavy apps.
 
