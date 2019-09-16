// Example usage:
//
//  $ ./bigger 5
//  => not bigger
//  $ ./bigger 15
//  => bigger

.global main

.data
bigger_text: .string "bigger"
not_bigger_text: .string "not bigger"

.text

main:
    enter $0, $0

    // int main(int argc, char** argv) 
    //            %rdi        %rsi 

    // char* text = argv[1];
    mov 8(%rsi), %rdi

    // int num = atol(text);
    // first argument already in %rdi
    call atol

    // result is in %rax

    // if (num > 10) {
    cmp $10, %rax
    jg big

// not bigger
    mov $not_bigger_text, %rdi
    call puts
    jmp done

big:
    mov $bigger_text, %rdi
    call puts

done:
    leave
    ret


