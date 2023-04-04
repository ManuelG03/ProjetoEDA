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
    outfile << "Dados da oficina:" << endl << endl;

    for (int i = 0; i < NUM_ETS; i++)
    {
        outfile << "ET: " << estacoes[i].id << " | ";
        outfile << "Mecânico: " << estacoes[i].mecanico << " | ";
        outfile << "Capacidade: " << estacoes[i].capacidade << " | ";
        outfile << "Carros: " << estacoes[i].capacidade_atual << " | ";
        outfile << "Marca: " << estacoes[i].marca << " | ";
        outfile << "Total de Faturação: " << estacoes[i].faturacao << "$" << endl;

        if (estacoes[i].capacidade_atual == 0) {
            outfile << "ET não possui carros de momento" << endl;
        }
        else {
            for (int h = 0; h < estacoes[i].capacidade_atual; h++)
            {
                outfile << "Carro: ID: " << estacoes[i].carros[h].id << " | ";
                outfile << estacoes[i].carros[h].marca << "-" << estacoes[i].carros[h].modelo << " | ";
                outfile << "Prioritário: " << estacoes[i].carros[h].prioridade << " | ";
                outfile << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
                outfile << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
            }
        }
        outfile << "--------------------------------------------------------------------" << endl;
    }


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