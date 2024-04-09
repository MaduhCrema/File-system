#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include <math.h>

int file_size(char file_name[12]){
     
    std::ifstream file(file_name, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Erro na abertura do arquivo" << std::endl;
        return -1;
    }

    file.seekg(0, std::ios::end);
    std::streampos filesize = file.tellg();
    file.close(); 

    return filesize;
}

int main(){

    char file_name[12], k;
    int rootdir = 512;

    cout << "Qual o nome do arquivo que você deseja tranferir para o sistema de arquivos?" << endl;
    cin >> file_name; 

    int size = file_size(file_name);
    if (size == -1)
        return 0;



    // ifstream in(file_name);

    // while (in >> k && k != 0) {
    
    // }
}