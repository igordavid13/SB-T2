;Projeto 2 da disciplina Software Basico
;Universidade de Brasilia
;Instituto de Ciencias Exatas
;Departamento de Ciencia da Computacao
;Software Basico 1/2021
;Professor: Bruno Macchiavello
;Desenvolvido por: Guilherme Silva Souza e Maria Eduarda Machado de Holanda

;macro para ler uma string
%macro read_str_macro 2
mov eax, 3
mov ebx, 0
mov ecx, %1 
mov edx, %2 
int 80h
%endmacro

;macro para printar uma string
%macro print_str_macro 2
mov eax, 4
mov ebx, 1 
mov ecx, %1
mov edx, %2
int 80h
%endmacro

s_input:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        ;empilhando registradores que vão ser utilizados
        push ebx
        push ecx
        push esi
        push edi

        sub ecx, ecx ; n total de bytes

loop_s_input:

        ; le caracter
        push ecx
        read_str_macro char, 1
        pop ecx

        mov edi, [EBP+8] ; edi = ponteiro pra label
        mov ebx, [EBP+12] ; ebx = numero de iteracoes
        
        add ecx, eax ; soma total de bytes lidos
        
        mov eax, [char]
        mov [edi+esi], eax ; edi[esi] = resultado da chamado do input
        inc esi ; esi += 1

        ; loop enquanto eax for menor que o numero de iteracoes
        cmp esi, ebx
        jl loop_s_input
fim_s_input:
        mov eax, ecx ;retorna o n de bytes lidos no eax
        
        push eax
        print_str_macro bytes_msg, bytes_msg_size ; exibe a msg "Foram lidos/escritos" 
        pop eax

        ;converte o n de bytes int->str
        push eax
        call convert_int_2_str
        mov eax, [result_int_str]
        
        print_str_macro result_int_str, [result_int_str_size] ; exibe a qnt de bytes lidos
        print_str_macro bytes_msg_2, bytes_msg_2_size ; exibe a msg " bytes"
      
        ; desempilha registradores
        pop esi
        pop edi
        pop ecx
        pop ebx
        pop EBP 
        ret 4

s_output:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        ;empilhando registradores que vão ser utilizados
        push ecx

        sub ecx, ecx ; n total de bytes

        print_str_macro [EBP+8], [EBP+12] ; ponteiro para label e tamanho da label
        mov ecx, eax ; total de bytes escritos
        
        push ecx
        print_str_macro newln, 2
        pop ecx

fim_s_output:
        mov eax, ecx ;retorna o n de bytes escritos no eax
        
        push eax
        print_str_macro bytes_msg, bytes_msg_size ; exibe a msg "Foram lidos/escritos" 
        pop eax

        ;converte o n de bytes int->str
        push eax
        call convert_int_2_str
        mov eax, [result_int_str]
        
        print_str_macro result_int_str, [result_int_str_size] ; exibe a qnt de bytes lidos
        print_str_macro bytes_msg_2, bytes_msg_2_size ; exibe a msg " bytes"
                
        ; desempilha registradores
        pop ecx
        pop EBP 
        ret 4

input:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        pusha ;empilhando registradores que vão ser utilizados
        
        read_str_macro [EBP+8], 10 ; le a str

        mov [number_of_bytes], eax ;salva o n de bytes lidos
        
        print_str_macro bytes_msg, bytes_msg_size ; exibe a msg "Foram lidos/escritos" 

        ;converte o n de bytes int->str
        push dword [number_of_bytes]
        call convert_int_2_str
        mov eax, [result_int_str]
        
        print_str_macro result_int_str, [result_int_str_size] ; exibe a qnt de bytes lidos
        print_str_macro bytes_msg_2, bytes_msg_2_size ; exibe a msg " bytes"

        push number
        call convert_str_2_int

fim_input:        
        ;desempilha os registradores usado
        popa
        pop EBP

        mov eax, [number_of_bytes] ;retorna o n de bytes lidos no eax
        ret 4

output:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        ;empilhando registradores que vão ser utilizados
        pusha

        mov eax, [EBP+8]

        push dword [EBP+8]
        call convert_int_2_str      
        mov eax, [result_int_str_size]
        mov [number_of_bytes], eax

        print_str_macro result_int_str, [result_int_str_size] 
        print_str_macro newln, 2 ; newln

        print_str_macro bytes_msg, bytes_msg_size ; exibe a msg "Foram lidos/escritos" 
        
        ; converte int->str
        push dword [result_int_str_size]
        call convert_int_2_str

        print_str_macro result_int_str, [result_int_str_size]; exibe a qnt de "bytes" 
        print_str_macro bytes_msg_2, bytes_msg_2_size; exibe a msg " bytes" 
        
        ;desempilha os registradores usado
        popa
        pop EBP
        
        mov eax, [number_of_bytes] ;retorna o n de bytes escritos no eax
        ret 4

; função para converter o str para int, o resultado vai pra result_str_int
convert_str_2_int:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        pusha

        mov eax, 0 ; eax = valor total
        mov ebx, [EBP+8] ; ebx = numero
loopchar: 
        movzx ecx, byte [ebx] ;carrega o char 
        inc ebx
        ;verificando o sinal (soh ignora pq vai ser tratado no final)
        cmp ecx, '-'
        je loopchar
        ; verificando se chegou no fim
        cmp ecx, '0'
        jb ehneg?
        cmp ecx, '9'
        ja ehneg?

        ;convertendo
        sub ecx, '0'
        imul eax, 10
        add eax, ecx

        jmp loopchar
ehneg?:    
        mov ebx, [EBP+8] ; ebx = numero
        movzx ecx, byte [ebx] ;carrega o primeiro char
        cmp ecx, '-' ;verifica se é um -
        jne fim_convert_str_2_int ;se nao for pula para o fim_convert_str_2_int
        imul eax, -1 ;se for multiplica por -1
fim_convert_str_2_int:
        mov [result_str_int], eax ;move o resultado para result_str_int
        
        ;desempilha os registradores usado
        popa
        pop EBP
        
        ret 4

; função para converter o int para str, o resultado vai pra result_int_str
convert_int_2_str:
        ;criando a pilha local (frame de pilha)
        push EBP
        mov EBP,ESP

        ;empilhando registradores que vão ser utilizados
        pusha

        mov eax, [EBP+8] ; valor
        mov esi, result_int_str_reverse ; ponteiro para resultado
        mov edi, 0; tamanho da string

        cmp eax, 0
        jge pos

        print_str_macro neg_, neg_size; exibe o simbolo de negativo
        
        mov eax, [EBP+8] ; valor
        
        imul eax, -1 ; transforma para positivo
        inc edi    
pos: 
        mov edx, 0
        mov ecx, 10
        div ecx
        add edx, '0'
        mov [esi], edx
        inc esi
        inc edi 
        cmp eax, 0
        jne pos 

revert:
        inc edi
        mov [result_int_str_size], edi
        mov esi, result_int_str_reverse
        mov edx, result_int_str
        mov eax, 0

loop1_reverse:
        mov cl, [esi] ;pega o char
        inc eax
        cmp eax, edi ;compara final str
        ja loop2_reverse 
        inc esi 
        jmp loop1_reverse

loop2_reverse:
        dec esi 
        mov cl, [esi] ; pega o char
        dec edi ; dec no tamanho
        cmp edi, -1 ; compara se ta no inicio da sring
        je fim_convert_int_2_str
        mov [edx], byte cl ;salva o char no conteudo de edx
        inc edx ; incrementa o ponteiro
        jmp loop2_reverse

fim_convert_int_2_str:
        ;desempilha os registradores usado
        popa
        pop EBP
        ret 4

overflow:
        print_str_macro overflow_msg, overflow_msg_size
        mov eax, 1
        mov ebx, 0
        int 80h

section .data
neg_                 db '-'
neg_size             EQU $-neg_
newln                db 0dH, 0aH
bytes_msg            db 'Foram lidos/escritos '
bytes_msg_size       EQU $-bytes_msg
bytes_msg_2          db ' bytes', 0dH, 0ah
bytes_msg_2_size     EQU $-bytes_msg_2
overflow_msg         db 'Overflow Detectado! O programa sera encerrado.', 0dH, 0ah
overflow_msg_size    EQU $-overflow_msg
label2		 dd 2
label3		 dd 0
label4		 dd 0

section .bss
number                  resb 10
number_of_bytes         resb 10
result_str_int          resd 1
result_int_str_reverse  resb 10
result_int_str          resb 10
result_int_str_size     resd 1
char                    resb 1
label1		 resd 1

section .text
global _start
_start:
push number
call input
mov EAX, [result_str_int]
mov [label1], EAX
mov EAX, [label1]
label5:
mov ECX, [label2]
cdq
idiv ECX
mov [label3], EAX
mov ECX, [label2]
imul ECX
jo overflow
mov [label4], EAX
mov EAX, [label1]
sub EAX, [label4]
mov [label4], EAX
push dword [label4]
call output
mov EBX, [label3]
mov [label1], EBX
mov EAX, [label1]
cmp EAX, 0
jg label5
mov EAX, 1
mov EBX, 0
int 80h
