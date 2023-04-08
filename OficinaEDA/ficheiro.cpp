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
//
//void carregarOficina() {
//    string linha;
//
//    fstream file("oficina.txt");
//    if (file.is_open()) {
//        while (getline(file, linha)) {
//            if (linha[0] != '-') {
//                
//            }
//        }
//    }
//
//    else {
//        cout << "Erro ao abrir o ficheiro" << endl;
//    }
//
//    file.close();
//}

void gravarOficina(ET* estacoes, carro* listadeespera, int NUM_CARROS_CRIADOS, carro* not_added, int num_not_added) {
    std::locale::global(locale(""));

    ofstream outfile;
    outfile.open("oficina.txt");

    for (int i = 0; i < NUM_ETS; i++)
    {
        outfile << estacoes[i].id << endl;
        outfile << estacoes[i].mecanico << endl;
        outfile << estacoes[i].capacidade << endl;
        outfile << estacoes[i].capacidade_atual << endl;
        outfile << estacoes[i].marca << endl;
        outfile << estacoes[i].faturacao << endl;

        if (estacoes[i].capacidade_atual == 0) {
            outfile << "ET não possui carros de momento" << endl;
        }
        else {
            for (int j = 0; j < estacoes[i].capacidade_atual; j++)
            {
                outfile << estacoes[i].carros[j].id << endl;
                outfile << estacoes[i].carros[j].marca << "-" << estacoes[i].carros[j].modelo << endl;
                outfile << estacoes[i].carros[j].prioridade << endl;
                outfile << estacoes[i].carros[j].tempo_reparacao << endl;
                outfile << estacoes[i].carros[j].dias_ET << endl;
            }
        }
        if (i < NUM_ETS - 1) {
            outfile << endl;
        }
    }
    /*outfile << endl << endl << endl;



    outfile << "-----------------------------------------------Lista de carros-----------------------------------------------" << endl;
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
        outfile << "Carro " << ": ";
        outfile << "ID: " << listadeespera[i].id << " | ";
        outfile << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
        outfile << "Prioritário: " << listadeespera[i].prioridade << " | ";
        outfile << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
        outfile << "Dias na ET: " << listadeespera[i].dias_ET << endl;
    }
    outfile << endl << endl << endl;



    outfile << "----------------------------------------------Lista de espera---------------------------------------------- - " << endl;
    for (int i = 0; i < num_not_added; i++) {
        outfile << "Carro: ID: " << not_added[i].id << " | ";
        outfile << not_added[i].marca << "-" << not_added[i].modelo << " | ";
        outfile << "Prioritário: " << not_added[i].prioridade << " | ";
        outfile << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
        outfile << "Dias da ET: " << not_added[i].dias_ET << endl;
    }
    outfile << endl << endl << endl;



    outfile << "-----------------------------------------------Carros reparados-----------------------------------------------" << endl;
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
    }*/

    outfile.close();
}

void carregarOficina() {
    ifstream file;
    file.open("oficina.txt");
    string linha;
    int count = 0;

    if (file.is_open()) {
        while (getline(file, linha) && count < 6) {
            cout << linha << endl;
            count++;
        }
        while (getline(file, linha)) {
            if (linha[0] == ' ') {
                count = 0;
            }
            else if (count == 6) { 
                cout << linha << endl;
                count = 0;
            }
            else {
                count++;
            }
        }
    }
    else {
        cout << "Não foi possível abrir o ficheiro." << endl;
    }

    file.close();
}