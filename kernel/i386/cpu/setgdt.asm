[GLOBAL GdtLoad]

GdtLoad:
   mov eax, [esp+4]
   lgdt [eax]
   
   ; reload cs register
   push 0x08
   lea ax, [rel .reload_cs]
   push ax
   retf
.reload_cs:
    mov ax, 0x10
    mov ds, ax
    MOV   ES, AX
    MOV   FS, AX
    MOV   GS, AX
    MOV   SS, AX
    RET