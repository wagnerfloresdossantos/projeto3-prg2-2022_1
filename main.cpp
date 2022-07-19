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
    if (argc <= 3) {
        perror("Falta argumento na linha de comando!");
    }

    //cria a variavel inteiro intervalo a ser informado por argv[2]
    int intervalo = stoi(argv[2]);

    //cria a variavel string tipo que vai definir o tipo de mdia a ser apurada informada por arv[3]
    string tipo = argv[3];

    //lista do tipo double que vai receber os dados a serem avaliados
    list<double> lista;

   //Abertura do arquivo e criaçao da lista
   //linha arquivo
    string linha;
    //laço para leitura das linhas
    while (getline(arq, linha)) {
        //caso não tenha nada dentro do texto devolve uma lista vazia
        if (!linha.empty()) {
            //variável pos inicia em 0
            int pos = 0;
            //laço para leitura do valor desejado
            while (pos != string::npos) {
                pos = linha.find(" ");
                lista.push_back(stod(linha.substr(pos, linha.size())));
                pos = -1;
            }
        }
    }
    if(tipo == "mms" || tipo == "") {
        //Calculo da Media Movel Simples
        //variavel da media movel simples
        double mms;
        cout << "Cálculo da Média Móvel Simples" << endl;
        //laço para contabilizar o periodo lido
        for (int j = 0.; j <= lista.size(); j++) {
            //obtem iterador para primeiro elemento da lista
            auto x = lista.begin();
            //mostra na tela o periodo a ser apurado e o intervalor selecionado via argv[2]
            cout << "Periodo=" << j << " " << "Intervalo=" << intervalo << " ";
            //laço que percorre o intervalo do periodo
            for (int i = 0; i < intervalo; i++) {
                //mostra os dados contabilizados no intervalo
                cout << i << "=" << *x << " ";
                //faz o calculo do dominador
                mms += *x;
                //interaçao do elemento da lista
                x++;
            }
            //remove o primieor dados da lista
            lista.pop_front();
            //mostra o resultado da Media Movel Simples apurada em cada periodo
            cout << "MMS=" << mms / intervalo << endl;
            //zera a variavel da media movel para fazer os calculos do proximo periodo
            mms = 0;
        }
    }else {
        double mmp;
        int mmp_deno;
        cout << "Cálculo da Média Móvel Ponderada" << endl;
        //laço para contabilizar o periodo lido
        for (int j = 0.; j <= lista.size(); j++) {
            //obtem iterador para primeiro elemento da lista
            auto x = lista.begin();
            //mostra na tela o periodo a ser apurado e o intervalor selecionado via argv[2]
            cout << "Periodo=" << j << " " << "Intervalo=" << intervalo << " ";
            //laço que percorre o intervalo do periodo
            for (int i = 0; i < intervalo; i++) {
                //mostra os dados contabilizados no intervalo
                cout << i << "=" << *x << " ";
                //faz o calculo do dominador
                mmp += *x * (i + 1);
                //faz o calculo do denominador
                mmp_deno += (i + 1);
                //interaçao do elemento da lista
                x++;
            }
            //remove o primieor dados da lista
            lista.pop_front();
            //mostra o resultado da Media Movel Simples apurada em cada periodo
            cout << "MMP=" << mmp / mmp_deno << endl;
            //zera a variavel da media movel para fazer os calculos do proximo periodo
            mmp = 0;
            //zera a variavel do denominador
            mmp_deno = 0;
        }
    }



}

