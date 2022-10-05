ok_overflow:
  push dword msg
  push dword [msg_size]
  call s_output
  add esp, 8
  mov EAX, 1
  mov EBX, 0
  int 80h


s_input:
push EBP
mov EBP,ESP
push ebx
push ecx
push esi
push edi
sub ecx, ecx 

s_input_loop:
push ecx
mov eax, 3
mov ebx, 0
mov ecx, char
mov edx, 1 
int 80h
push ecx
mov edi, [EBP+8] 
mov ebx, [EBP+12]
add ecx, eax 
mov eax, [char]
mov [edi+esi], eax 
inc esi 
jl s_input_loop
pop esi
pop edi
pop ecx
pop ebx
pop EBP 
ret 4

s_output:
push EBP
mov EBP,ESP
push ecx
sub ecx, ecx 
mov eax, 4
mov ebx, 1
mov ecx, [EBP+8]
mov edx, [EBP+12] 
int 80h
pop ecx
pop EBP 
ret 4

output:

input:

section .data

msg db 'DEU OVERFLOW,OdH,0aH'
msg_size EQU $-msg
msg_w_r db 'Foram lidos/escritos '
msg_w_r_size EQU $-msg_w_r
label_0 dd 2

section .bss

char resb 1
label_1 resd 1
label_2 resd 1
label_3 resd 1

section .text

global _start:

_start:
    push dword label_1

    call input

    add esp, 8

    mov ECX, [label_0]
    cdq
    idiv ECX

    mov ECX, [label_0]
    imul ECX
    jo ok_overflow

    mov EAX, [label_1]

    mov [label_3], EAX

    mov EBX, [label_2]
    mov [label_1], EBX

    mov EAX, 1
    mov EBX, 0
    int 80h

