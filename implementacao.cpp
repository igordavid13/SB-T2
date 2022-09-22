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
    bool ok1,ok2;
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
                    cout << ";" <<endl;
                    vetor = false;
                    //cout<<"vetor"<<vetor<<endl; 
                    break;
                }
            }
            if (vetor == true) cout << "," << numbers[i];
        }    
        if(vetor == false){
            for(int j=0; j < vetores.size();j++){
                if (i == vetores[j]){  
                vetor = true;
                //cout<<"vetor"<<vetor<<endl; 
                cout << "VETOR : " << numbers[i];
                } 
            }
            //cout<<numbers[i]<<endl; 
            if(vetor == false){           
                if(numbers[i] == 0)
                        cout << "variavel sem valor definido"<< endl;
                else cout << "constante" << endl;;    
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

    
    for(int i = 0; i < table.size() ; i++){
        cout << "OPCODE = " << table[i].opcode << endl;
        if(table[i].op1 != -1)
        cout << "OP1 = " << table[i].op1 << endl;
        if(table[i].op2 != -1)
        cout << "OP2 = " << table[i].op2 << endl;
    }




}