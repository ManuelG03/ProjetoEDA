#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "oficina.h"
#include "constantes.h"
#include "structs.h"

using namespace std;


int NUM_CARROS_CRIADOS = 0;
int id_lista = 0;
int car_ids[100];
int num_car_ids = 0;

int num_not_added;
int HOLD_nca;


void inicializarEstacoes(ET* estacoes, string* marcas) {
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

    fileMarcas.close();

    
}

void obtemMarcasET(string* marcas, string* marcas_ET, ET* estacoes) {
    for (int i = 0; i < NUM_ETS; i++) {
        marcas_ET[i] = estacoes[i].marca;
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
        listadeespera[i].marca = marcas[rand() % NUM_ETS];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % NUM_MODELOS];

        int decisao = rand() % 100;
        if (decisao > 5) {
            listadeespera[i].prioridade = "Não";
        }
        else listadeespera[i].prioridade = "Sim";

        id_lista++;
    }
    NUM_CARROS_CRIADOS += 10;
    sort(listadeespera, listadeespera + NUM_CARROS_CRIADOS, comparaCarros);

    fileModelos.close();
}

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro* not_added) {

    int num_carros_adicionados = 0;
    int i = 0;
    int f = 0;
    int carange = NUM_CARROS_CRIADOS;
    bool car_added;
    num_not_added = 0;
    bool car_id_exists = false;  // Add this line

    while (num_carros_adicionados < 8 && i < carange) {
        car_added = false;
        car_id_exists = false;  // Reset the flag for each car

        for (int j = 0; j < NUM_ETS; j++) {
            if (estacoes[j].marca == listadeespera[i].marca) {
                if (estacoes[j].capacidade > 0) {
                    for (int k = 0; k < num_car_ids; k++) {
                        if (listadeespera[i].id == car_ids[k]) {
                            car_id_exists = true;
                            break;
                        }
                    }
                    if (!car_id_exists) {
                        estacoes[j].carros[estacoes[j].capacidade_atual] = listadeespera[i];
                        estacoes[j].capacidade--;
                        estacoes[j].capacidade_atual++;
                        num_carros_adicionados++;
                        car_added = true;
                        car_ids[num_car_ids] = listadeespera[i].id;
                        num_car_ids++;
                        break;
                    }
                }
            }
        }
        if (car_added == false) {
            not_added[num_not_added] = listadeespera[i];
            num_not_added++;
        }
        i++;
    }

    if (num_carros_adicionados == 8 && i < carange) {
        while (i < carange) {
            not_added[num_not_added] = listadeespera[i];
            num_not_added++;
            i++;
        }
    }

    cout << num_carros_adicionados << " carros adicionados às ETs.\n";
    cout << num_not_added << " carros NÃO adicionados ás ETs.\n";
    cout << NUM_CARROS_CRIADOS << " carros criados inicialmente.\n";

    for (int g = 0; g < num_car_ids; g++) {
        cout << car_ids[g];
    }
    HOLD_nca = HOLD_nca + num_carros_adicionados;
}



bool comparaCarros(const carro& a, const carro& b) {
    if (a.prioridade == "Sim" && b.prioridade != "Sim") {
        return true;
    }

    return false;
}

void menu(ET* estacoes, carro* listadeespera) {
    for (int i = 0; i < NUM_ETS; i++)
    {
        cout << "ET: " << estacoes[i].id << " | ";
        cout << "Mecânico: " << estacoes[i].mecanico << " | ";
        cout << "Capacidade: " << estacoes[i].capacidade << " | ";
        cout << "Carros: " << estacoes[i].capacidade_atual << " | ";
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
                cout << "Prioritário: " << estacoes[i].carros[h].prioridade << " | ";
                cout << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
                cout << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
            }
        }
    }

}

void verListaDeEspera(carro* listadeespera) { 
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
        cout << "Carro: ID: " << listadeespera[i].id << " | ";
        cout << listadeespera[i].marca << "-" << listadeespera[i].modelo << " | ";
        cout << "Prioritario: " << listadeespera[i].prioridade << " | ";
        cout << "Tempo Reparação: " << listadeespera[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << listadeespera[i].dias_ET << endl;
    }
}

void verNotAdded(carro* not_added) {
    cout << "------------------NA--------------" << endl;
    for (int i = 0; i < NUM_CARROS_CRIADOS - HOLD_nca; i++) {
        cout << "Carro: ID: " << not_added[i].id << " | ";
        cout << not_added[i].marca << "-" << not_added[i].modelo << " | ";
        cout << "Prioritario: " << not_added[i].prioridade << " | ";
        cout << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << not_added[i].dias_ET << endl;
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
        case 1:; break;
        case 2:; break;
        case 3:; break;
        case 4:; break;
        case 5:; break;
        default: cout << "Escolha Inválida!"; break;
        }
    } while (escolha > 6);
    return 0;
}

void ciclo(carro* listadeespera, string* modelos, string* marcas) {
    criarCarros(listadeespera, modelos, marcas);
}