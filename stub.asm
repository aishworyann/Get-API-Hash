a section .text
global calculate_api_hash
global calculate_dll_hash
global __ROR__
;---------------------------------------------

/*
__ROR__:
    mov eax, ecx
    mov ecx, edx

    ror rax, cl
    ret
*/
------------------------------------------------
calculate_dll_hash:
    
    mov rsi, rcx
    mov rcx, rdx

    xor rax, rax
    xor rdx, rdx


_loop_dll:

    mov al, byte [rsi]
    cmp al, 0x61
    jge do_upper

do_ror:

    ror edx, 0xd
    add edx, eax
    add rsi, 1
    loop _loop_dll

    mov eax, edx
    ret


do_upper:
    sub ax, 0x20
    jmp do_ror


;----------------------------------------------

calculate_api_hash:

    xor rax, rax
    mov rsi, rcx
    xor rdx, rdx
    dec rsi

_loop_api:

    inc rsi
    mov al, byte [rsi]
    ror edx, 0xd
    add edx, eax

    cmp byte [rsi], 0
    jne _loop_api

    mov eax, edx
    ret

; abcd