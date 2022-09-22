#include <fstream>
ofstream fileout;

fileOut.open("output.txt"); // Cria o arquivo e 


fileOut << "section .DATA" << endl << endl;

fileOut << "section .bss" << endl << endl;


fileOut << "section .TEXT" << endl << endl;
fileOut << "global _START:" << endl << endl;
fileOut << "_START:" << endl;

// ACC é um nome genérico para o nosso acumulador

switch(table[i].opcode) {
    case 1:  // ADD
        fileOut << "    mov EAX, " << OP1 << endl;  // EAX = dado de OP
        fileOut << "    add [ACC], EAX" << endl;  // ACC = ACC + OP
        fileOut << endl;
        i++;
        break;
    case 2:  // SUB
        fileOut << "    mov EAX, " << OP1 << endl;  // EAX = dado de OP
        fileOut << "    sub [ACC], EAX" << endl;  // ACC = ACC - OP
        fileOut << endl;
        i++;
        break;
    case 3:  // MUL
    // Primeiro deve verificar overflow. Se tiver, o programa deve parar.
    // Como o sinal deve ser considerado, a operação de saída é "imul"

    // MULT X ; 
        fileOut << "    mov EAX, [ACC]" << endl;   // Passa o ACC para EAX
        fileOut << "    mov EBX, " << OP1 << endl; // EBX = Dado de OP
        fileOut << "    imul EBX" << endl;         // EBX=ACC*OP
        fileout << "    jo overflow";              // Pula para a função que verifica overflow
        fileOut << "    mov [ACC], eax" << endl;   // ACC=ACC*OP, como no assembly inventado
        fileOut << endl;
        i++;
        break;
    case 4:  // DIV
    /* EXEMPLO
    .DATA
    dword_val SDWORD -50000
    .CODE
    mov eax, dword_val ; dividend, low
    cdq                ; sign-extend EAX into EDX
    mov ebx, 256       ; divisor
    idiv ebx           ; quotient EAX = -195, remainder EDX = -80
    */
        fileOut << "    mov EAX, [ACC]"<< endl;     // EAX recebe ACC
        fileOut << "    cdq" << endl;               // Extensão de sinal
        fileOut << "    mov EBX, OP1" << endl;      // EBX recebe OP
        fileOut << "    idiv EBX" << endl;          // EBX = ACC/OP
        fileOut << "    mov [ACC], EBX" << endl;    // ACC = ACC/OP, como no assembly inventado
        fileOut << endl;
        i++;
        break;
    case 5:  // JMP
        fileOut << "    jmp " << OP << endl << endl;  // Jump para o rótulo que tem o endereço OP
        i++;
        break;
    case 6:  // JMPN
        fileOut << "    cmp dword [ACC], 0" << endl;
        fileOut << "    jl " << OP << endl << endl; // Jump para o rótulo que tem o endereço OP, se ACC < 0
        i++;
        break;
    case 7:  // JMPP
        fileOut << "    cmp dword [ACC], 0" << endl; 
        fileOut << "    jg " << OP << endl << endl; // Jump para o rótulo que tem o endereço OP, se ACC > 0
        i++;
        break;
    case 8:  // JMPZ
        fileOut << "    cmp dword [ACC], 0" << endl;
        fileOut << "    je " << OP << endl << endl; // Jump para o rótulo que tem o endereço OP,  se ACC = 0
        i++;
        break;
    case 9:  // COPY
        fileOut << "    mov EAX, [" << OP1 << "]" << endl;          // EAX = mem(OP1)
        fileOut << "    mov [" << OP2 << "], eax" << endl << endl;  // mem(OP2) = EAX
        i += 2;
        break;
    case 10:  // LOAD
        fileOut << "    mov [ACC], "<< OP << endl << endl; // ACC = dado no endereço OP
        i++;
        break;
    case 11:  // STORE
        fileOut << "    mov "<< OP << ", [ACC]" << endl << endl; // endereço OP recebe ACC
        i++;
        break;
    /*
    case 12:  // INPUT mem(OP) = entrada
        fileOut << "    push dword " << OP << endl;
        fileOut << "    push dword num_aux" << endl;
        fileOut << "    call input_call" << endl;
        fileOut << "    add esp, 8" << endl << endl;
        i++;
        break;
    case 13:  // OUTPUT saída = mem(OP)
        fileOut << "  ; OUTPUT " << OP << endl;
        fileOut << "    push dword " << OP << endl;
        fileOut << "    push dword 13" << endl;
        fileOut << "    call output_call" << endl;
        fileOut << "    add esp, 8" << endl << endl;
        i++;
        break;
    case 14:  // STOP
        fileOut << "  ; STOP" << endl;
        fileOut << "    mov EAX, 1" << endl;
        fileOut << "    mov EBX, 0" << endl;
        fileOut << "    int 80h" << endl << endl;
        isInSectionText = false;
        break;
    case 15:  // S_INPUT
        fileOut << ", " << tokenFound->second << endl;
        fileOut << "  push dword " << temp << endl;
        fileOut << "  push dword [" << tokenFound->second << "]" << endl;
        fileOut << "  call s_input_call" << endl;
        fileOut << "  add esp, 8" << endl << endl;
        break;
    case 16:  // S_OUTPUT
        fileOut << ", " << tokenFound->second << endl;
        fileOut << "  push dword " << temp << endl;
        fileOut << "  push dword [" << tokenFound->second << "]" << endl;
        fileOut << "  call s_output_call" << endl;
        fileOut << "  add esp, 8" << endl << endl;
        break;
    */

}



/*
  fileOut << "output_call:" << endl;
  fileOut << "  push ebp" << endl;
  fileOut << "  mov ebp, esp" << endl;
  fileOut << "  mov eax, 4" << endl;
  fileOut << "  mov ebx, 1" << endl;
  fileOut << "  mov ecx, [ebp + 12]" << endl;
  fileOut << "  mov edx, [ebp + 8]" << endl;
  fileOut << "  int 80h" << endl;
  fileOut << "  pop ebp" << endl;
  fileOut << "  ret" << endl;
  fileOut << endl;

  fileOut << "input_call:" << endl;
  fileOut << "  push ebp" << endl;
  fileOut << "  mov ebp, esp" << endl;
  fileOut << "  mov eax, 3" << endl;
  fileOut << "  mov ebx, 0" << endl;
  fileOut << "  mov ecx, [ebp + 8]" << endl;
  fileOut << "  mov edx, 13" << endl;
  fileOut << "  int 80h" << endl;
  fileOut << "  mov ebx, dword [ebp + 12]" << endl;
  fileOut << "  mov ebp, 0" << endl;
  fileOut << "  mov edx, 10" << endl;
  fileOut << " input_loop:" << endl;
  fileOut << "  cmp byte [ecx], 10" << endl;
  fileOut << "  je bye_input" << endl;
  fileOut << "  mov eax, ebp" << endl;
  fileOut << "  imul edx" << endl;
  fileOut << "  mov ebp, eax" << endl;
  fileOut << "  mov edx, [ecx]" << endl;
  fileOut << "  and edx, 255" << endl;
  fileOut << "  add ebp, edx" << endl;
  fileOut << "  mov edx, 10" << endl;
  fileOut << "  sub ebp, 48" << endl;
  fileOut << "  add ecx, 1" << endl;
  fileOut << "  jmp input_loop" << endl;
  fileOut << " bye_input:" << endl;
  fileOut << "  mov dword [ebx], ebp" << endl;
  fileOut << "  pop ebp" << endl;
  fileOut << "  ret" << endl;
  fileOut << endl;

  fileOut << "s_output_call:" << endl;
  fileOut << "  push ebp" << endl;
  fileOut << "  mov ebp, esp" << endl;
  fileOut << "  mov eax, 4" << endl;
  fileOut << "  mov ebx, 1" << endl;
  fileOut << "  mov ecx, [ebp + 12]" << endl;
  fileOut << "  mov edx, [ebp + 8]" << endl;
  fileOut << "  int 80h" << endl;
  fileOut << "  pop ebp" << endl;
  fileOut << "  ret" << endl;
  fileOut << endl;
  fileOut << "s_input_call:" << endl;
  fileOut << "  push ebp" << endl;
  fileOut << "  mov ebp, esp" << endl;
  fileOut << "  mov eax, 3" << endl;
  fileOut << "  mov ebx, 0" << endl;
  fileOut << "  mov ecx, [ebp + 12]" << endl;
  fileOut << "  mov edx, [ebp + 8]" << endl;
  fileOut << "  int 80h" << endl;
  fileOut << "  pop ebp" << endl;
  fileOut << "  ret" << endl;

  fileOut.close();
*/

fileOut.close(); // Fecha o arquivo