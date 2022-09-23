#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
// 12 29 10 29 4 28 11 30 3 28 11 31 10 29 2 31 11 31 13 31 9 30 29 10 29 7 4 15 35 38 14 2 0 0 0 23 24 25 0

typedef struct gramatica{

int opcode;
int op1;
int op2;

}gramatica;

typedef struct dados{

string label;
int posicao;
int tipo;
vector<int> valor;
}dados;


void leitura(char* arquivo){
    ifstream ifile(arquivo);
    ofstream fileout;
    string line;
    int num;
    bool ok1,ok2;
    vector<int> numbers;
    vector<int> vetores;
    vector<int> percorridos;
    vector<gramatica> table;
    gramatica exemple;
    vector<dados> tipo_dados;
    dados exemple_dados;
    int variables_begin;
    
    
    if(!ifile.is_open()){
        cout << "ERRO" << endl;
        exit(0);
    
    }else{
        getline(ifile, line);          
    }
    //ifile.close();

    stringstream lineStream(line);
    while (lineStream >> num) numbers.push_back(num);

    
    
    
    for(int i = 0; i < numbers.size() ; i++){
        exemple.opcode = -1;
        exemple.op1 = -1;
        exemple.op2 = -1;
        exemple.opcode = numbers[i];
        if(numbers[i] == 14) {
            table.push_back(exemple);
            variables_begin = i + 1;
            break; 
        }    
            
        i++;
        exemple.op1 = numbers[i];
        if(numbers[i-1] == 9 || numbers[i-1] == 16 || numbers[i-1] == 15){

            i++;
            exemple.op2 = numbers[i];
        
        }
        table.push_back(exemple);
        

    }

    for(int i = 0; i < table.size() ; i++){
        ok1 = true;
        ok2 = true;
        if(table[i].op1 == -1) ok1 = false;
        if(table[i].op2 == -1) ok2 = false;
        for(int j = 0; j < percorridos.size(); j++){
            //cout << i<<" : " << table[i].op2 <<endl;            
           if(table[i].op1 == percorridos[j]) ok1 = false;  
           if(table[i].op2 == percorridos[j]) ok2 = false;
        }
        if (ok1 == true){ 
            //cout << i<<" : " << table[i].op1 <<endl;
            percorridos.push_back(table[i].op1);
        }
        if (ok2 == true){ 
            //cout << i<<" : " << table[i].op2 <<endl;
            percorridos.push_back(table[i].op2);
        }       
    }

    

    for(int i = 0; i < table.size() ; i++){ // CONFERE SE TEM VETORES A SEREM DECLARADOS NO .DATA
        if(table[i].opcode == 15 || table[i].opcode == 16){
            vetores.push_back(table[i].op1);
        }
    }

    
    bool vetor = false;
    for(int i = variables_begin; i < numbers.size(); i++){
        if(vetor == true){
            //cout<<"aki"<<endl;
            for(int k = 0; k < percorridos.size();k++){
                if(i == percorridos[k]) {
                    
                    //cout<<"  "<< k << "  "<< percorridos[k]<< "  "<<endl;
                    tipo_dados.push_back(exemple_dados);
                    exemple_dados = {};
                    vetor = false;
                    //cout<<"vetor"<<vetor<<endl; 
                    break;
                }
            }
            if (vetor == true) exemple_dados.valor.push_back(numbers[i]);;
        }    
        if(vetor == false){
            for(int j=0; j < vetores.size();j++){
                if (i == vetores[j]){  
                vetor = true;                
                exemple_dados.posicao = i;
                exemple_dados.label = "label_" + to_string(tipo_dados.size());
                exemple_dados.tipo = 2;
                exemple_dados.valor.push_back(numbers[i]);    
                //cout << "VETOR : " << numbers[i];
                } 
            }
            //cout<<numbers[i]<<endl; 
            if(vetor == false){           
                if(numbers[i] == 0){
                    exemple_dados.posicao = i;
                    exemple_dados.label = "label_" + to_string(tipo_dados.size());
                    exemple_dados.tipo = 0;
                    exemple_dados.valor.push_back(numbers[i]);
                    tipo_dados.push_back(exemple_dados);
                    exemple_dados = {};
                    //cout << "variavel sem valor definido"<< endl;
                }    
                else{
                    exemple_dados.posicao = i;
                    exemple_dados.label = "label_" + to_string(tipo_dados.size());
                    exemple_dados.tipo = 1;
                    exemple_dados.valor.push_back(numbers[i]);
                    tipo_dados.push_back(exemple_dados);  
                    exemple_dados = {};                   
                    //cout << "constante" << endl;
                }   
            }
        }
    }    






    // for(int i = 0; i < numbers.size() ; i++){
    //     cout << numbers[i] << " ";
    // }
    // cout<< endl;


    // for(int i = 0; i < vetores.size() ; i++){
    //     cout << vetores[i] << " ";
    // }
    // cout<< endl;


    // for(int i = 0; i < percorridos.size() ; i++){
    //     cout << percorridos[i] << " ";
    // }
    // cout<< endl;

    
    // for(int i = 0; i < table.size() ; i++){
    //     cout << "OPCODE = " << table[i].opcode << endl;
    //     if(table[i].op1 != -1)
    //     cout << "OP1 = " << table[i].op1 << endl;
    //     if(table[i].op2 != -1)
    //     cout << "OP2 = " << table[i].op2 << endl;
    // }

    // for(int i = 0; i < tipo_dados.size() ; i++){
    //     cout << "label = " << tipo_dados[i].label << endl;
    //     cout << "posicao = " << tipo_dados[i].posicao << endl;
    //     cout << "tipo = " << tipo_dados[i].tipo << endl;
    //     for(int j=0; j<(tipo_dados[i].valor).size();j++){
    //     cout << "valor = " << tipo_dados[i].valor[j] << endl;
    //     }
    //     cout<<endl;
    // }




    fileout.open("output.txt");

    fileout << "ok_overflow:" << endl;
    fileout << "  push dword msg"  << endl;
    fileout << "  push dword [msg_size]" << endl;
    fileout << "  call s_output_call" << endl;
    fileout << "  add esp, 8" << endl;
    fileout << "  mov EAX, 1" << endl;
    fileout << "  mov EBX, 0" << endl;
    fileout << "  int 80h" << endl << endl;
    fileout << endl;

    fileout << "s_input:" << endl;
    fileout << "  push ebp" << endl;
    fileout << "  mov ebp, esp" << endl;
    fileout << "  mov eax, 3" << endl;
    fileout << "  mov ebx, 0" << endl;
    fileout << "  mov ecx, [ebp + 12]" << endl;
    fileout << "  mov edx, [ebp + 8]" << endl;
    fileout << "  int 80h" << endl;
    fileout << "  pop ebp" << endl;
    fileout << "  ret" << endl;

    fileout << "s_output:" << endl;
    fileout << "  push ebp" << endl;
    fileout << "  mov ebp, esp" << endl;
    fileout << "  mov eax, 4" << endl;
    fileout << "  mov ebx, 1" << endl;
    fileout << "  mov ecx, [ebp + 12]" << endl;
    fileout << "  mov edx, [ebp + 8]" << endl;
    fileout << "  int 80h" << endl;
    fileout << "  pop ebp" << endl;
    fileout << "  ret" << endl;
    fileout << endl;


    fileout << "output:" << endl;
    /*Implementar*/
    fileout << endl;

    fileout << "input:" << endl;
    /*Implementar*/
    fileout << endl;

    fileout << "section .data" << endl << endl;

    fileout << "msg db 'DEU OVERFLOW,OdH,0aH'" << endl;
    fileout << "msg_size EQU $-msg" << endl;


    for(int i = 0; i < tipo_dados.size() ; i++){
        if(tipo_dados[i].tipo == 1){
            fileout << tipo_dados[i].label;
            fileout << " dd "; 
            fileout << tipo_dados[i].valor[0];
            fileout << endl;
        }
        if(tipo_dados[i].tipo == 2){
            fileout << tipo_dados[i].label; 
            fileout << " dd "; 
            for(int j = 0; j < tipo_dados[i].valor.size(); j++){ 
                fileout << (tipo_dados[i].valor[j]);
                if(j+1 != tipo_dados[i].valor.size())
                fileout << ", ";
            }
            fileout << ";" <<endl;
        }
    }

    fileout <<endl;
    fileout << "section .bss" << endl << endl;

    for(int i = 0; i < tipo_dados.size() ; i++){
        if(tipo_dados[i].tipo == 0){
            fileout << tipo_dados[i].label; 
            fileout << " resd 1" << endl; 
        }

    }

    fileout <<endl;
    fileout << "section .text" << endl << endl;
    fileout << "global _start:" << endl << endl;
    fileout << "_start:" << endl;

    for(int i = 0; i < table.size() ; i++){
        string label_op1, label_op2;

        for(int j = 0; j < tipo_dados.size() ; j++){
            if(tipo_dados[j].posicao == table[i].op1)
                label_op1 = tipo_dados[j].label;
            if(tipo_dados[j].posicao == table[i].op2)    
                label_op2 = tipo_dados[j].label;
            

        }



        switch(table[i].opcode) {
        case 1:  // ADD
            fileout << "    mov EBX, [" << label_op1 << "]"<< endl; 
            fileout << "    add [EAX], EBX" << endl;  
            fileout << endl;
            i++;
            break;
        case 2:  // SUB
            fileout << "    mov EBX, [" << label_op1 << "]" << endl;  
            fileout << "    sub [EAX], EBX" << endl;  
            fileout << endl;
            i++;
            break;
        case 3:  // MUL
        // Primeiro deve verificar overflow. Se tiver, o programa deve parar.
        // Como o sinal deve ser considerado, a operação de saída é "imul"


        // MULT X ; 
            fileout << "    mov EBX, [" << label_op1 <<"]" << endl; // EBX = Dado de OP
            fileout << "    imul dword EBX" << endl;         
            fileout << "    jo ok_overflow" << endl;              // Pula para a função que verifica overflow
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
            fileout << "    cdq" << endl;               // Extensão de sinal
            fileout << "    mov EBX, [" << label_op1 <<"]" << endl;      // EBX recebe OP1
            fileout << "    idiv EBX" << endl;          // EBX = ACC/OP
            i++;
            break;
        case 5:  // JMP
            fileout << "    jmp " << label_op1 << endl ;  // Jump para o rótulo que tem o endereço OP
            i++;
            break;
        case 6:  // JMPN
            fileout << "    cmp dword [EAX], 0" << endl;
            fileout << "    jl " << label_op1 << endl << endl; // Jump para o rótulo que tem o endereço OP, se ACC < 0
            i++;
            break;
        case 7:  // JMPP
            fileout << "    cmp dword [EAX], 0" << endl; 
            fileout << "    jg " << label_op1 << endl << endl; // Jump para o rótulo que tem o endereço OP, se ACC > 0
            i++;
            break;
        case 8:  // JMPZ
            fileout << "    cmp dword [EAX], 0" << endl;
            fileout << "    je " << label_op1 << endl << endl; // Jump para o rótulo que tem o endereço OP,  se ACC = 0
            i++;
            break;
        case 9:  // COPY
            fileout << "    mov EBX, [" << label_op1 << "]" << endl;          // EBX = mem(OP1)
            fileout << "    mov [" << label_op2 << "], EBX" << endl;  // mem(OP2) = EBX
            i += 2;
            break;
        case 10:  // LOAD
            fileout << "    mov [EAX], "<< label_op1 << endl; // ACC = dado no endereço OP
            i++;
            break;
        case 11:  // STORE
            fileout << "    mov "<< label_op1 << ", [EAX]" << endl; // endereço OP recebe ACC
            i++;
            break;

    
        case 12:  // INPUT mem(OP) = entrada
            fileout << "    push dword " << label_op1 << endl;
            fileout << "    push dword num_aux" << endl;
            fileout << "    call input" << endl;
            fileout << "    add esp, 8" << endl;
            i++;
            break;
        case 13:  // OUTPUT saída = mem(OP)
            fileout << "  ; OUTPUT " << label_op1 << endl;
            fileout << "    push dword " << label_op1 << endl;
            fileout << "    push dword 13" << endl;
            fileout << "    call output" << endl;
            fileout << "    add esp, 8" << endl;
            i++;
            break;
        case 14:  // STOP
            fileout << "    mov EAX, 1" << endl;
            fileout << "    mov EBX, 0" << endl;
            fileout << "    int 80h" << endl;
            break;
        case 15:  // S_INPUT
            fileout << "  push dword " << label_op1 << endl;
            fileout << "  push dword [" << label_op2 << "]" << endl;
            fileout << "  call s_input" << endl;
            fileout << "  add esp, 8" << endl;
            fileout << endl;

            break;
        case 16:  // S_OUTPUT
            fileout << "  push dword " << label_op1 << endl;
            fileout << "  push dword [" << label_op2 << "]" << endl;
            fileout << "  call s_output" << endl;
            fileout << "  add esp, 8" << endl;
            fileout << endl;


            break;
    

        }
    }    

    fileout.close();



}