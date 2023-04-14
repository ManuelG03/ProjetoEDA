#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "oficina.h"
#include "constantes.h"
#include "structs.h"
#include "string.h"
#include "ficheiro.h"

using namespace std;

int NUM_CARROS_CRIADOS = 0;
int id_lista = 0;
int car_ids[100];
int num_car_ids = 0;
int num_carros_reparados = 0;
int num_not_added;
int HOLD_nca;


void inicializarEstacoes(ET* estacoes, string* marcas) {        //Função para inicializar estações
    string file = "marcas.txt";                                 //Abrir ficheiro marcas.txt
    ifstream fileMarcas(file);

    string marca;

    int id_estacao = 1;                                         //Inicializar o id das estações a 1

    if (fileMarcas.is_open()) {
        int i = 0;
        while (!fileMarcas.eof()) {
            getline(fileMarcas, marcas[i++]);                   //Guardar todas as marcas do ficheiro num array chamado marcas
        }
    }

    for (int i = 0; i < NUM_ETS; i++)
    {
        cout << "Introduza o mecânico para a estação " << i << ": ";
        getline(cin, estacoes[i].mecanico);                     //O nome do mecânico é introduzido pelo utilizador e adicionado ao array estacoes
        estacoes[i].id = id_estacao++;                          //O id da estação é incrementado
        estacoes[i].capacidade = rand() % 4 + 2;                //A capacidade de cada estacao é um valor aleatório entre 3 a 5
        estacoes[i].capacidade_atual = 0;                       //A capacidade atual de cada estação é inicializada a 0
        estacoes[i].marca = marcas[rand() % NUM_MARCAS];        //A marca de cada estação é retirada aleatóriamente do array marcas
        estacoes[i].carros = new carro[estacoes[i].capacidade]; //Inicializado um array de carros para cada estação
        estacoes[i].regRepCars = new carro[LIMITE];             //Inicializado um array regRepCars para os carros reparados de cada estação
        estacoes[i].faturacao = 0;                              //A faturação de cada estação é inicializada a 0
        estacoes[i].carros_reparados = 0;                       //O número de carros reparados de cada estação inicialmente é 0
    }

    fileMarcas.close();                                         //Fechar o ficheiro marcas.txt


}

void obtemMarcasET(string* marcas, string* marcas_ET, ET* estacoes) { //Função para obter as marcas de cada estação criada
    for (int i = 0; i < NUM_ETS; i++) {
        marcas_ET[i] = estacoes[i].marca;                             //Igualar a cada posição do array marcas_ET, cada marca de cada estação
    }
}

void criarCarros(carro* listadeespera, string* modelos, string* marcas_ET) {
    string file2 = "modelos.txt";
    ifstream fileModelos(file2);

    if (fileModelos.is_open()) {
        int i = 0;
        while (!fileModelos.eof()) {
            getline(fileModelos, modelos[i++]);
        }
    }

    for (int i = NUM_CARROS_CRIADOS; i < NUM_CARROS_CRIADOS + 10; i++) {
        listadeespera[i].id = id_lista + 1;
        listadeespera[i].tempo_reparacao = rand() % 6 + 2;
        listadeespera[i].marca = marcas_ET[rand() % NUM_ETS];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % NUM_MODELOS];
        listadeespera[i].custo_reparacao = rand() % 71 + 60;

        int decisao = rand() % 100;
        listadeespera[i].prioridade = (decisao <= 5);

        id_lista++;
    }
    NUM_CARROS_CRIADOS += 10;
    sort(listadeespera, listadeespera + NUM_CARROS_CRIADOS, comparaCarros);

    fileModelos.close();
}

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro*& not_added_copy) {
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
                if (estacoes[j].capacidade - estacoes[j].capacidade_atual > 0) {
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
    
    //verNotAdded(not_added_copy); SERVE PARA VER A LISTA DE ESPERA REAL!
}

bool comparaCarros(const carro& a, const carro& b) {
    if (a.prioridade && !b.prioridade) {
        return true;
    }

    return false;
}

bool compareCarrosByMarca(const carro& a, const carro& b) {
    return a.marca < b.marca;
}

void reparacaoManual(ET* estacoes) {
    string marca;
    string modelo;
    cout << "Reparação Manual" << endl;

    cout << "Marca: " << endl;
    cin.ignore();
    getline(cin, marca);

    cout << "Modelo: " << endl;
    getline(cin, modelo);

    for (int i = 0; i < NUM_ETS; i++) {
        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            if (estacoes[i].carros[h].marca == marca && estacoes[i].carros[h].modelo == modelo) {
                for (int j = h; j < estacoes[i].capacidade_atual - 1; j++) {
                    estacoes[i].carros[j] = estacoes[i].carros[j + 1];
                }
                estacoes[i].regRepCars[estacoes[i].carros_reparados] = estacoes[i].carros[h];
                estacoes[i].carros_reparados++;
                estacoes[i].capacidade_atual--;
            }
        }
    }
}

void atualiza_tempo_rep(carro* not_added_copy) {
    int tempoRep;
    string marca, modelo;
    bool carroEncontrado = false;

    cout << "Atualizar tempo de reparação" << endl;

    cout << "Marca: " << endl;
    cin.ignore();
    getline(cin, marca);

    cout << "Modelo: " << endl;
    getline(cin, modelo);

    for (int i = 0; i < num_not_added; i++) {
        if (not_added_copy[i].marca == marca && not_added_copy[i].modelo == modelo) {
            cout << "Insira o novo tempo de reparacao (em dias): " << endl;
            cin >> tempoRep;
            not_added_copy[i].tempo_reparacao = tempoRep;
            carroEncontrado = true;
        }
    }
    if (!carroEncontrado) {
        cout << "Não existe nenhum carro desse modelo/marca na fila de espera." << endl;
    }
}

void menu(ET* estacoes, carro* listadeespera) {
    cout << "--------------------------------------------------------------------" << endl;
    for (int i = 0; i < NUM_ETS; i++)
    {
        cout << "ET: " << estacoes[i].id << " | ";
        cout << "Mecânico: " << estacoes[i].mecanico << " | ";
        cout << "Capacidade: " << estacoes[i].capacidade << " | ";
        cout << "Carros: " << estacoes[i].capacidade_atual << " | ";
        cout << "Marca: " << estacoes[i].marca << " | ";
        cout << "Total de Faturação: " <<  estacoes[i].faturacao << "$" << endl;

        if (estacoes[i].capacidade_atual == 0) {
            cout << "ET não possui carros de momento" << endl;
        }
        else {
            for (int h = 0; h < estacoes[i].capacidade_atual; h++)
            {
                cout << "Carro: ID: " << estacoes[i].carros[h].id << " | ";
                cout << estacoes[i].carros[h].marca << "-" << estacoes[i].carros[h].modelo << " | ";
                if (estacoes[i].carros[h].prioridade) {
                    cout << "Prioritário: Sim" << " | ";
                }
                else{
                    cout << "Prioritário: Não" << " | ";
                }
                cout << "Tempo Reparação: " << estacoes[i].carros[h].tempo_reparacao << " | ";
                cout << "Dias da ET: " << estacoes[i].carros[h].dias_ET << endl;
            }
        }
        cout << "--------------------------------------------------------------------" << endl;

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
    cout << "------------------LISTA DE ESPERA------------------" << endl;
    for (int i = 0; i < num_not_added; i++) {
        cout << "Carro: ID: " << not_added[i].id << " | ";
        cout << not_added[i].marca << "-" << not_added[i].modelo << " | ";
        if (not_added[i].prioridade) {
            cout << "Prioritário: Sim" << " | ";
        }
        else {
            cout << "Prioritário: Não" << " | ";
        }
        cout << "Tempo Reparação: " << not_added[i].tempo_reparacao << " | ";
        cout << "Dias da ET: " << not_added[i].dias_ET << endl;
    }
    cout << "---------------------------------------------------" << endl;
}

void reparar_carros2(ET* estacoes, int num_estacoes) {
    if (NUM_CARROS_CRIADOS == 0) {
        return;
    }
    for (int i = 0; i < num_estacoes; i++) {
        num_carros_reparados = 0;
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            carro* car = &estacoes[i].carros[j];
            if (car->dias_ET <= car->tempo_reparacao) {
                int probabilidade = rand() % 100 + 1;
                if (probabilidade <= 15) {
                    estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *car;
                    num_carros_reparados++;
                    estacoes[i].faturacao += car->custo_reparacao;
                    cout << "O carro com o ID " << car->id << " foi reparado na ET " << estacoes[i].id << "." << endl;
                }
            }
            else {
                estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *car;
                num_carros_reparados++;
                cout << "O carro com o ID " << car->id << " foi removido da ET " << estacoes[i].id << " por ter ultrapassado o tempo máximo de reparação." << endl;
            }
        }

        int nova_capacidade_atual = estacoes[i].capacidade_atual - num_carros_reparados;
        carro* new_carros = new carro[25];
        int new_index = 0;

        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            carro* car = &estacoes[i].carros[j];
            bool carro_removido = false;
            for (int k = 0; k < estacoes[i].carros_reparados; k++) { 
                if (car->id == estacoes[i].regRepCars[k].id) {
                    carro_removido = true;
                    break;
                }
            }
            if (!carro_removido) {
                new_carros[new_index++] = *car;
            }
        }

        delete[] estacoes[i].carros;
        estacoes[i].carros = new_carros;
        estacoes[i].capacidade_atual = nova_capacidade_atual;
    }
    cout << endl;
}

void incrementar_dias_ET(ET* estacoes, int num_estacoes) {
    for (int i = 0; i < num_estacoes; i++) {
        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            cout << "dias_et: " << estacoes[i].carros[h].dias_ET << endl;
        }
    }
    if (NUM_CARROS_CRIADOS == 0) {
        return;
    }
    for (int i = 0; i < num_estacoes; i++) {
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            estacoes[i].carros[j].dias_ET++;
        }
    }
}

//void imprimeOficina(ET* estacoes, carro* listadeespera) {
//    carro* listadeespera_copy = new carro[NUM_CARROS_CRIADOS];
//    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {
//        listadeespera_copy[i] = listadeespera[i];
//    }
//
//    int range = NUM_CARROS_CRIADOS;
//    for (int i = 0; i < NUM_ETS; i++) {
//        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
//            carro car_reparado = estacoes[i].regRepCars[j];
//            for (int k = 0; k < range; k++) {
//                if (listadeespera_copy[k].id == car_reparado.id) {
//                    for (int l = k; l < range - 1; l++) {
//                        listadeespera_copy[l] = listadeespera_copy[l + 1];
//                    }
//                    range--;
//                }
//            }
//        }
//    }
//
//    int escolha;
//    cout << "(1). ordenar por marca, por ordem alfabética. \n(2). ordenar por tempo de reparação" << endl;
//    cout << ">> ";
//    cin >> escolha;
//
//
//    carro* newlist = new carro[range];
//    int newlistindex = 0;
//    for (int i = 0; i < range; i++) {
//        bool carinrepcars = false;
//        bool caradded = false;
//        for (int j = 0; j < NUM_ETS; j++) {
//            for (int k = 0; k < estacoes[j].carros_reparados; k++) {
//                if (listadeespera_copy[i].id == estacoes[j].regRepCars[k].id) {
//                    carinrepcars = true;
//                    break;
//                }
//            }
//            if (carinrepcars) {
//                break;
//            }
//        }
//        if (!carinrepcars) {
//            for (int j = 0; j < newlistindex; j++) {
//                if (listadeespera_copy[i].id == newlist[j].id) {
//                    caradded = true;
//                    break;
//                }
//            }
//            //adiciona a newlist se ainda nao foi
//            if (!caradded) {
//                newlist[newlistindex] = listadeespera_copy[i];
//                newlistindex++;
//            }
//        }
//    }
//
//    if (escolha == 1) {
//        for (int i = 0; i < newlistindex - 1; i++) {
//            for (int j = i + 1; j < newlistindex; j++) {
//                if (newlist[i].marca > newlist[j].marca) {
//                    carro temp = newlist[i];
//                    newlist[i] = newlist[j];
//                    newlist[j] = temp;
//                }
//            }
//        }
//    }
//
//    if (escolha == 2) {
//        for (int i = 0; i < newlistindex - 1; i++) {
//            for (int j = i + 1; j < newlistindex; j++) {
//                if (newlist[i].tempo_reparacao > newlist[j].tempo_reparacao) {
//                    carro temp = newlist[i];
//                    newlist[i] = newlist[j];
//                    newlist[j] = temp;
//                }
//            }
//        }
//    }
//
//
//    if (escolha != 1 && escolha != 2) {
//        return;
//    }
//
//
//
//    cout << "----------------------------------------" << endl;
//    cout << "lista de carros (et + lista de espera) :" << endl;
//    for (int i = 0; i < newlistindex; i++) {
//        cout << "id: " << newlist[i].id << " | ";
//        cout << newlist[i].marca << "-" << newlist[i].modelo << " | ";
//        cout << "prioritário: " << newlist[i].prioridade << " | ";
//        cout << "tempo reparação: " << newlist[i].tempo_reparacao << " | ";
//        cout << "dias na et: " << newlist[i].dias_ET << endl;
//    }
//    delete[] newlist;
//    cout << endl;
//}

void imprimeOficina(ET* estacoes, carro* listadeespera, carro* not_added_copy) {
    /*cout << "carros carregados do arquivo: " << endl;
    for (int i = 0; i < 30; i++) {
        cout << "id: " << listadeespera[i].id << endl;
        cout << "marca: " << listadeespera[i].marca << endl;
        cout << "modelo: " << listadeespera[i].modelo << endl;
        cout << "prioridade: " << listadeespera[i].prioridade << endl;
        cout << "tempo de reparação: " << listadeespera[i].tempo_reparacao << endl;
        cout << "dias na et: " << listadeespera[i].dias_ET << endl;
        cout << endl;
    }*/

    /*cout << "number of not added cars: " << endl;
    for (int i = 0; i < num_not_added; i++) {
        cout << "car " << i + 1 << endl;
        cout << "\tid: " << not_added_copy[i].id << endl;
        cout << "\tmarca: " << not_added_copy[i].marca << endl;
        cout << "\tmodelo: " << not_added_copy[i].modelo << endl;
        cout << "\tprioridade: " << not_added_copy[i].prioridade << endl;
        cout << "\ttempo de reparação: " << not_added_copy[i].tempo_reparacao << endl;
        cout << "\tdias em espera: " << not_added_copy[i].dias_ET << endl;
    }*/

    for (int i = 0; i < NUM_ETS; i++) {
        cout << "estação id: " << estacoes[i].id << "\n";
        cout << "mecanico: " << estacoes[i].mecanico << "\n";
        cout << "capacidade: " << estacoes[i].capacidade << "\n";
        cout << "capacidade_atual: " << estacoes[i].capacidade_atual << "\n";
        cout << "marca: " << estacoes[i].marca << "\n";
        cout << "faturacao: " << estacoes[i].faturacao << "\n";

        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            cout << "carro id: " << estacoes[i].carros[h].id << "\n";
            cout << "marca: " << estacoes[i].carros[h].marca << "\n";
            cout << "modelo: " << estacoes[i].carros[h].modelo << "\n";
            cout << "prioridade: " << estacoes[i].carros[h].prioridade << "\n";
            cout << "tempo_reparacao: " << estacoes[i].carros[h].tempo_reparacao << "\n";
            cout << "dias_et: " << estacoes[i].carros[h].dias_ET << endl;
        }

        cout << "carros_reparados: " << estacoes[i].carros_reparados << endl;
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            cout << "carro id: " << estacoes[i].regRepCars[j].id << endl;
            cout << "marca: " << estacoes[i].regRepCars[j].marca << endl;
            cout << "modelo: " << estacoes[i].regRepCars[j].modelo << endl;
            cout << "prioridade: " << estacoes[i].regRepCars[j].prioridade << endl;
            cout << "tempo_reparacao: " << estacoes[i].regRepCars[j].tempo_reparacao << endl;
            cout << "dias_et: " << estacoes[i].regRepCars[j].dias_ET << endl;
        }

        cout << endl;
    }
}

//void printAllCarsInRegRepCars(ET* estacoes) {
//    cout <<  "CARROS JÁ REPARADOS: " << "INFO MANUEL " << "APAGAR" << endl;
//    for (int i = 0; i < NUM_ETS; i++) {
//        cout << "ET " << i + 1 << ":" << endl;
//        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
//            cout << "Carro " << j + 1 << ": ";
//            cout << "ID: " << estacoes[i].regRepCars[j].id << " | ";
//            cout << estacoes[i].regRepCars[j].marca << "-" << estacoes[i].regRepCars[j].modelo << " | ";
//            cout << "Prioritário: " << estacoes[i].regRepCars[j].prioridade << " | ";
//            cout << "Tempo Reparação: " << estacoes[i].regRepCars[j].tempo_reparacao << " | ";
//            cout << "Dias na ET: " << estacoes[i].regRepCars[j].dias_ET << endl;
//        }
//        cout << endl;
//    }
//}

void menuInicial(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET, int NUM_ETS) {
    bool sair = false;
    char escolha = ' ';

    do {
        cout << "***** Bem Vindo Gestor ***** \n";
        cout << "(1).Reparação Manual \n";
        cout << "(2).Atualizar tempo de reparação \n";
        cout << "(3).Adicionar Prioridade\n";
        cout << "(4).Remover Mecânico\n";
        cout << "(5).Gravar Oficina \n";
        cout << "(6).Carregar Oficina \n";
        cout << "(7).Imprimir Oficina \n";
        cout << "(9). Voltar Atrás \n";
        cout << "(0).Sair" << endl;
        cout << "Selecione a sua opção:";
        cin >> escolha;
        switch (escolha)
        {
        case '1':
            reparacaoManual(estacoes);
            break;
        case '2':
            atualiza_tempo_rep(not_added_copy);
            break;
        case '3':; break;
        case '4':; break;
        case '5':
            gravarOficina(listadeespera, NUM_CARROS_CRIADOS, not_added_copy, num_not_added, estacoes);
            break;
        case '6':
            NUM_ETS = numEstacoes();
            NUM_CARROS_CRIADOS = numCarrosCriados();
            num_not_added = numListaDeEspera();
            estacoes = carregarEstacoes(estacoes);
            not_added_copy = carregarListaDeEspera(not_added_copy);
            listadeespera = carregarCarros(listadeespera);
            marcas_ET = obtemMarcasETnova(marcas_ET, estacoes, NUM_ETS);
            break;
        case '7':
            imprimeOficina(estacoes, listadeespera, not_added_copy);
            break;
        case '9':
            simulateDay(estacoes, listadeespera, not_added_copy, modelos, marcas_ET);
            break;
        case '0': cout << "Selecionou a opção sair! " << endl;
            exit(0);
            break;
        default: cout << "Escolha Inválida!" << endl;
            break;
        }
    } while (!sair);
    cin.ignore();
}

void simulateDay(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET) {
    char opcao = ' ';
    bool sair = false;

    do {
        cout << endl;
        cout << "(s): Simular um dia " << endl;
        cout << "(g): Painel de gestão" << endl;
        cout << "(0): SAIR" << endl;
        cin >> opcao;
        switch (opcao) {
        case 's':
        case 'S':
            cout << "Dia simulado com sucesso!\n";
            incrementar_dias_ET(estacoes, NUM_ETS);
            reparar_carros2(estacoes, NUM_ETS);
            criarCarros(listadeespera, modelos, marcas_ET);
            adicionarCarrosETs(listadeespera, estacoes, not_added_copy);
            menu(estacoes, listadeespera);
            break;
        case 'g':
        case 'G':
            menuInicial(estacoes, listadeespera, not_added_copy, modelos, marcas_ET, NUM_ETS);
            break;
        case '0':
            exit(0);
            cout << "Até à proxima!\n";
            break;
        default:
            cout << "Escolha inválida!" << endl;
            break;
        }
    } while (!sair);
}
