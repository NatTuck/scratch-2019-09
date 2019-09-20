.global main

/*
A LinkedList is one of:
 - 0 (a null pointer), for an empty list
 - The (non-zero) address of a Cell

A Cell is a struct with two fields:
 - head: A long
 - tail: A LinkedList
*/

.text

car:
    //enter $0, $0
    mov 0(%rdi), %rax
    //leave 
    ret

cdr:
    // enter $0, $0
    mov 8(%rdi), %rax
    // leave
    ret

cons:
    enter $0, $0
    mov $16, %rdi
    call malloc
    leave 
    ret




