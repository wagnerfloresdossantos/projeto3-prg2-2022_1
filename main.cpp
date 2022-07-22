#include <iostream>
#include <fstream>
#include "errno.h"
#include <list>

using namespace std;
//struct
struct classe{
    //Elementos obtidos do arquivo csv
    string data;
    double valor;

};

//Função que separa uma linha baseada em um caracter passado para a mesma
    list<string> separa(const string &texto, const string &sep) {

        //declara uma variável temporaria para devolver o resultado como lista
        list<string> lista;

        //caso não tenha nada dentro do texto , devolve uma lista vazia
        if (!texto.empty()) {
            //Variavel pos = posições do character separa
            //Variavel coisa = Copia de algo que está declarada como constante
            int pos = 0;
            string coisa = texto;

            //loop que separa a string
            //pos recebe a posição do character 'sep'
            //Coloca a substring de 0 até pos dentro da fila
            //Apaga a substring utilizada
            while (pos != string::npos) {
                pos = coisa.find(sep);
                lista.push_back(coisa.substr(0, pos));
                coisa.erase(0, pos + 1);
            }
        }
        return lista;

}

void adiciona_a_classe(list<string> & lista,classe & classe_temporario)
{
    //A lista está ordenada da mesma forma que o arquivo
    //Primeiro código da classe
    classe_temporario.data = lista.front();
    lista.pop_front();

    //Segundo prioridade da classe
    classe_temporario.valor = stod(lista.front());
    lista.pop_front();
}

//Função Leitura do arquivo csv
list<classe> leitura_csv(ifstream & arq ){
    //Lista onde Todas as classes passadas pelo arquivo vão ser armazenadas
    //String linha para a leitura das linhas do arquivo
    list<classe> temp_classes;
    string linha;

    //Enquanto é possivel ler uma linha desse arquivo ele repete o loop
    while (getline(arq, linha)) {

        //Declaração de Lista temporaria e de classe temporaria
        //lista temporaria que contem os dados de uma linha do arquivo
        //classe_de_clientes temporaria os quais serão armazenados dentro da fila de classes
        list<string> lista_temporaria = separa(linha, " ");
        classe classe_temporaria;

        //Chama o adiona_a_classe que converte os dados que estão na lista em uma classe_temporaria
        //Logo em seguida pega a classe_temporaria e armazena em uma lista com todas as classes
        adiciona_a_classe(lista_temporaria, classe_temporaria);
        temp_classes.push_back(classe_temporaria);
    }

    return temp_classes;
}
void mms(list<classe> & classes, int periodo) {

    //lista temporária com os valores a serem mostrados
    list<string> lista_temp;

    for (auto it = classes.begin(); it != classes.end(); it++) {
        it = classes.begin();
        //variavel para numerador da conta
        double numerador = 0;
        for (int i = 0; i < periodo; i++) {
            numerador += it->valor + (i + 1);
            it++;
        }
        it--;
        lista_temp.push_back(to_string(numerador / periodo)+" "+( it->data));
        classes.pop_front();
    }
    for (auto &y: lista_temp) {
        cout << y<< endl;
    }
}
void mmp(list<classe> & classes, int periodo) {
    //lista temporária com os valores a serem mostrados
    list<string> lista_temp;

    for (auto it = classes.begin(); it != classes.end(); it++) {
        it = classes.begin();
        //variavel para numerador da conta
        double numerador = 0;
        for (int i = 0; i < periodo; i++) {
            numerador += it->valor + (i + 1);
            it++;
        }
        it--;
        lista_temp.push_back(to_string(numerador / periodo)+" "+( it->data));
        classes.pop_front();
    }
    for (auto &y: lista_temp) {
        cout << y<< endl;
    }
}

int main(int argc, char **argv) {

    //Abre o arquivo
    ifstream arq(argv[1]);

    //Caso o arquivo não abra
    if (!arq.is_open()) {
        perror("Erro ao abrir o Arquivo!");
    }

    //cria a variavel inteiro intervalo a ser informado por argv[2]
    int intervalo = stoi(argv[2]);

    //cria a variavel string tipo que vai definir o tipo de mdia a ser apurada informada por arv[3]
    string tipo = argv[3];

    list<classe>classes = leitura_csv(arq);

    //Verifica se os argumentos de linha são suficientes
    if (argc <= 3) {
        perror("Falta argumento na linha de comando!");
    }

    if(tipo == "mms" || tipo == "") {
        //chama a função que calcula a media movel simples
        mms(classes, intervalo);
    }else {
        //chama a função quelcula a media movel ponderada
        mmp(classes, intervalo);

    }



}

