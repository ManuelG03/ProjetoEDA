#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "constantes.h"

using namespace std;
const int NUM_CARROS_A_CRIAR = 10;
int NUM_CARROS_CRIADOS = 0;
int id_lista = 0;


struct carro {
    int id;
    string marca;
    string modelo;
    int tempo_reparacao;
    int dias_ET;
    string prioridade;
};

struct ET {
    int id;
    int capacidade;
    string mecanico;
    string marca;
    static int num_ETs;
    carro* carros;
    int capacidade_atual;

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
        estacoes[i].capacidade_atual = 0;
        estacoes[i].marca = marcas[rand() % NUM_MARCAS];
        estacoes[i].carros = new carro[estacoes[i].capacidade];
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
    
    
    for (int i = NUM_CARROS_CRIADOS; i < NUM_CARROS_CRIADOS + 10; i++) {
        listadeespera[i].id = id_lista + 1;
        listadeespera[i].tempo_reparacao = rand() % 6 + 2;
        listadeespera[i].marca = marcas[rand() % NUM_MARCAS];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % NUM_MODELOS];
        
        int decisao = rand() % 100;
        if (decisao > 6) {
            listadeespera[i].prioridade = "Não";
        }
        else listadeespera[i].prioridade = "Sim";

        id_lista++;
    }
    NUM_CARROS_CRIADOS += 10;
}

void adicionarCarrosETs(carro* listadeespera, ET* estacoes) {
    int num_carros_adicionados = 0;
    int i = 0;
    int NUM_CARROS_A_CRIAR = NUM_CARROS_CRIADOS; 
    int ultima_posicao = -1;
    int f = 0;
    while (num_carros_adicionados < 8 && i < NUM_CARROS_A_CRIAR) {
        for (int j = 0; j < NUM_ETS; j++) {
            if (estacoes[j].marca == listadeespera[i].marca) {
                if (estacoes[j].capacidade > 0) {
                    estacoes[j].carros[estacoes[j].capacidade_atual] = listadeespera[i];
                    estacoes[j].capacidade--;
                    estacoes[j].capacidade_atual++;
                    num_carros_adicionados++;
                    
 
                    for (int k = i; k < NUM_CARROS_A_CRIAR - 1; k++) { //***
                        listadeespera[k] = listadeespera[k + 1];
                    }
                    NUM_CARROS_A_CRIAR--;
                    i--;
                    break;
                }
            }
            
        }
        
        i++;
    }

    cout << num_carros_adicionados << " carros adicionados às ETs.\n";
}





void menu(ET* estacoes, carro* listadeespera) {
    for (size_t i = 0; i < NUM_ETS; i++)
    {
        cout << "ET: " << estacoes[i].id << " | ";
        cout << "Mecânico: " << estacoes[i].mecanico << " | ";
        cout << "Capacidade: " << estacoes[i].capacidade << " | ";
        cout << "Carros: " << estacoes[i].capacidade_atual<< " | ";
        cout << "Marca: " << estacoes[i].marca << " | ";
        cout << "Total de Faturação: " << endl;

        if (estacoes[i].capacidade_atual == 0) {
            cout << " ET não possui carros de momento" << endl;
        }
        else {
            for (int h = 0; h < estacoes[i].capacidade_atual; h++)
            {
                cout << "Carro: ID: " << estacoes[i].carros[h].id << " | ";
                cout << estacoes[i].carros[h].marca << "-" << estacoes[i].carros[h].modelo << " | ";
                cout << "Prioritario: " << estacoes[i].carros[h].prioridade << " | ";
                cout << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
                cout << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
            }
        }
    }

}

void verListaDeEspera(carro* listadeespera) {
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++)
        {
            cout << "Carro: ID: " << listadeespera[i].id << " | ";
            cout << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
            cout << "Prioritario: " << listadeespera[i].prioridade << " | ";
            cout << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
            cout << "Dias da ET: " << listadeespera[i].dias_ET << endl;
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

void ciclo(carro* listadeespera, string* modelos, string* marcas) {
    criarCarros(listadeespera,modelos,marcas);
}

int main() {
    locale::global(locale(""));
    srand(time(NULL));

    string* marcas = new string[NUM_MARCAS];
    string* modelos = new string[NUM_MODELOS];
    carro* listadeespera = new carro[200];
    ET* estacoes = new ET[NUM_ETS];

    criarEstacoes(estacoes, marcas);
    criarCarros(listadeespera, modelos, marcas);
    verListaDeEspera(listadeespera);
    adicionarCarrosETs(listadeespera,estacoes);

    //verListaDeEspera(listadeespera);
   
    menu(estacoes, listadeespera);
    return 0;
}