sys_read:   equ     0
sys_write:  equ     1
sys_exit:   equ     60

stdin_fileno:   equ     0
stdout_fileno:  equ     1
stderr_fileno:  equ     2

; buf is on stack
buf_size:   equ     8192

; ===================================================

    section     .rodata
error_msg:      db      "Read error occured", 0x0a
error_msg_len:  equ     $ - error_msg

; ===================================================

    section     .text
    global      _start

_start:
    ; word_count = 0;
    xor         r9, r9

    ; last_char_was_word = 0;
    xor         r8,  r8

    ; char buf[8192];
    sub         rsp, buf_size
    mov         rsi, rsp

read_next_buf:
    ; fread(buf, 8192, stdin);
    xor         rax, rax
    xor         rdi, rdi
    mov         rdx, buf_size
    syscall

    ; if (res == 0)
    ;   goto quit;
    ; else if (res < 0)
    ;   goto read_error;
    test        rax, rax
    jz          quit
    js          read_error

    ; curr_index = 0;
    xor         rcx, rcx

.check_next_char:
    ; if (curr_index == bytes_read)
    ;   goto read_next_buf;
    cmp         rcx, rax
    je          read_next_buf

    ; if (c >= 9 && c <= 13)
    ;   goto char_is_space
    ; else 
    ;   goto .check_if_32
    mov         bl, byte [rsi + rcx]
    sub         rbx, 9
    cmp         rbx, 4
    ja          .check_if_32
    jmp         .char_is_space

.check_if_32:
    cmp         rbx, 23
    jne         .char_is_not_space

.char_is_space:
    ; if (last_char_was_word == true)
    ;   word_count++;
    test        r8, r8
    jz          .after_increment
    inc         r9

.after_increment:
    ; last_char_was_word = 0;
    ; goto loop_end;
    xor         r8, r8 
    jmp         .loop_end

.char_is_not_space:
    ; last_char_was_word = 1;
    mov         r8, 1

.loop_end:
    ; curr_index++;
    inc         rcx
    jmp         .check_next_char


quit:
    ; if (last_char_was_word)
    ;    word_count++;
    cmp         r8, 1
    jne         .after_increment
    inc         r9

.after_increment:
    ; print_answer()
    call        print_int
    
    ; exit()
    mov         rax, sys_exit
    xor         rdi, rdi
    syscall     


read_error:
    ; print("Read error occured\n");
    mov         rax, sys_write
    mov         rdi, stdout_fileno
    mov         rsi, error_msg
    mov         rdx, error_msg_len
    syscall

    ; exit(1)
    mov         rax, sys_exit
    mov         rdi, 1
    syscall


print_int:
    ; Allocate char[24] ending with '\n'
    mov         r11, rsp
    dec         r11
    mov         byte [r11], 0x0a
    sub         rsp, 24

    ; r10 is curr len, r12 is just 10,
    ; rax holds curr number of words
    mov         r10, 1
    mov         r12, 10
    mov         rax, r9
    
.next_digit:
    ; num_digits++;
    inc         r10

    ; res /= 10;
    xor         rdx, rdx 
    div         r12

    ; buf[--i] = char(remainder);
    dec         r11
    add         dl, '0'
    mov         byte [r11], dl

    ; if (res == 0)
    ;   goto end
    ; else
    ;   goto next_digit
    test        rax, rax
    jz          .end
    jmp         .next_digit

.end:
    ; print("%d", answer);
    mov         rax, sys_write
    mov         rdi, stdout_fileno
    mov         rsi, r11
    mov         rdx, r10
    syscall

    ; free(char[24])
    add         rsp, 24
    ret