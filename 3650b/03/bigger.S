//   $ ./bigger 5
//   => not bigger
//   $ ./bigger 15
//   => bigger

.global main

.data
bigger_msg: .string "bigger"
not_bigger_msg: .string "not bigger"
fmt: .string "number is '%ld'\n"

.text

main:
    enter $0, $0

    // int main(int argc, char** argv)
    //            %rdi         %rsi

    mov 8(%rsi), %rdi
    call atol

    cmp $10, %rax 
    jg bigger

    mov $not_bigger_msg, %rdi
    call puts
    jmp done

bigger:
    mov $bigger_msg, %rdi
    call puts

done:
    leave
    ret





