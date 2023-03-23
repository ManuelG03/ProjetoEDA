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


                    for (int k = i; k < NUM_CARROS_A_CRIAR - 1; k++) {
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
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++)
    {
        cout << "Carro: ID: " << " | ";
        cout << " | ";
        cout << "Prioritario: " << " | ";
        cout << "Tempo Reparação: " << " | ";
        cout << "Dias da ET: " << endl;
    }
}

void ciclo(carro* listadeespera, string* modelos, string* marcas) {
    criarCarros(listadeespera, modelos, marcas);
}

void gravarOficina(ET* estacoes, carro* listadeespera){
    ofstream outputFile;
    outputFile.open("dadosOficina.txt", ios::out);

    if (outputFile.is_open()) {
        outputFile << "--------------------------------------------OFICINA--------------------------------------------\n";
        for (int i = 0; i < NUM_ETS; i++)
        {
            outputFile << "ET: " << estacoes[i].id << " | ";
            outputFile << "Mecânico: " << estacoes[i].mecanico << " | ";
            outputFile << "Capacidade: " << estacoes[i].capacidade << " | ";
            outputFile << "Carros: " << estacoes[i].capacidade_atual << " | ";
            outputFile << "Marca: " << estacoes[i].marca << " | ";
            outputFile << "Total de Faturação: " << endl;

            if (estacoes[i].capacidade_atual == 0) {
                outputFile << " ET não possui carros de momento" << endl;
            }
            else {
                for (int h = 0; h < estacoes[i].capacidade_atual; h++)
                {
                    outputFile << "Carro: ID: " << estacoes[i].carros[h].id << " | ";
                    outputFile << estacoes[i].carros[h].marca << "-" << estacoes[i].carros[h].modelo << " | ";
                    outputFile << "Prioritário: " << estacoes[i].carros[h].prioridade << " | ";
                    outputFile << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
                    outputFile << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
                }
            }
        }

        cout << "\nOs dados da oficina foram escritos no ficheiro com sucesso.";

        outputFile.close();
    }
    else {
        cout << "Erro ao abrir o ficheiro.\n";
    }
}

void carregarOficina() {

}

int menuInicio(ET* estacoes, carro* listadeespera) {
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
        case 1:
            ; 
            break;
        case 2:
            ; 
            break;
        case 3:
            ; 
            break;
        case 4:
            ; 
            break;
        case 5:
            gravarOficina(estacoes, listadeespera);
            break;
        default: 
            cout << "Escolha Inválida!"; 
            break;
        }
    } while (escolha > 6);
    return 0;
}