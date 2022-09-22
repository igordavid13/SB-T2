/*
op: vetor que guarda a ordem das operações
i: endereço do token no código objeto
j: endereço da operação
k: endereço da label

*/

#include <vector>

class operacao{       
  public:             
    int endereco;   // Endereço no código objeto
    //int arg;        // Quantidade de argmuntos
    string op;      // Tipo de operação
};




vector<operacao> instrucao; // Declarar na main
vector<int> label, space;   // Vetor label carrega os endereços dos tokens que foram referenciados no código objeto
                            // Vetor space carrega os endereços dos chamados 

int j=0, k=0;


while (input[i]!=14){
    switch(input[i]) { // Aqui deve entrar um token. A priori, sempre vai ser um opcode
        case 01:
        instrucao.op[j] = "ADD"; // Vetor que carrega as operações
        instrucao.endereco = i;
        j++;      

        label[k] = input[i+1]; // Adiciona o endereço do token que foi referenciado no space
        k++;

        break;

        case 02:
        instrucao.op[j] ="SUB";
        instrucao.endereco = i;
        j++;

        label[k] = input[i+1];
        k++;

        break;

        case 03:
        instrucao.op[j] ="MUL";
        instrucao.endereco = i;
        j++;

        label[k] = input[i+1];
        k++;

        break;

        case 04:
        instrucao.op[j] = "DIV";
        instrucao.endereco = i;
        j++;
        label[k] = input[i+1];
        k++;
        break;

        case 05:
        instrucao.op[j] = "JMP";
        instrucao.endereco = i;
        j++;

        break;

        case 06:
        instrucao.op[j] = "JMPN" ;
        instrucao.endereco = i;
        j++;

        break;

        case 07:
        instrucao.op[j] = "JMPP";
        instrucao.endereco = i;
        j++;

        break;

        case 08:
        instrucao.op[j] = "JMPZ";
        instrucao.endereco = i;
        j++;

        break;

        case 09:
        instrucao.op[j] = "COPY";
        instrucao.endereco = i;
        j++;

        break;

        case 10:
        instrucao.op[j] = "LOAD";
        instrucao.endereco = i;
        j++;

        break;

        case 11:
        instrucao.op[j] = "STORE";
        instrucao.endereco = i;
        j++;

        break;

        case 12:
        instrucao.op[j] = "INPUT";
        instrucao.endereco = i;
        j++;
        label[k] = input[i+1];
        k++;
        break;

        case 13:
        instrucao.op[j] = "OUTPUT";
        instrucao.endereco = i;
        j++;
        label[k] = input[i+1];
        k++;
        break;

        case 15:
        instrucao.op[j] = "S_INPUT";
        instrucao.endereco = i;
        j++;
        label[k] = input[i+1];
        label[k+1] = i+2;
        k+=2;
        break;

        case 16:
        instrucao.op[j] = "S_OUTPUT";
        instrucao.endereco = i;
        j++;

        break;
    }
    // Depois do switch, deve andar no arquivo para servir de input novamente.
}

instrucao.op[j] = "STOP"
        instrucao.endereco = i;
// Após isso, deve adicionar cada token no vetor space

k=0; // Aproveitando o contador para outro vetor
while(){            // Esse while deve continuar a adicionar os endereços dos tokens até terminar o arquivo objeto
    space[k] = i;
}


/*
DUVIDAS:
- Qual argumento em jumps?

*/


#include <fstream>
ofstream fileout;

fileOut.open("output.txt"); // Cria o arquivo e 


fileOut << ".DATA" << endl;


fileOut << ".CODE" << endl;

switch(opcode) {
    case :  // ADD
        fileOut << "    mov EAX, " << OP1 << endl;  // EAX = memória de OP1
        fileOut << "    add EAX, " << OP2 << endl;  // EAX = EAX + memória de OP2
        fileOut << "    mov [acc], EAX" << endl;
        fileOut << endl;
        break;
    case :  // SUB
        fileOut << "    mov EAX, " << OP1 << endl;  // EAX = memória de OP1
        fileOut << "    sub EAX, " << OP2 << endl;  // EAX = EAX - memória de OP2
        fileOut << "    mov [acc], EAX" << endl;
        fileOut << endl;
        break;
    case :  // MUL
    // Primeiro deve verificar overflow. Se tiver, o programa deve parar.
    // Como o sinal deve ser considerado, a operação de saída é "imul"
        fileOut << "    mov EAX, " << OP1 << endl;  // Passa o primeiro parâmetro para o acumulador
        fileOut << "    mov EBX, " << OP2 << endl;  // Passa o segundo parâmetro para BX
        fileOut << "    imul EBX" << endl;  // Multiplica o conteúdo do acumulador EAX com o conteúdo de EBX e guarda no acumulador
        fileOut << "    mov [acc], eax" << endl;
        fileOut << endl;
        break;
    case :  // DIV
        fileOut << "  mov EDX, 0" << endl;
        fileOut << "  mov EBX, [" << tokenFound->second << "]" << endl;
        fileOut << "  idiv EBX" << endl;
        fileOut << "  mov [acc], eax" << endl;
        fileOut << endl;
        break;
    case :  // JMP
        fileOut << "  ; JMP " << tokenFound->second << endl;
        fileOut << "  jmp " << tokenFound->second << endl;
        fileOut << endl;
        i++;
        break;
    case :  // JMPN
        
        fileOut << "  ; JMPN " << tokenFound->second << endl;
        fileOut << "  cmp dword [acc], 0" << endl;
        fileOut << "  jl " << tokenFound->second << endl;
        fileOut << endl;
        i++;
        break;
    case :  // JMPP
        fileOut << "  ; JMPP " << tokenFound->second << endl;
        fileOut << "  cmp dword [acc], 0" << endl;
        fileOut << "  jg " << tokenFound->second << endl;
        fileOut << endl;
        i++;
        break;
    case :  // JMPZ
        fileOut << "  ; JMPZ " << tokenFound->second << endl;
        fileOut << "  cmp dword [acc], 0" << endl;
        fileOut << "  je " << tokenFound->second << endl;
        fileOut << endl;
        i++;
        break;
    case :  // COPY
        cond << endl;
        fileOut << "  mov eax, [" << temp << "]" << endl;
        fileOut << "  mov [" << tokenFound->second << "], eax" << endl;
        fileOut << endl;
        i += 2;
        break;
    case :  // LOAD
        fileOut << "  mov eax, [" << tokenFound->second << "]" << endl;
        fileOut << "  mov [acc], eax" << endl;
        fileOut << endl;
        i++;
        break;
    case :  // STORE
        fileOut << "  ; STORE " << tokenFound->second << endl;
        fileOut << "  mov eax, [acc]" << endl;
        fileOut << "  mov [" << tokenFound->second << "], eax" << endl;
        fileOut << endl;
        i++;
        break;
    case :  // INPUT
        fileOut << "  ; INPUT " << tokenFound->second << endl;
        fileOut << "  push dword " << tokenFound->second << endl;
        fileOut << "  push dword num_aux" << endl;
        fileOut << "  call input_call" << endl;
        fileOut << "  add esp, 8" << endl;
        fileOut << endl;
        i++;
        break;
    case :  // OUTPUT
        fileOut << "  ; OUTPUT " << tokenFound->second << endl;
        fileOut << "  push dword " << tokenFound->second << endl;
        fileOut << "  push dword 13" << endl;
        fileOut << "  call output_call" << endl;
        fileOut << "  add esp, 8" << endl;
        fileOut << endl;
        i++;
        break;
    case :  // STOP
        fileOut << "  ; STOP" << endl;
        fileOut << "  mov eax, 1" << endl;
        fileOut << "  mov ebx, 0" << endl;
        fileOut << "  int 80h" << endl;
        fileOut << endl;
        isInSectionText = false;
        break;
    case :  // S_INPUT
        fileOut << ", " << tokenFound->second << endl;
        fileOut << "  push dword " << temp << endl;
        fileOut << "  push dword [" << tokenFound->second << "]" << endl;
        fileOut << "  call s_input_call" << endl;
        fileOut << "  add esp, 8" << endl;
        fileOut << endl;
        break;
    case :  // S_OUTPUT
        fileOut << ", " << tokenFound->second << endl;
        fileOut << "  push dword " << temp << endl;
        fileOut << "  push dword [" << tokenFound->second << "]" << endl;
        fileOut << "  call s_output_call" << endl;
        fileOut << "  add esp, 8" << endl;
        fileOut << endl;
        break;
}

