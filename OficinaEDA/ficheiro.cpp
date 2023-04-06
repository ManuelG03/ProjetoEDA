#include <iostream>
#include <fstream>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

void gravarOficina(ET* estacoes, carro* listadeespera, int NUM_CARROS_CRIADOS, carro* not_added, int num_not_added) {
    ofstream outfile;
    outfile.open("oficina.txt");

    outfile << "--------------------Lista de carros--------------------" << endl;
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
        carro car_waiting = listadeespera[i];
        outfile << "Carro " << ": ";
        outfile << "ID: " << car_waiting.id << " | ";
        outfile << car_waiting.marca << "-" << car_waiting.modelo << " | ";
        outfile << "Prioritário: " << car_waiting.prioridade << " | ";
        outfile << "Tempo Reparação: " << car_waiting.tempo_reparacao << " | ";
        outfile << "Dias na ET: " << car_waiting.dias_ET << endl;
    }
    outfile << endl << endl;

    outfile << "------------------Lista de espera------------------" << endl;
    for (int i = 0; i < num_not_added; i++) {
        outfile << "Carro: ID: " << not_added[i].id << " | ";
        outfile << not_added[i].marca << "-" << not_added[i].modelo << " | ";
        outfile << "Prioritário: " << not_added[i].prioridade << " | ";
        outfile << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
        outfile << "Dias da ET: " << not_added[i].dias_ET << endl;
    }
    outfile << endl << endl;

    outfile << "--------------------Carros reparados--------------------" << endl;
    for (int i = 0; i < NUM_ETS; i++) {
        outfile << "ET " << i + 1 << ":" << endl;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            outfile << "Carro " << j + 1 << ": ";
            outfile << "ID: " << estacoes[i].regRepCars[j].id << " | ";
            outfile << estacoes[i].regRepCars[j].marca << "-" << estacoes[i].regRepCars[j].modelo << " | ";
            outfile << "Prioritário: " << estacoes[i].regRepCars[j].prioridade << " | ";
            outfile << "Tempo Reparação: " << estacoes[i].regRepCars[j].tempo_reparacao << " | ";
            outfile << "Dias na ET: " << estacoes[i].regRepCars[j].dias_ET << endl;
        }
        outfile << endl;
    }
    outfile << endl << endl;

    outfile.close();
}