section .text
    global cpuidpresent             ; Entry point for the Linker

cpuidpresent:                       ; Function start
    pushfq                          ; Save RFLAGS to the stack
    pop     rax                     ; Load RFLAGS into RAX 
    mov     rbx, rax                ; Copy RAX to RBX 
    xor     rax, 0x200000           ; Toggle bit 21
    push    rax                     ; Push to stack
    popfq                           ; Save changed RAX to RFLAGS
    pushfq                          ; Push RFLAGS to TOS
    pop     rax                     ; Store RFLAGS in RAX 
    xor     rax, rbx                ; See if bit 21 has changed
    jz      no_cpuid                ; If no change, no CPUID 

    mov     eax, 1                  ; CPUID is supported, return 1
    ret                             ; Return from function

no_cpuid:
    xor     eax, eax                ; CPUID is not supported, return 0
    ret                             ; Return from function
