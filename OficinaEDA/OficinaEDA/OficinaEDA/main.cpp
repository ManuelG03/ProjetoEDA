#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "contagemLinhas.h"

using namespace std;

struct ET {
    int capacidade;
    string mecanico;
    string marca;
};

struct carro {
    int id;
    string marca;
    string modelo;
    int tempo_reparacao;
    int dias_ET;
    string prioridade;
};

string* marcas = new string[num_marcas];
string* modelos = new string[num_modelos];

void criarEstacoes(int num_ETs) {
    string file = "marcas.txt";
    ifstream fileMarcas(file);
    string marca;

    ET* estacoes = new ET[num_ETs];


    if (fileMarcas.is_open()) {
        int i = 0;
        while (!fileMarcas.eof()) {
            getline(fileMarcas, marcas[i++]);
        }
    }

    for (int i = 0; i < num_ETs; i++)
    {
        ET* et = new ET[i];
        cout << "Introduza o mecânico para a estação " << i << ": ";
        cin >> estacoes[i].mecanico;
        estacoes[i].capacidade = rand() % 4 + 2;
        estacoes[i].marca = marcas[rand() % num_marcas];
    }
}

void criarCarros(int num_Ets) {
    string file2 = "modelos.txt";
    ifstream fileModelos(file2);
    string modelo;

    if (fileModelos.is_open()) {
        int i = 0;
        while (!fileModelos.eof()) {
            getline(fileModelos, modelos[i++]);
        }
    }


    carro* listadeespera = new carro[10];
    int id = 0;
    for (int i = 0; i < 10; i++) {
        listadeespera[i].id = id + 1;
        listadeespera[i].tempo_reparacao = rand() % 6 + 2;
        listadeespera[i].marca = marcas[rand() % num_marcas];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % num_modelos];
        int decisao = rand() % 2;
        if (decisao == 0) {
            listadeespera[i].prioridade = "Não";
        }
        else listadeespera[i].prioridade = "Sim";
        id++;
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "Carro: ID: " << listadeespera[i].id << " | ";
        cout << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
        cout << "Prioritario: " << listadeespera[i].prioridade << " | ";
        cout << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << listadeespera[i].dias_ET << endl;
    }
}

int main() {
    locale::global(locale(""));
    srand(time(NULL));

    int num_ETs;
    num_ETs = rand() % 6 + 3;
    criarEstacoes(num_ETs);
    criarCarros(num_ETs);



    return 0;
}