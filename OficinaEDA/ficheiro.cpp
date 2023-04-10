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

void carregarCarros(carro* listadeespera) {
    fstream fileCarros;
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

void carregarListaDeEspera(carro* not_added) {
    fstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");

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

void carregarEstacoes(ET* estacoes) {
    fstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");

    fstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    int NUM_ETS;
    fileEstacoes >> NUM_ETS;

    delete[] estacoes;
    estacoes = new ET[NUM_ETS];

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes >> estacoes[i].id;
        getline(fileEstacoes, estacoes[i].mecanico);
        fileEstacoes >> estacoes[i].capacidade;
        fileEstacoes >> estacoes[i].capacidade_atual;
        getline(fileEstacoes, estacoes[i].marca);
        fileEstacoes >> estacoes[i].faturacao;
        for (int h = 0; h < estacoes[i].capacidade_atual; h++)
        {
            fileEstacoes >> estacoes[i].carros[h].id;
            getline(fileEstacoes, estacoes[i].carros[h].marca);
            getline(fileEstacoes, estacoes[i].carros[h].modelo);
            getline(fileEstacoes, estacoes[i].carros[h].prioridade);
            fileEstacoes >> estacoes[i].carros[h].tempo_reparacao;
            fileEstacoes >> estacoes[i].carros[h].dias_ET;
        }
        fileCarrosReparados >> estacoes[i].carros_reparados;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            fileCarrosReparados >> estacoes[i].regRepCars[j].id;
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].marca);
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].modelo);
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].prioridade);
            fileCarrosReparados >> estacoes[i].regRepCars[j].tempo_reparacao;
            fileCarrosReparados >> estacoes[i].regRepCars[j].dias_ET;
        }
    }

    fileEstacoes.close();

    fileCarrosReparados.close();
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