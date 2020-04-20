
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col
        ; rbx is my temp register

        ; add your code here
        ; A[Row][Column]
        ; &A[i][j] = Xa + L(C * i + j)
        ; need to set bit at array[row][col]
        mov rax, rdx    ;move row into rax
        imul rax, rsi   ;multiple row by row width
        add rax, rcx    ;add columns
        mov rbx, rax    ;store index into rbx, rax has index

        sar rax, 3      ;byte offset, index/8
        sal rax, 3      ;byte offset * 8

        sub rbx, rax    ;subtrack index(rbx) - byte_offset*8(rax)  ; bit_offset

        ;starting mask
        ;rax has byte_offset*8 in it at this point
        ;rbx has bit_offset in it at this point
        mov rax, 8
        sub rax, rbx    ;8 - bit_offset
        dec rax         ;mask shift value

        mov rbx, 0
        mov rsi, 1
        begin_shift:
            cmp rbx, rax
            je complete
        shift_left:
            sal rsi, 1
            inc rbx
            jmp begin_shift
        complete:
        ;rsi has the value i want to or against our value in rdi
        mov rax, rdx    ;move row into rax
        mov rbx, 10
        imul rax, rbx   ;multiple row by row width
        add rax, rcx    ;add columns        ;index on where i am in array, rdi + rax
        ;mov rbx, 8
        sar rax, 3

        or [rdi+rax], rsi
        ;add rdi, rax
        ;or [rdi], rsi
        ;add rax, rdi
        ;mov rdi, rax
        ;mov rax, 1
        ;or [rdi], rax

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0
        ; need to get bit from array[row][col]
        mov rax, rdx    ;move row into rax
        imul rax, rsi   ;multiple row by row width
        add rax, rcx    ;add columns
        mov rbx, rax    ;store index into rbx, rax has index

        sar rax, 3      ;byte offset, index/8
        sal rax, 3      ;byte offset * 8

        sub rbx, rax    ;subtrack index(rbx) - byte_offset*8(rax)  ; bit_offset

        ;starting mask
        ;rax has byte_offset*8 in it at this point
        ;rbx has bit_offset in it at this point
        mov rax, 8
        sub rax, rbx    ;8 - bit_offset
        dec rax         ;mask shift value

        mov rbx, 0
        mov rsi, 1
        check_begin_shift:
            cmp rbx, rax
            je check_complete
        check_shift_left:
            sal rsi, 1
            inc rbx
            jmp check_begin_shift
        check_complete:
        ;rsi has the value i want to or against our value in rdi
        mov rax, rdx    ;move row into rax
        mov rbx, 10
        imul rax, rbx   ;multiple row by row width
        add rax, rcx    ;add columns        ;index on where i am in array, rdi + rax
        ;mov rbx, 8
        sar rax, 3

        and [rdi+rax], rsi
        mov rax, [rdi+rax]
        ;add rdi, rax
        ;mov rax, [rdi]
        cmp rax, 0
        setg al
        movsx rax, al

        ;mov rax, [rax]

;        mov rax, rdx
;        imul rax, 10
;        add rax, rcx
;        sal rax, 2
;        add rax, rdi
;        mov rax, [rax]

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
