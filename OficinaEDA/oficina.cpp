#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "oficina.h"
#include "constantes.h"
#include "structs.h"
#include "string.h"

using namespace std;


int NUM_CARROS_CRIADOS = 0;
int id_lista = 0;
int car_ids[100];
int num_car_ids = 0;
int num_carros_reparados = 0;
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
        estacoes[i].regRepCars = new carro[LIMITE];
        estacoes[i].faturacao = 0;
        estacoes[i].carros_reparados = 0;
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
        listadeespera[i].custo_reparacao = rand() % 71 + 60;


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

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro* not_added_copy) {
    int num_carros_adicionados = 0;
    int i = 0;
    int f = 0;
    int x = 0;
    int carange = NUM_CARROS_CRIADOS;
    carro* not_added = new carro[carange];
    bool car_added;
    bool ALFA = false;
    bool BETA = false;
    bool AURIS = false;
    bool JAESTA = false;
    int GAMA = 0;
    num_not_added = 0;
    while (i < carange) {
        car_added = false;
        bool car_id_exists = false;
        bool reny = false;
        for (int j = 0; j < NUM_ETS; j++) {
            if (estacoes[j].marca == listadeespera[i].marca) {
                if (estacoes[j].capacidade > 0) {
                    //bool car_id_exists = false;
                    for (int k = 0; k < num_car_ids; k++) {
                        if (listadeespera[i].id == car_ids[k]) {
                            car_id_exists = true;
                            car_added = true;
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
            for (int r = 0; r < num_car_ids; r++) {
                if (car_ids[r] == listadeespera[i].id) {
                    reny = true;
                    
                }
            }
            if (reny == false) {
                not_added[num_not_added] = listadeespera[i];
                num_not_added++;
            }
        }
        if (num_carros_adicionados == 8) {
            BETA = true;
            break;
        }
        i++;
    }
    
    if (BETA == true) { //8+
        while (GAMA < carange) {
            AURIS = false;
            JAESTA = false;
            for (int y = 0; y < num_car_ids; y++) {
                if (car_ids[y] == listadeespera[GAMA].id) {
                    AURIS = true; 
                    //cout << "ID:" << car_ids[y] << " ja tem ET." << endl; NAO APAGAR
                }
            }
            for (int w = 0; w < num_not_added; w++) { 
                
                if (listadeespera[GAMA].id == not_added[w].id) {
                    JAESTA = true;
                    //cout << "ID:" << not_added[w].id << " ja esta no not_added." << endl; NAO APAGAR
                }
            }
            //cout << AURIS << " | " << JAESTA << endl;  NAO APAGAR
            if (AURIS == false && JAESTA == false) {
                not_added[num_not_added] = listadeespera[GAMA];
                num_not_added++;
            }
            GAMA++;
        }

    }
    
    cout << "\n" << num_carros_adicionados << " carros adicionados às ETs.\n" << endl;
    //cout << num_car_ids << num_not_added << endl;
    //for (int L = 0; L < num_car_ids +1 ; L++) {
      //  cout << car_ids[L] << " | ";

    //
    HOLD_nca = num_not_added;
    not_added_copy = not_added;
    
    verNotAdded(not_added_copy);
}

bool comparaCarros(const carro& a, const carro& b) {
    if (a.prioridade == "Sim" && b.prioridade != "Sim") {
        return true;
    }

    return false;
}

bool compareCarrosByMarca(const carro& a, const carro& b) {
    return a.marca < b.marca;
}

void menu(ET* estacoes, carro* listadeespera) {
    for (int i = 0; i < NUM_ETS; i++)
    {
        cout << "ET: " << estacoes[i].id << " | ";
        cout << "Mecânico: " << estacoes[i].mecanico << " | ";
        cout << "Capacidade: " << estacoes[i].capacidade << " | ";
        cout << "Carros: " << estacoes[i].capacidade_atual << " | ";
        cout << "Marca: " << estacoes[i].marca << " | ";
        cout << "Total de Faturação: " <<  estacoes[i].faturacao << "€ | " << endl;

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
    cout << endl;

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
    cout << "------------------LISTA DE ESPERA------------------" << endl;
    for (int i = 0; i < num_not_added; i++) {
        cout << "Carro: ID: " << not_added[i].id << " | ";
        cout << not_added[i].marca << "-" << not_added[i].modelo << " | ";
        cout << "Prioritario: " << not_added[i].prioridade << " | ";
        cout << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << not_added[i].dias_ET << endl;
    }
    cout << "---------------------------------------------------" << endl;
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

void reparacaoCarros(ET* estacoes) {
    int pen = 0;
    srand(time(NULL));
    int probRep = rand() % 100 + 1;
    while (pen < NUM_ETS) {

    }
    

}
void reparar_carros(ET* estacoes, int num_estacoes) {
    for (int i = 0; i < num_estacoes; i++) {
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            int probabilidade = rand() % 100 + 1;
            if (probabilidade <= 15) {
                carro car = estacoes[i].carros[j];
                estacoes[i].capacidade_atual--;
                estacoes[i].capacidade++; //ATENCAO
                for (int k = j; k < estacoes[i].capacidade_atual; k++) {
                    estacoes[i].carros[k] = estacoes[i].carros[k + 1];
                }
                estacoes[i].regRepCars[j] = car;
                cout << "O carro com id " << car.id << " foi reparado na ET " << estacoes[i].id << endl;
                j--; // ATENÇAO
            }
        }
    }
    cout << endl;
}

void reparar_carros2(ET* estacoes, int num_estacoes) {
    for (int i = 0; i < num_estacoes; i++) {
        num_carros_reparados = 0;
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            carro* car = &estacoes[i].carros[j];
            if (car->dias_ET < car->tempo_reparacao) {
                int probabilidade = rand() % 100 + 1;
                if (probabilidade <= 50) {
                    estacoes[i].capacidade_atual--;
                    estacoes[i].capacidade++;
                    for (int k = j; k < estacoes[i].capacidade_atual; k++) {
                        estacoes[i].carros[k] = estacoes[i].carros[k + 1];
                    }
                    estacoes[i].regRepCars[num_carros_reparados++] = *car;
                    estacoes[i].faturacao += car->custo_reparacao;
                    estacoes[i].carros_reparados++;
                    cout << "O carro com o ID " << car->id << " foi reparado na ET " << estacoes[i].id << "." << endl;
                    j--; //VERIFICAR A POSIÇAO ATUAL
                }
            }
            else {

                estacoes[i].capacidade_atual--;
                estacoes[i].capacidade++;
                for (int k = j; k < estacoes[i].capacidade_atual; k++) {
                    estacoes[i].carros[k] = estacoes[i].carros[k + 1];
                }
                estacoes[i].regRepCars[num_carros_reparados++] = *car;
                estacoes[i].carros_reparados++;
                j--; // VERIFICAR(again) posicao atual
                cout << "O carro com o ID " << car->id << " foi removido da ET " << estacoes[i].id << " por ter ultrapassado o tempo máximo de reparação." << endl;
            }
        }
    }
    cout << endl;
}




void incrementar_dias_ET(ET* estacoes, int num_estacoes) {
    for (int i = 0; i < num_estacoes; i++) {
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            estacoes[i].carros[j].dias_ET++;
        }
    }
}

void criaimprimeOficina(ET* estacoes, carro* listadeespera, carro* imprime) {
    int index = 0;
    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
        bool found = false;
        for (int j = 0; j < NUM_ETS; j++) {
            for (int h = 0; h < estacoes[j].capacidade_atual; h++) {
                if (listadeespera[i].id == estacoes[j].regRepCars[h].id) {
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            imprime[index] = listadeespera[i];
            index++;
        }
    }
    int holdon = NUM_CARROS_CRIADOS - num_carros_reparados;
    sort(imprime, imprime + holdon, compareCarrosByMarca);

    cout << "Lista de carros na oficina (ETs + Lista de Espera)" << endl;

    for (int i = 0; i < holdon; i++) {
        cout << "Carro: ID: " << imprime[i].id << " | ";
        cout << imprime[i].marca << "-" << imprime[i].modelo << " | ";
        cout << "Prioritário: " << imprime[i].prioridade << " | ";
        cout << "Tempo Reparação: " << imprime[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << imprime[i].dias_ET << endl;
    }
    cout << "---------------------------------------------------" << endl;
}


void printAllCarsInRegRepCars(ET* estacoes) {
    cout <<  "CARROS JÁ REPARADOS:" << "INFO MANUEL" << "APAGAR" << endl;
    for (int i = 0; i < NUM_ETS; i++) {
        cout << "ET " << i + 1 << ":" << endl;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            cout << "Carro " << j + 1 << ": ";
            cout << "ID: " << estacoes[i].regRepCars[j].id << " | ";
            cout << estacoes[i].regRepCars[j].marca << "-" << estacoes[i].regRepCars[j].modelo << " | ";
            cout << "Prioritário: " << estacoes[i].regRepCars[j].prioridade << " | ";
            cout << "Tempo Reparação: " << estacoes[i].regRepCars[j].tempo_reparacao << " | ";
            cout << "Dias na ET: " << estacoes[i].regRepCars[j].dias_ET << endl;
        }
        cout << endl;
    }
}

void simulateDay() {
    bool continua = true;
    while (continua) {
        cout << "Pressione 's' seguido de Enter para simular um dia na OficinaEDA ou 0 para sair: ";
        string Input;
        getline(cin, Input);
        if (Input == "s" || Input == "S") {
            
            cout << "Dia simulado com sucesso!\n";
        }
        else if (Input == "0") {
            continua = false;
        }
        else {
            cout << "Opção Inválida!\n";
        }
    }
}
