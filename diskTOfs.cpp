#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
    char file_name[12], image_name[12];
    int numero_setores;
    int size;
    long long int primeiro_sector;
}copia;

int file_size(copia informacoes){
     
    ifstream in(informacoes.file_name, std::ios::binary);

    if (!in.is_open()) {
        std::cerr << "Erro na abertura do arquivo" << std::endl;
        return -1;
    }

    in.seekg(0, std::ios::end);
    std::streampos filesize = in.tellg();
    in.close(); 

    return filesize;
}

long long int primeiro_setor(copia informacoes){
    
    ifstream in(informacoes.image_name);
    ofstream out(informacoes.image_name);
    long long int bitmap, tamanho_bitmap, primeiro_sector;

    in.seekg(12, std::ios::beg);
    in >> bitmap;
    
    in.seekg(20, std::ios::beg);
    in >> tamanho_bitmap;
    
    in.seekg(bitmap, std::ios::beg);
    int aux;

    for (int i = 0; i < tamanho_bitmap; i++){
        if(i == 0)
            aux++;
        else
            aux = 0;
        if(aux == informacoes.numero_setores){
            aux = i;
            break;
        }else if (i == tamanho_bitmap){
            aux = -1;
        }
    }
    if(aux < 0){
        cout << "ERRO! NÃO EXISTE ESPAÇO EM MEMORIA" << endl;
        primeiro_sector = -1;
    }else{
        primeiro_sector = (aux-informacoes.numero_setores+1);
        out.seekp(bitmap+(512*primeiro_sector), std::ios::beg);
        for(int i = 0; i < informacoes.numero_setores; i++)
            out << 1;
    }

    in.close();
    return primeiro_sector;
}

bool rootdir(copia informacoes){

    ifstream in(informacoes.file_name);
    ofstream out(informacoes.image_name);
     
    short int temp;

    for (int i = 0; i < 128; i++){
        out.seekp(512+(i*32), std::ios::beg);
        in >> temp;
        if(temp == 0){
            out << informacoes.file_name;
            out << informacoes.primeiro_sector;
            out << informacoes.size;
            out << informacoes.numero_setores;
            temp = -1;
            break;
        }
    }
    if (temp == -1)
        return true;
    else 
        return false;
}

void escrita_fs(copia informacoes){

    ifstream in(informacoes.file_name);
    ofstream out(informacoes.image_name);

    informacoes.primeiro_sector = 4608 + (informacoes.primeiro_sector*512);
    out.seekp(informacoes.primeiro_sector, std::ios::beg);

    char k;

    for (int i = 0; i < informacoes.size; i++){
        in >> k;
        out << k;
    }

    cout << "SUAS INFORMAÇÕES FORAM GRAVADAS NO SISTEMA DE ARQUIVOS";

}

int main(){

    copia informacoes;

    cout << "Qual o nome do arquivo que você deseja copiar para o sistema de arquivos?" << endl;
    cin >> informacoes.file_name; 

    int size = file_size(informacoes);
    if (size == -1)
        return 0;

    cout << "Para qual imagem você deseja fazer a cópia?" << endl;
    cin >> informacoes.image_name; 

    informacoes.numero_setores = size/512;

    long long int primeiro_sector = primeiro_setor(informacoes);
    if (primeiro_sector < 0)
        return 0;

    rootdir(informacoes);
    escrita_fs(informacoes);
}