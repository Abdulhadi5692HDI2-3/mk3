extern ExceptionHandler
extern IrqHandle
; ISRS
%macro isr_err_stub 1
isr_stub_%+%1:
    call ExceptionHandler
    iret 
%endmacro
%macro isr_no_err_stub 1
isr_stub_%+%1:
    call ExceptionHandler
    iret
%endmacro
%macro isr_irq 1
isr_stub_%+%1:
    push eax
    mov eax, %1
    jmp isr_irq_stub
%endmacro

; the 32 exception handlers
; todo: if there's an error they should
; give that as an argument to the exception handler.
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
isr_irq 32
isr_irq 33
isr_irq 34
isr_irq 35
isr_irq 36
isr_irq 37
isr_irq 38
isr_irq 39
isr_irq 40
isr_irq 41
isr_irq 42
isr_irq 43
isr_irq 44
isr_irq 45
isr_irq 46
isr_irq 47

isr_irq_stub:
    pusha
    push ds
    push es
    
    push eax
    call IrqHandle
    add esp, 4

    pop es
    pop ds
    popa
    pop eax
    iret

global IsrStubTable
IsrStubTable:
%assign i 0 
%rep    48
    dd isr_stub_%+i
%assign i i+1 
%endrep
