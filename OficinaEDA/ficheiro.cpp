#include <iostream>
#include <fstream>
#include <string>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

void gravarCarros(carro* listadeespera, int num_carros_criados) {
    ofstream fileCarros;
    fileCarros.open("carros.txt");

    fileCarros << num_carros_criados << endl;

    for (int i = 0; i < num_carros_criados; i++) {
        fileCarros << listadeespera[i].id << endl;
        fileCarros << listadeespera[i].marca << endl;
        fileCarros << listadeespera[i].modelo << endl;
        fileCarros << listadeespera[i].prioridade << endl;
        fileCarros << listadeespera[i].tempo_reparacao << endl;
        fileCarros << listadeespera[i].dias_ET << endl;
    }

    fileCarros.close();
}

void printCarros(carro* listadeespera, int num_carros_criados) {
    cout << "Carros carregados do arquivo: " << endl;
    for (int i = 0; i < num_carros_criados; i++) {
        cout << "ID: " << listadeespera[i].id << endl;
        cout << "Marca: " << listadeespera[i].marca << endl;
        cout << "Modelo: " << listadeespera[i].modelo << endl;
        cout << "Prioridade: " << listadeespera[i].prioridade << endl;
        cout << "Tempo de reparação: " << listadeespera[i].tempo_reparacao << endl;
        cout << "Dias na ET: " << listadeespera[i].dias_ET << endl;
        cout << endl;
    }
}


void carregarCarros(carro* listadeespera) {
    ifstream fileCarros;
    fileCarros.open("carros.txt");

    int num_carros_criados;
    fileCarros >> num_carros_criados;

    delete[] listadeespera;
    listadeespera = new carro[num_carros_criados];

    for (int i = 0; i < num_carros_criados; i++) {
        fileCarros >> listadeespera[i].id;
        getline(fileCarros, listadeespera[i].marca);
        getline(fileCarros, listadeespera[i].modelo);
        getline(fileCarros, listadeespera[i].prioridade);
        fileCarros >> listadeespera[i].tempo_reparacao;
        fileCarros >> listadeespera[i].dias_ET;
    }

    fileCarros.close();

    //printCarros(listadeespera, num_carros_criados);
} 

void gravarListaDeEspera(carro* not_added, int num_not_added) { //Função que grava as informações dos carros presentes na lista de espera
    ofstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");

    fileListaDeEspera << num_not_added << endl; //Gravar o número de carros presentes na lista de espera

    for (int i = 0; i < num_not_added; i++) {
        fileListaDeEspera << not_added[i].id << endl; //Gravar o id de cada carro da lista de espera
        fileListaDeEspera << not_added[i].marca << endl; //Gravar a marca de cada carro da lista de espera
        fileListaDeEspera << not_added[i].modelo << endl; //Gravar o modelo de cada carro da lista de espera
        fileListaDeEspera << not_added[i].prioridade << endl; //Gravar a prioridade de cada carro da lista de espera
        fileListaDeEspera << not_added[i].tempo_reparacao << endl; //Gravar o tempo de reparação de cada carro da lista de espera
        fileListaDeEspera << not_added[i].dias_ET << endl; //Gravar a quantidade de dias que o carro esteve na ET de cada carro da lista de espera
    }

    fileListaDeEspera.close();
} 

void printListaDeEspera(carro* not_added, int num_not_added) {
    cout << "Number of not added cars: " << num_not_added << endl;
    for (int i = 0; i < num_not_added; i++) {
        cout << "Car " << i + 1 << endl;
        cout << "\tID: " << not_added[i].id << endl;
        cout << "\tMarca: " << not_added[i].marca << endl;
        cout << "\tModelo: " << not_added[i].modelo << endl;
        cout << "\tPrioridade: " << not_added[i].prioridade << endl;
        cout << "\tTempo de Reparação: " << not_added[i].tempo_reparacao << endl;
        cout << "\tDias em espera: " << not_added[i].dias_ET << endl;
    }
}


void carregarListaDeEspera(carro* not_added) {
    ifstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");
    string linha;

    int num_not_added;
    fileListaDeEspera >> num_not_added;

    delete[] not_added;
    not_added = new carro[num_not_added];

    for (int i = 0; i < num_not_added; i++) {
        fileListaDeEspera >> not_added[i].id;
        getline(fileListaDeEspera, not_added[i].marca);
        getline(fileListaDeEspera, not_added[i].modelo);
        getline(fileListaDeEspera, not_added[i].prioridade);
        fileListaDeEspera >> not_added[i].tempo_reparacao;
        fileListaDeEspera >> not_added[i].dias_ET;
    }

    fileListaDeEspera.close();

    printListaDeEspera(not_added, num_not_added);
} 

void gravarEstacoes(ET* estacoes) {
    ofstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");

    ofstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    fileEstacoes << NUM_ETS << endl;

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes << estacoes[i].id << endl;
        fileEstacoes << estacoes[i].mecanico << endl;
        fileEstacoes << estacoes[i].capacidade << endl;
        fileEstacoes << estacoes[i].capacidade_atual << endl;
        fileEstacoes << estacoes[i].marca << endl;
        fileEstacoes << estacoes[i].faturacao << endl;

        for (int h = 0; h < estacoes[i].capacidade_atual; h++)
        {
            fileEstacoes << estacoes[i].carros[h].id << endl;
            fileEstacoes << estacoes[i].carros[h].marca << endl;
            fileEstacoes << estacoes[i].carros[h].modelo << endl;
            fileEstacoes << estacoes[i].carros[h].prioridade << endl;
            fileEstacoes << estacoes[i].carros[h].tempo_reparacao << endl;
            fileEstacoes << estacoes[i].carros[h].dias_ET << endl;
        }

        fileCarrosReparados << estacoes[i].carros_reparados << endl;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            fileCarrosReparados << estacoes[i].regRepCars[j].id << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].marca << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].modelo << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].prioridade << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].tempo_reparacao << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].dias_ET << endl;
        }
    }

    fileEstacoes.close();

    fileCarrosReparados.close();
}

void printEstacoes(ET* estacoes, int NUM_ETS) {
    for (int i = 0; i < NUM_ETS; i++) {
        cout << "id: " << estacoes[i].id << "\n";
        cout << "mecanico: " << estacoes[i].mecanico << "\n";
        cout << "capacidade: " << estacoes[i].capacidade << "\n";
        cout << "capacidade_atual: " << estacoes[i].capacidade_atual << "\n";
        cout << "marca: " << estacoes[i].marca << "\n";
        cout << "faturacao: " << estacoes[i].faturacao << "\n";

        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            cout << "carro " << h + 1 << ":\n";
            cout << "id: " << estacoes[i].carros[h].id << "\n";
            cout << "marca: " << estacoes[i].carros[h].marca << "\n";
            cout << "modelo: " << estacoes[i].carros[h].modelo << "\n";
            cout << "prioridade: " << estacoes[i].carros[h].prioridade << "\n";
            cout << "tempo_reparacao: " << estacoes[i].carros[h].tempo_reparacao << "\n";
            cout << "dias_ET: " << estacoes[i].carros[h].dias_ET << "\n";
        }

        cout << "carros_reparados: " << estacoes[i].carros_reparados << "\n";
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            cout << "carro " << j + 1 << ":\n";
            cout << "id: " << estacoes[i].regRepCars[j].id << "\n";
            cout << "marca: " << estacoes[i].regRepCars[j].marca << "\n";
            cout << "modelo: " << estacoes[i].regRepCars[j].modelo << "\n";
            cout << "prioridade: " << estacoes[i].regRepCars[j].prioridade << "\n";
            cout << "tempo_reparacao: " << estacoes[i].regRepCars[j].tempo_reparacao << "\n";
            cout << "dias_ET: " << estacoes[i].regRepCars[j].dias_ET << "\n";
        }

        cout << "\n";
    }
}

void carregarEstacoes(ET* estacoes) {
    ifstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");
    ifstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    int NUM_ETS;
    fileEstacoes >> NUM_ETS;

    delete[] estacoes;
    estacoes = new ET[NUM_ETS];

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes >> estacoes[i].id; break;
        getline(fileEstacoes, estacoes[i].mecanico); break;
        fileEstacoes >> estacoes[i].capacidade; break;
        fileEstacoes >> estacoes[i].capacidade_atual; break;
        getline(fileEstacoes, estacoes[i].marca); break;
        fileEstacoes >> estacoes[i].faturacao; break;

        for (int h = 0; h < estacoes[i].capacidade_atual; h++)
        {
            fileEstacoes >> estacoes[i].carros[h].id; break;
            getline(fileEstacoes, estacoes[i].carros[h].marca); break;
            getline(fileEstacoes, estacoes[i].carros[h].modelo); break;
            getline(fileEstacoes, estacoes[i].carros[h].prioridade); break;
            fileEstacoes >> estacoes[i].carros[h].tempo_reparacao; break;
            fileEstacoes >> estacoes[i].carros[h].dias_ET; break;
        }

        fileCarrosReparados >> estacoes[i].carros_reparados; break;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            fileCarrosReparados >> estacoes[i].regRepCars[j].id; break;
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].marca); break;
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].modelo); break;
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].prioridade); break;
            fileCarrosReparados >> estacoes[i].regRepCars[j].tempo_reparacao; break;
            fileCarrosReparados >> estacoes[i].regRepCars[j].dias_ET; break;
        }
    }

    fileEstacoes.close();
    fileCarrosReparados.close();
    
    //printEstacoes(estacoes, NUM_ETS);
}


void gravarOficina(carro* listadeespera, int num_carros_criados, carro* not_added, int num_not_added, ET* estacoes) {
    gravarCarros(listadeespera, num_carros_criados);
    gravarListaDeEspera(not_added, num_not_added);
    gravarEstacoes(estacoes);
}

void carregarOficina(carro* listadeespera, carro* not_added, ET* estacoes) {
    carregarEstacoes(estacoes);
    carregarListaDeEspera(not_added);
    carregarCarros(listadeespera);
}