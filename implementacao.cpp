#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


typedef struct gramatica{

int opcode;
int op1;
int op2;

}gramatica;

void leitura(char* arquivo){
    ifstream ifile(arquivo);
    string line;
    int num;
    bool ok;
    vector<int> numbers;
    vector<int> vetores;
    vector<int> percorridos;
    vector<gramatica> table;
    gramatica exemple;
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
        if(table[i].opcode == 15 || table[i].opcode == 16){
            vetores.push_back(table[i].op1);
            vetores.push_back(table[i].op2);

            cout<<"VETOR AQUI COMECO: "<< numbers[table[i].op1] <<" final: "<<  numbers[table[i].op1 + table[i].op2 -1] <<endl;
        }
    }

    for(int i = 0; i <vetores.size();i++){
        percorridos.push_back(vetores[i]);
        i++;
        while(vetores[i]>0){
            vetores[i]--;
            percorridos.push_back(vetores[(i-1)]+vetores[i]);
            
        }

    }
    for(int i = variables_begin; i < numbers.size(); i++){
        ok = true;
        for(int j=0; j < percorridos.size();j++){
            if(i == percorridos [j]){
                ok = false;
                break;
            } 
        }
        if(ok == true){
            if (numbers[i] == 0)
                cout << "variavel sem valor definido"<< endl;
            else cout << "constante" << endl;;    
        }

    }





    for(int i = 0; i < numbers.size() ; i++){
        cout << numbers[i] << " ";
    }
    cout<< endl;


    
    // for(int i = 0; i < table.size() ; i++){
    //     cout << "OPCODE = " << table[i].opcode << endl;
    //     if(table[i].op1 != -1)
    //     cout << "OP1 = " << table[i].op1 << endl;
    //     if(table[i].op2 != -1)
    //     cout << "OP2 = " << table[i].op2 << endl;
    // }




}