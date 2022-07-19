#include <iostream>
#include <fstream>
#include "errno.h"
#include <list>



using namespace std;

int main(int argc, char **argv) {

    //Abre o arquivo
    ifstream arq(argv[1]);

    //Caso o arquivo não abra
    if (!arq.is_open()) {
        perror("Erro ao abrir o Arquivo!");
    }
    //Verifica se os argumentos de linha são suficientes
    if (argc <= 2) {
        perror("Falta argumento na linha de comando!");
    }

    int intervalo = stoi(argv[2]);

    list<double> lista;

    string linha;


    while (getline(arq, linha)) {


        //caso não tenha nada dentro do texto devolve uma lista vazia
        if (!linha.empty()) {
            //variável pos inicia em 0
            //variável coisa = copia de algo o que esta declarado como constante
            int pos = 0;

            while (pos != string::npos) {
                pos = linha.find(" ");
                lista.push_back(stod(linha.substr(pos, linha.size())));
                pos = -1;
            }
        }
    }
    double mms;




        for(int j=0.;j<=lista.size();j++) {
            auto x = lista.begin();
            cout << "Periodo=" << j <<" " <<"Intervalo=" << intervalo << " " ;
            for (int i=0 ; i <= intervalo; i++) {

                cout <<  i << "=" << *x << " ";
                mms += *x;
                x++;
            }
            lista.pop_front();
            cout << "MMS=" << mms / intervalo << endl;
            mms=0;

        }



}

