#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

typedef struct {
    char file_name[12], image_name[15];
    int numero_setores;
    int size;
    long long int primeiro_sector;
    int entrada_diretorio;
    long long int bitmap;
}copia;

int file_size(copia informacoes) {
    ifstream in(informacoes.file_name);

    if (!in.is_open()) {
        cerr << endl << "ERRO NA ABERTURA DO ARQUIVO" << endl;
        return -1;
    }

    in.seekg(0, ios::end);
    streampos filesize = in.tellg();
    in.close(); 

    cout << "tamanho: " << filesize << " bytes" << endl;
    return filesize;
}

copia encontrar_primeiro_setor(copia informacoes){

    long long int tamanho_bitmap;
    FILE *fp;
 
    fp = fopen(informacoes.image_name, "rb");

    fseek(fp, 14, SEEK_SET);
    fread(&informacoes.bitmap ,8,1, fp);

    fseek(fp, 22, SEEK_SET);
    fread(&tamanho_bitmap ,8,1, fp);

    int aux, cont;
    for (int i = 0; i < tamanho_bitmap; i++){
        fseek(fp, (informacoes.bitmap*512)+i, SEEK_SET);
        fread(&aux, 1,1, fp);
        if(aux == 0)
            cont++;
        else
            cont = 0;
        if(cont == informacoes.numero_setores){
            aux = i;
            break;
        }else if (i == tamanho_bitmap){
            aux = -1;
        }
    }
    if(aux < 0){
        cout << "ERRO! NÃO EXISTE ESPAÇO EM MEMORIA" << endl;
        informacoes.primeiro_sector = -1;
    }else{
        ofstream out(informacoes.image_name);
        informacoes.primeiro_sector = (aux-informacoes.numero_setores+1);
    }

    return informacoes;
}

void aloca_entrada_rootdir(copia informacoes) {

        ifstream in("teste.txt");
        ofstream out("disk_image.bin");
        int temp;

    for(int i = 0; i < 128; i++){
        int aux = 512+(i*32);
        out.seekp(aux, std::ios::beg);
        in >> temp;

        if(temp == 0){
                out.seekp(aux, std::ios::beg);
                out << "informacoes.file_name";

                out.seekp(aux+12, std::ios::beg);
                out << "informacoes.primeiro_sector";

                out.seekp(aux+20, std::ios::beg);
                out << "informacoes.size";

                out.seekp(aux+24, std::ios::beg);
                out << "informacoes.numero_setores";

                temp = -1;
        }}
}


void escrita_em_fs(copia informacoes){

    ifstream in(informacoes.file_name);
    ofstream out(informacoes.image_name);

    informacoes.primeiro_sector = 4608 + (informacoes.primeiro_sector*512);
    out.seekp(informacoes.primeiro_sector, std::ios::beg);
    cout << informacoes.primeiro_sector;

    char k;

    for (int i = 0; i < informacoes.size; i++){
        in >> k;
        k = 1;
        out << k;
    }

    cout << "SUAS INFORMAÇÕES FORAM GRAVADAS NO SISTEMA DE ARQUIVOS NO ENDEREÇO " << informacoes.primeiro_sector;

}

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

            in.seekg(512+(i*32)+11, std::ios::beg);
            in >> informacoes.primeiro_sector;

            in.seekg(512+(i*32)+19, std::ios::beg);
            in >> informacoes.size;

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
    ofstream out(informacoes.file_name);

    in.seekg(4608+(512*informacoes.primeiro_sector), std::ios::beg);

    char k;
    for (int i = 0; i < informacoes.size; i++){
        in >> k;
        out << k;
    }

    cout << "SUAS INFORMAÇÕES FORAM GRAVADAS NO SISTEMA DE ARQUIVOS";

}

int main(){

    int op;
    cout << "Que operação você deseja realizar?" << endl << endl << "Tecle (1) para cópia do sistema de arquivos para o disco rígido" << endl << "ou tecle (2) para cópia do disco rígido para o sistema de arquivos" << endl << endl;
    cin >> op;
    copia informacoes;
    switch (op){
    case 1:{
        cout << endl << "Qual o nome do arquivo que você deseja copiar para o sistema de arquivos?" << endl << endl;
        cin >> informacoes.file_name; 

        cout << endl << "Em que imagem este arquivo está localizado?" << endl << endl;
        cin >> informacoes.image_name; 

        informacoes = localiza_arquivo_fs(informacoes);
        if (informacoes.primeiro_sector == -1)
            return 0;
        
        escrita_em_disco(informacoes);
        return 0;
    }case 2:{

        cout << endl << "Qual o nome do arquivo que você deseja copiar para o sistema de arquivos?" << endl << endl;
        cin >> informacoes.file_name; 

        informacoes.size = file_size(informacoes);
        if (informacoes.size == -1){
            cout << "ERRO! " << endl;
            return 0;
        }

        cout << endl << "Para qual imagem você deseja fazer a cópia?" << endl;
        cin >> informacoes.image_name; 

        informacoes.numero_setores = informacoes.size/512;

         informacoes = encontrar_primeiro_setor(informacoes);
         if (informacoes.primeiro_sector < 0){
            cout << "ERRO! NÃO EXISTE ESPAÇO EM MEMORIA" << endl;
            return 0;
         }

        ifstream in(informacoes.file_name);
        ofstream out(informacoes.image_name);
        int temp;

        for(int i = 0; i < 128; i++){
            int aux = 512+(i*32);
            out.seekp(aux, std::ios::beg);
            in >> temp;

            if(temp == 0){
                out.seekp(aux, std::ios::beg);
                out << informacoes.file_name;

                out.seekp(aux+12, std::ios::beg);
                out << informacoes.primeiro_sector;

                out.seekp(aux+20, std::ios::beg);
                out << informacoes.size;

                out.seekp(aux+24, std::ios::beg);
                out << informacoes.numero_setores;
                break;

            }}        
        return 0;

       escrita_em_fs(informacoes);

    }default:
        break;
    }


    
}