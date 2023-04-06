#include <iostream>
#include <fstream>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

void gravarOficina(ET* estacoes, carro* listadeespera) {
    ofstream outfile;
    outfile.open("oficina.txt");
    outfile << "Dados da oficina:" << endl;
    outfile << "Carros reparados: " << endl;
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
    outfile.close();
}