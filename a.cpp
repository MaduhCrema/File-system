#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
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

