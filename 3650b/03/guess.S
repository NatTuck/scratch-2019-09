// guess the number
//  - prompt user for number
//  - say "too low", "too high" or "you win"
//  - repeat if not win
//  - count guesses

// Function:
//  - main
//  - get_number // print and read
//  - check_number // print message, handle wins

// main():
//   global n = random(0, 100) 
//   for(ii = 0; ii < 10; ++ii):
//     x = get_number()
//     done = check_number(x)
//     if (done): break

// vars:
//   - n is on global label "number"
//   - ii is %rbx
//   - x is %rax -> %rdi
//   - done is %rax



// get_number():
//   print "enter number"
//   long n;
//   scanf(...)
//   return n

// check_number(x):
//   if (x > n): 
//     print "too high"
//     return false
//   else if (x < n): 
//     print "too low"
//     return false
//   print "done"
//   return true


