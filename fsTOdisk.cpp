#include <cmath> 
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct {
    char file_name[12], image_name[15];
    int numero_setores;
    int size;
    long long int primeiro_sector;
    int entrada_diretorio;
    long long int bitmap;
}copia;

copia localiza_arquivo_fs(copia informacoes){

    char file_SA[12];

    ifstream in(informacoes.image_name);
    in.seekg(512, std::ios::beg);

    for (int i = 0; i < 128; i++){

        in.seekg(512+(i*32), std::ios::beg);
        in.read(file_SA, 12);
        int resultado = strcmp(file_SA, informacoes.file_name);

        if (resultado == 0){
            
            informacoes.entrada_diretorio = i;
            cout << "informacoes.entrada_diretorio " << informacoes.entrada_diretorio << endl;

            in.seekg(512+(i*32)+12, std::ios::beg);
            in >> informacoes.primeiro_sector;
            cout << "informacoes.primeiro_sector " << informacoes.primeiro_sector << endl;

            in.seekg(512+(i*32)+20, std::ios::beg);
            in >> informacoes.size;
            cout << "informacoes.size: " << informacoes.size << endl;

            break;
        }

        if (i == 127){
            cout << endl << "NÃO FOI POSSÍVEL ENCONTRAR SEU ARQUIVO" << endl;
            informacoes.primeiro_sector = -1;
        }
    }
            return informacoes;
}

void escrita_em_disco(copia informacoes){

    ifstream in(informacoes.image_name);
    std::ofstream out(informacoes.file_name);

    in.seekg(4608+(512*informacoes.primeiro_sector), std::ios::beg);

    char k;
    for (int i = 0; i < 17; i++){
        in.get(k);
        out << k;
    }

    cout << "SUAS INFORMAÇÕES FORAM GRAVADAS NO SISTEMA DE ARQUIVOS";
}

int main(){
    copia informacoes;
        cout << endl << "Qual o nome do arquivo que você deseja copiar para o disco?" << endl << endl;
        cin >> informacoes.file_name; 

        cout << endl << "Em que imagem este arquivo está localizado?" << endl << endl;
        cin >> informacoes.image_name; 

        informacoes = localiza_arquivo_fs(informacoes);
        if (informacoes.primeiro_sector == -1)
            return 0;
        
       //escrita_em_disco(informacoes);
        return 0;
}