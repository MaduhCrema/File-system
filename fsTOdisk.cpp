#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

typedef struct {
    char file_name[12], image_name[12];
    int size;
    long long int primeiro_sector;
    int entrada_diretorio;
}copia;

// 3. se existir, ir até primeiro cluster
// 4. criar arquivo no disco rigido
// 5. passas as informações

int main(){

    copia informacoes;
    char file_SA[12];
   
    cout << "Qual o nome do arquivo que você deseja copiar para o sistema de arquivos?" << endl;
    cin >> informacoes.file_name; 

    cout << "Em que imagem este arquivo está localizado?" << endl;
    cin >> informacoes.image_name; 

    ifstream in(informacoes.image_name);
    in.seekg(512, std::ios::beg);

    for (int i = 0; i < 128; i++){

        in.seekg(512+(i*32), std::ios::beg);
        in.read(file_SA, 12);
        int resultado = strcmp(file_SA, informacoes.file_name);

        if (resultado == 0){
            informacoes.entrada_diretorio = i;

            in.seekg(512+(i*32)+11, std::ios::beg);
            in >> informacoes.primeiro_sector;

            in.seekg(512+(i*32)+19, std::ios::beg);
            in >> informacoes.size;

            break;
        }

        if (i == 127){
            cout << "NÃO FOI POSSÍVEL ENCONTRAR SEU ARQUIVO" << endl;
            return 0;
        }
    }
    

}