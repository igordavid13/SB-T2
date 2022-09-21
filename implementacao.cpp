#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;


void leitura(char* arquivo){
    ifstream ifile(arquivo);
    string line;
    int num;
    vector<int> numbers;

    if(!ifile.is_open()){
        cout << "ERRO" << endl;
        exit(0);
    
    }else{
        getline(ifile, line);          
    }
    ifile.close();

    stringstream lineStream(line);
    while (lineStream >> num) numbers.push_back(num);


    

    for(int i = 0; i<numbers.size(); i++){
        cout<<numbers[i]<< " ";
    }

}