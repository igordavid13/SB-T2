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
                cout << "VETOR : " << numbers[i];
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
                    cout << "variavel sem valor definido"<< endl;
                }    
                else{
                    exemple_dados.posicao = i;
                    exemple_dados.label = "label_" + to_string(tipo_dados.size());
                    exemple_dados.tipo = 1;
                    exemple_dados.valor.push_back(numbers[i]);
                    tipo_dados.push_back(exemple_dados);  
                    exemple_dados = {};                   
                    cout << "constante" << endl;
                }   
            }
        }
    }    






    for(int i = 0; i < numbers.size() ; i++){
        cout << numbers[i] << " ";
    }
    cout<< endl;


    for(int i = 0; i < vetores.size() ; i++){
        cout << vetores[i] << " ";
    }
    cout<< endl;


    for(int i = 0; i < percorridos.size() ; i++){
        cout << percorridos[i] << " ";
    }
    cout<< endl;

    
    // for(int i = 0; i < table.size() ; i++){
    //     cout << "OPCODE = " << table[i].opcode << endl;
    //     if(table[i].op1 != -1)
    //     cout << "OP1 = " << table[i].op1 << endl;
    //     if(table[i].op2 != -1)
    //     cout << "OP2 = " << table[i].op2 << endl;
    // }

    for(int i = 0; i < tipo_dados.size() ; i++){
        cout << "label = " << tipo_dados[i].label << endl;
        cout << "posicao = " << tipo_dados[i].posicao << endl;
        cout << "tipo = " << tipo_dados[i].tipo << endl;
        for(int j=0; j<(tipo_dados[i].valor).size();j++){
        cout << "valor = " << tipo_dados[i].valor[j] << endl;
        }
        cout<<endl;
    }




    fileout.open("output.txt"); 

    fileout << "section .data" << endl << endl;

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
            fileout << " resd 1;" << endl; 
        }

    }



    fileout.close();



}