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

    char file_name[12], k, image_name[12];
    int rootdir = 512;

    cout << "Qual o nome do arquivo que você deseja copiar para o sistema de arquivos?" << endl;
    cin >> file_name; 

    int size = file_size(file_name);
    if (size == -1)
        return 0;

    cout << "Para qual imagem você deseja fazer a cópia?" << endl;
    cin >> image_name; 

    ifstream in(file_name);
    ofstream out(image_name);

    out.seekp(rootdir, std::ios::beg);

    for (int i = 0; i < size; i++){
        in >> k;
        out << k;
    }
}