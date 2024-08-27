; Assembly function to check if CPUID instruction is supported
; Author: Maurice Green

section .data
    msg1 db "CPUID is not Supported on this Architecture", 0xA      ; Message if CPUID not supported 
    msg2 db "CPUID is supported", 0xA                               ; CPUID supported Message 
    len1 equ $ - msg1                                               ; calculate length of msg1
    len2 equ $ - msg2                                               ; calculate length of msg2   

section .text
    global _start               ; Entry point for the Linker

_start:
    pushfd                      ; Save EFLAGS to the stack
    pop         eax             ; Load EFLAGS into EAX 
    mov         ebx, eax        ; Copy EAX to EBX 
    xor         eax, 0x200000   ; Toggle bit 21
    push        eax             ; push to stack
    popfd                       ; save changed EAX to EFLAGS
    pushfd                      ; push EFLAGS to TOS
    pop         eax             ; store EFLAGS in EAX 
    xor         eax, ebx        ; see if bit 21 has changed
    jz          NO_CPUID        ; if no change, no CPUID 

YES_CPUID:                      ; Non-branch transition to YES CPUID
    mov         eax, 4          ; syscall number for sys_write == 4
    mov         ebx, 1          ; File descriptor 1 is stdout
    mov         ecx, msg2       ; Pointer to Yes CPUID string 
    mov         edx, len2       ; Length of msg2 
    int         0x80            ; Interrupt to invoke syscall
    jmp         EXIT            ; Exit program

NO_CPUID:
    mov         eax, 4          ; syscall number for sys_write == 4
    mov         ebx, 1          ; File descriptor 1 is stdout
    mov         ecx, msg1       ; Pointer to Yes CPUID string 
    mov         edx, len1       ; Length of msg1 
    int         0x80            ; Interrupt to invoke syscall 

EXIT:
    mov         eax, 1          ; Syscall to sys_exit (on x86 use 1)
    xor         ebx, ebx        ; return code 0
    int         0x80            ; interrupt to invoke syscall