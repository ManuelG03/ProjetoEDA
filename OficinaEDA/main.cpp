#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "constantes.h"

using namespace std;

struct ET {
    int id;
    int capacidade;
    string mecanico;
    string marca;
    static int num_ETs;
};

struct carro {
    int id;
    string marca;
    string modelo;
    int tempo_reparacao;
    int dias_ET;
    string prioridade;
};

void criarEstacoes(ET* estacoes, string* marcas) {
    string file = "marcas.txt";
    ifstream fileMarcas(file);
    string marca;

    int id_estacao = 1;

    if (fileMarcas.is_open()) {
        int i = 0;
        while (!fileMarcas.eof()) {
            getline(fileMarcas, marcas[i++]);
        }
    }

    for (int i = 0; i < NUM_ETS; i++)
    {
        cout << "Introduza o mecânico para a estação " << i << ": ";
        getline(cin, estacoes[i].mecanico);
        estacoes[i].id = id_estacao++;
        estacoes[i].capacidade = rand() % 4 + 2;
        estacoes[i].marca = marcas[rand() % NUM_MARCAS];
    }
}

void criarCarros(carro* listadeespera, string* modelos, string* marcas) {
    string file2 = "modelos.txt";
    ifstream fileModelos(file2);
    string modelo;

    if (fileModelos.is_open()) {
        int i = 0;
        while (!fileModelos.eof()) {
            getline(fileModelos, modelos[i++]);
        }
    }
    
    int id = 0;
    for (int i = 0; i < NUM_CARROS; i++) {
        listadeespera[i].id = id + 1;
        listadeespera[i].tempo_reparacao = rand() % 6 + 2;
        listadeespera[i].marca = marcas[rand() % NUM_MARCAS];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % NUM_MODELOS];
        
        int decisao = rand() % 2;
        if (decisao == 0) {
            listadeespera[i].prioridade = "Não";
        }
        else listadeespera[i].prioridade = "Sim";

        id++;
    }
}

void menu(ET* estacoes, carro* listadeespera) {
    for (size_t i = 0; i < NUM_ETS; i++)
    {
        cout << "ET: " << estacoes[i].id << " | ";
        cout << "Mecânico: " << estacoes[i].mecanico << " | ";
        cout << "Capacidade: " << estacoes[i].capacidade << " | ";
        cout << "Carros: " << " | ";
        cout << "Marca: " << estacoes[i].marca << " | ";
        cout << "Total de Faturação: " << endl;
        for (int i = 0; i < NUM_CARROS; i++)
        {
            cout << "Carro: ID: " << listadeespera[i].id << " | ";
            cout << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
            cout << "Prioritario: " << listadeespera[i].prioridade << " | ";
            cout << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
            cout << "Dias da ET: " << listadeespera[i].dias_ET << endl;
        }
        cout << "---------------------------------" << endl;
    }

}

int menuInicio() {
    int escolha;
    cout << "***** Bem Vindo Gestor ***** \n";
    cout << "(1).Reparação Manual \n";
    cout << "(2).Atualizar tempo de reparação \n";
    cout << "(3).Adicionar Prioridade\n";
    cout << "(4).Remover Mecânico\n";
    cout << "(5).Gravar Oficina \n";
    cout << "(6).Carregar Oficina \n";
    cout << "(7).Imprimir Oficina \n";


do
{
    cout << "Selecione a sua opção:";
    cin >> escolha;
    switch (escolha)
    {
    case 1: ; break;
    case 2: ; break;
    case 3: ; break;
    case 4: ; break;
    case 5: ; break;
    default: cout << "Escolha Inválida!"; break;
    }
} while (escolha > 6);
return 0;
}

int main() {
    locale::global(locale(""));
    srand(time(NULL));

    string* marcas = new string[NUM_MARCAS];
    string* modelos = new string[NUM_MODELOS];
    carro* listadeespera = new carro[NUM_CARROS];
    ET* estacoes = new ET[NUM_ETS];

    criarEstacoes(estacoes, marcas);
    criarCarros(listadeespera, modelos, marcas);
    menu(estacoes, listadeespera);
    return 0;
}