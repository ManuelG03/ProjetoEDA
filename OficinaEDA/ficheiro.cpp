#include <iostream>
#include <fstream>
#include <string>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

//void gravarOficina(ET* estacoes, carro* listadeespera, int NUM_CARROS_CRIADOS, carro* not_added, int num_not_added) {
//    ofstream outfile;
//    outfile.open("oficina.txt");
//
//    outfile << "-----------------------------------------------Estações de Trabalho-----------------------------------------------" << endl;
//    for (int i = 0; i < NUM_ETS; i++)
//    {
//        outfile << "ET: " << estacoes[i].id << " | ";
//        outfile << "Mecânico: " << estacoes[i].mecanico << " | ";
//        outfile << "Capacidade: " << estacoes[i].capacidade << " | ";
//        outfile << "Carros: " << estacoes[i].capacidade_atual << " | ";
//        outfile << "Marca: " << estacoes[i].marca << " | ";
//        outfile << "Total de Faturação: " << estacoes[i].faturacao << "$" << endl;
//
//        if (estacoes[i].capacidade_atual == 0) {
//            outfile << "ET não possui carros de momento" << endl;
//        }
//        else {
//            for (int h = 0; h < estacoes[i].capacidade_atual; h++)
//            {
//                outfile << "Carro: ID: " << estacoes[i].carros[h].id << " | ";
//                outfile << estacoes[i].carros[h].marca << "-" << estacoes[i].carros[h].modelo << " | ";
//                outfile << "Prioritário: " << estacoes[i].carros[h].prioridade << " | ";
//                outfile << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
//                outfile << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
//            }
//        }
//        if (i < NUM_ETS - 1) {
//            outfile << "----------------------------------------------------------------------------------------------------" << endl;
//        }
//    }
//    outfile << endl << endl << endl;
//
//
//
//    outfile << "-----------------------------------------------Lista de carros-----------------------------------------------" << endl;
//
//    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
//        outfile << "Carro " << ": ";
//        outfile << "ID: " << listadeespera[i].id << " | ";
//        outfile << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
//        outfile << "Prioritário: " << listadeespera[i].prioridade << " | ";
//        outfile << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
//        outfile << "Dias na ET: " << listadeespera[i].dias_ET << endl;
//    }
//    outfile << endl << endl << endl;
//
//
//
//    outfile << "----------------------------------------------Lista de espera---------------------------------------------- - " << endl;
//    for (int i = 0; i < num_not_added; i++) {
//        outfile << "Carro: ID: " << not_added[i].id << " | ";
//        outfile << not_added[i].marca << "-" << not_added[i].modelo << " | ";
//        outfile << "Prioritário: " << not_added[i].prioridade << " | ";
//        outfile << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
//        outfile << "Dias da ET: " << not_added[i].dias_ET << endl;
//    }
//    outfile << endl << endl << endl;
//
//
//
//    outfile << "-----------------------------------------------Carros reparados-----------------------------------------------" << endl;
//    for (int i = 0; i < NUM_ETS; i++) {
//        outfile << "ET " << i + 1 << ":" << endl;
//        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
//            outfile << "Carro " << j + 1 << ": ";
//            outfile << "ID: " << estacoes[i].regRepCars[j].id << " | ";
//            outfile << estacoes[i].regRepCars[j].marca << "-" << estacoes[i].regRepCars[j].modelo << " | ";
//            outfile << "Prioritário: " << estacoes[i].regRepCars[j].prioridade << " | ";
//            outfile << "Tempo Reparação: " << estacoes[i].regRepCars[j].tempo_reparacao << " | ";
//            outfile << "Dias na ET: " << estacoes[i].regRepCars[j].dias_ET << endl;
//        }
//        outfile << endl;
//    }
//
//    outfile.close();
//}

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

//void carregarCarros(carro* listadeespera) {
//    fstream fileCarros;
//    fileCarros.open("carros.txt");
//
//    int num_carros_criados;
//    fileCarros >> num_carros_criados;
//
//    delete[] listadeespera;
//    carro* listadeespera = new carro[num_carros_criados];
//
//    for (int i = 0; i < num_carros_criados; i++) {
//        fileCarros >> listadeespera[i].id;
//        getline(fileCarros, listadeespera[i].marca);
//        getline(fileCarros, listadeespera[i].modelo);
//        getline(fileCarros, listadeespera[i].prioridade);
//        fileCarros >> listadeespera[i].tempo_reparacao;
//        fileCarros >> listadeespera[i].dias_ET;
//    }
//
//    fileCarros.close();
//}

void gravarListaDeEspera(carro* not_added, int num_not_added) {
    ofstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");

    fileListaDeEspera << num_not_added << endl;

    for (int i = 0; i < num_not_added; i++) {
        fileListaDeEspera << not_added[i].id << endl;
        fileListaDeEspera << not_added[i].marca << endl;
        fileListaDeEspera << not_added[i].modelo << endl;
        fileListaDeEspera << not_added[i].prioridade << endl;
        fileListaDeEspera << not_added[i].tempo_reparacao << endl;
        fileListaDeEspera << not_added[i].dias_ET << endl;
    }

    fileListaDeEspera.close();
}

//void carregarListaDeEspera(carro* not_added) {
//    fstream fileListaDeEspera;
//    fileListaDeEspera.open("listaDeEspera.txt");
//
//    int num_not_added;
//    fileListaDeEspera >> num_not_added;
//
//    delete[] not_added;
//    carro* not_added = new carro[num_not_added];
//
//    for (int i = 0; i < num_not_added; i++) {
//        fileListaDeEspera >> not_added[i].id;
//        getline(fileListaDeEspera, not_added[i].marca);
//        getline(fileListaDeEspera, not_added[i].modelo);
//        getline(fileListaDeEspera, not_added[i].prioridade);
//        fileListaDeEspera >> not_added[i].tempo_reparacao;
//        fileListaDeEspera >> not_added[i].dias_ET;
//    }
//
//    fileListaDeEspera.close();
//}

void gravarCarrosReparados(ET* estacoes) {
    ofstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    fileCarrosReparados << NUM_ETS << endl;

    for (int i = 0; i < NUM_ETS; i++) {
        fileCarrosReparados << estacoes[i].id << endl;
        if (estacoes[i].carros_reparados == 0) {
            fileCarrosReparados << "Nenhum carro foi reparado" << endl;
        }
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            fileCarrosReparados << estacoes[i].regRepCars[j].id << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].marca << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].modelo << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].prioridade << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].tempo_reparacao << endl;
            fileCarrosReparados << estacoes[i].regRepCars[j].dias_ET << endl;
        }
    }

    fileCarrosReparados.close();
}

//void carregarCarrosReparados(ET* estacoes) {
//    fstream fileCarrosReparados;
//    fileCarrosReparados.open("carrosReparados.txt");
//
//    int NUM_ETS;
//    fileCarrosReparados >> NUM_ETS;
//
//    delete[] estacoes;
//    carro* estacoes = new carro[NUM_ETS];
//
//    for (int i = 0; i < NUM_ETS; i++) {
//        fileCarrosReparados >> estacoes[i].id;
//        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
//            fileCarrosReparados >> estacoes[i].regRepCars[j].id;
//            getline(fileCarrosReparados, estacoes[i].regRepCars[j].marca);
//            getline(fileCarrosReparados, estacoes[i].regRepCars[j].modelo);
//            getline(fileCarrosReparados, estacoes[i].regRepCars[j].prioridade);
//            fileCarrosReparados >> estacoes[i].regRepCars[j].tempo_reparacao;
//            fileCarrosReparados >> estacoes[i].regRepCars[j].dias_ET;
//        }
//    }
//
//    fileCarrosReparados.close();
//}

void gravarEstacoes(ET* estacoes) {
    ofstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");

    fileEstacoes << NUM_ETS << endl;

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes << estacoes[i].id << endl;
        fileEstacoes << estacoes[i].mecanico << endl;
        fileEstacoes << estacoes[i].capacidade << endl;
        fileEstacoes << estacoes[i].capacidade_atual << endl;
        fileEstacoes << estacoes[i].marca << endl;
        fileEstacoes << estacoes[i].faturacao << endl;
        if (estacoes[i].capacidade_atual == 0) {
            fileEstacoes << "ET não possui carros de momento" << endl;
        }
        else {
            for (int h = 0; h < estacoes[i].capacidade_atual; h++)
            {
                fileEstacoes << estacoes[i].carros[h].id << endl;
                fileEstacoes << estacoes[i].carros[h].marca << endl;
                fileEstacoes << estacoes[i].carros[h].modelo << endl;
                fileEstacoes << estacoes[i].carros[h].prioridade << endl;
                fileEstacoes << estacoes[i].carros[h].tempo_reparacao << endl;
                fileEstacoes << estacoes[i].carros[h].dias_ET << endl;
            }
        }
    }
}

void gravarOficina(carro* listadeespera, int num_carros_criados, carro* not_added, int num_not_added, ET* estacoes) {
    gravarCarros(listadeespera, num_carros_criados);
    gravarListaDeEspera(not_added, num_not_added);
    gravarCarrosReparados(estacoes);
    gravarEstacoes(estacoes);
}

//void carregarOficina(carro* listadeespera, carro* not_added, ET* estacoes) {
//    carregarCarros(listadeespera);
//    carregarListaDeEspera(not_added);
//    carregarCarrosReparados(estacoes);
//}