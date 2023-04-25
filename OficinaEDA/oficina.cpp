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

int NUM_CARROS_CRIADOS = 0;     //Variável para guardar número de carros criados na Oficina
int id_lista = 0;               //Variavel para guardar o ID no array de carros criados
int car_ids[100];               //Array para guardar ID'S dos carros que entram nas ETs
int num_car_ids = 0;            //Varíavel para guardar o número de IDs em car_ids
int num_carros_reparados = 0;   //Variável para guardar o número de carros reparados em ETs
int num_not_added;              //Variável para guardar o número de carros em lista de espera


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
        estacoes[i].capacidade = rand() % 4 + 2;                //A capacidade de cada estacao é um valor aleatório entre 2 a 5
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
    ifstream fileModelos(file2);                                //Abre  ficheiro modelos.txt

    if (fileModelos.is_open()) {
        int i = 0;
        while (!fileModelos.eof()) {
            getline(fileModelos, modelos[i++]); //Guarda todos os modelos od ficheiro no array modelos
        }
    }

    for (int i = NUM_CARROS_CRIADOS; i < NUM_CARROS_CRIADOS + 10; i++) { //Criacão de 10 carros novos
        listadeespera[i].id = id_lista + 1;                              
        listadeespera[i].tempo_reparacao = rand() % 6 + 2;
        listadeespera[i].marca = marcas_ET[rand() % NUM_ETS];
        listadeespera[i].dias_ET = 0;
        listadeespera[i].modelo = modelos[rand() % NUM_MODELOS];
        listadeespera[i].custo_reparacao = rand() % 71 + 60;

        int decisao = rand() % 100;       
        listadeespera[i].prioridade = (decisao <= 5);   //Um veiculo tem 5% de chance de ser considerado prioritário

        id_lista++; // Incrementa os ID'S dos carros
    }
    NUM_CARROS_CRIADOS += 10; //Incremente a variável NUM_CARROS_CRIADOS em 10 (número de carros criados)
    sort(listadeespera, listadeespera + NUM_CARROS_CRIADOS, comparaCarros); //Ordena os carros de acordo com a prioridade (prioritários ficam no inicio)

    fileModelos.close(); //Fecha o ficheiro modelos.txt
}

int* carregarCarrosId(ET* estacoes, int* car_ids, int NUM_ETS, int& num_car_ids) { //VITOR
    delete[] car_ids; 
    car_ids = new int[LIMITE];

    for (int i = 0; i < NUM_ETS; i++) { 
        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            car_ids[num_car_ids++] = estacoes[i].carros[h].id;
        }
        for (int j = 0; j < estacoes[i].carros_reparados; j++) {
            car_ids[num_car_ids++] = estacoes[i].regRepCars[j].id;
        }
    }

    return car_ids;
}

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro*& not_added_copy, int NUM_ETS, int& num_not_added, int* car_ids, int& num_car_ids) {
    //Funcao para adicionar carros ás ETs
    //car_ids vai guardar todos os ID'S dos carros que já passaram por ET'S (inclui os que estão atualmente e os já reparados)
    int num_carros_adicionados_ET = 0;
    int i = 0;
    int f = 0;
    carro* not_added = new carro[NUM_CARROS_CRIADOS];
    bool carroEntrou;
    bool OitoCarrosAdicionados = false;
    bool carroJaPassouPelaOficina = false;
    bool carroJaEstaNaListaDeEspera = false;
    int posicaoListaDeEsperaFake = 0;
    num_not_added = 0;
    while (i < NUM_CARROS_CRIADOS) { //Percorre todos os carros da lista de carros criados
        carroEntrou = false;         // As tres variaveís têm como função verificar se o carro está ou já esteve numa ET
        bool carroJaEstaNaET = false;
        bool carroJaEstaNaEt2 = false;
        for (int j = 0; j < NUM_ETS; j++) {
            if (estacoes[j].marca == listadeespera[i].marca) { //Verifica se há uma marca nas estacoes que coincida com a marca do carro analisado
                if (estacoes[j].capacidade - estacoes[j].capacidade_atual > 0) { //Verifica se a estação tem capacidade para alojar um novo carro
                    for (int k = 0; k < num_car_ids; k++) {
                        if (listadeespera[i].id == car_ids[k]) { //Verifica se o carro ja está nas ETs
                            carroJaEstaNaET = true;
                            carroEntrou = true;
                            break;
                        }
                    }
                    if (!carroJaEstaNaET) { //Se o carro ainda não estiver
                        estacoes[j].carros[estacoes[j].capacidade_atual] = listadeespera[i]; //O carro é adicionado ao array carros da ET
                        estacoes[j].capacidade_atual++; //A capacidade atual da ET é incrementado
                        num_carros_adicionados_ET++; //O número de carros adicionados durante o ciclo é incrementado
                        carroEntrou = true; //Indica que o carro entrou na ET
                        car_ids[num_car_ids] = listadeespera[i].id; //Adiciona o ID do carro que entrou ao car_ids
                        num_car_ids++; //Incrementa o indice em car_ids
                        break;
                    }
                }
            }
        }
        if (carroEntrou == false) {
            for (int r = 0; r < num_car_ids; r++) {
                if (car_ids[r] == listadeespera[i].id) { //Verifica se o carro analisado (e que não entrou na ET) já passou por alguma ET (car_ids)
                    carroJaEstaNaEt2 = true;
                    
                }
            }
            if (carroJaEstaNaEt2 == false) { //Como o carro não entrou, e nunca passou pela ET´s, é adicionado á Lista de Espera
                not_added[num_not_added] = listadeespera[i];
                num_not_added++; //Incrementa o indice da Lista De Espera
            }
        }
        if (num_carros_adicionados_ET == 8) { //Verifica se o limite de 8 carros adicionados ás ETs foi atingido
            OitoCarrosAdicionados = true;
            break;
        }
        i++; //Incrementa o indice e altera o carro a ser analisado
    }
    
    if (OitoCarrosAdicionados == true) { //A partir do momento que já foram adicionados ás ETs 8 carros
        while (posicaoListaDeEsperaFake < NUM_CARROS_CRIADOS) { //Analisa a Lista De carros criados novamente
            carroJaPassouPelaOficina = false;
            carroJaEstaNaListaDeEspera = false;
            for (int y = 0; y < num_car_ids; y++) {
                if (car_ids[y] == listadeespera[posicaoListaDeEsperaFake].id) {  //Verifica se o carro já passou pelas ETs
                    carroJaPassouPelaOficina = true;
                }
            }
            for (int w = 0; w < num_not_added; w++) { 
                
                if (listadeespera[posicaoListaDeEsperaFake].id == not_added[w].id) { //Verifica se o carro ja está na lista de espera
                    carroJaEstaNaListaDeEspera = true;
                }
            }
            if (carroJaPassouPelaOficina == false && carroJaEstaNaListaDeEspera == false) { //Caso contrário, o carro é adicionado á ListaDeEspera
                not_added[num_not_added] = listadeespera[posicaoListaDeEsperaFake];
                num_not_added++;
            }
            posicaoListaDeEsperaFake++; //Incrementa o indice e o proximo carro da Lista de carros criados é analisado
        }

    }
    
    cout << "\n" << num_carros_adicionados_ET << " carros adicionados às ETs.\n" << endl;
    not_added_copy = not_added; //Cria uma cópia da Lista De Espera.
    
}

bool comparaCarros(const carro& a, const carro& b) { //Compara dois carros de acordo com a sua prioridade
    if (a.prioridade && !b.prioridade) {
        return true;
    }

    return false;
}

void reparacaoManual(ET* estacoes, int NUM_ETS) { //SARA
    string marca;
    string modelo;
    bool carrosEncontrados = false;
    cout << endl << "*****Reparação Manual*****" << endl;

    cout << "Marca: " << endl;
    cin.ignore();
    getline(cin, marca);

    cout << "Modelo: " << endl;
    getline(cin, modelo);

    for (int i = 0; i < NUM_ETS; i++) {                                                            //ciclo que percorre todas as estações da oficina

        int carrosReparados = 0;                                                                   //variável inteira responsável por identificar quantos carros foram reparados
        int index = 0;                                                                             // variável inteira que vai ser usada com índice
        carro* carroRestantes = new carro[estacoes[i].capacidade];                                 //novo array dinânmico do tipo carro que tem a mesma capacidade que a capacidade de cada estação
        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {                                   //ciclo que percorre a capacidade atual de cada estação
            bool carroEncontrado = false;                                                          // variável responsável por identificar se o carro foi ou não encontrado
            carro* carro = &estacoes[i].carros[h];                                                 //apontador carro que aponta o endereço de memória onde está guardado o carro h da ET i
            if (estacoes[i].carros[h].marca == marca && estacoes[i].carros[h].modelo == modelo) {  //Procurar nas estações atuais pela marca e modelo que o utilizador escreveu
                carroEncontrado = true;                                                            //se a condição se verificar o carro foi encontrado
                cout << carro->custo_reparacao << endl;                                            //imprime o valor da reparação do veículo
                estacoes[i].faturacao += carro->custo_reparacao;                                   //Adiciona á faturação da estação o preço da reparação
                estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *carro;                   //o carro reparado vai ser guardado no array dos carros reparados
                carrosReparados++;                                                                 //o nº de carros reparados aumenta 1 valor
                carrosEncontrados = true;                                                          //identificação que o carro foi encontrado
            }
            if (!carroEncontrado) {
                carroRestantes[index++] = *carro;                                                  //array carros restantes guarda todo os carros exceto o carro que queríamos reparar
            }
        }

        estacoes[i].capacidade_atual -= carrosReparados;                                           //Capacidade atual da estação diminui
        delete[] estacoes[i].carros;                                                               //o array que continha todos os carros na oficina é eliminado 
        estacoes[i].carros = carroRestantes;                                                       //os carros que estão na oficina passam a ser os mesmos que os anteriores exceto o que queríamos reparar

        if (carrosReparados > 0) {                                                                 //imprime o nº de carros iguais reparados na estação
            cout << "Foram reparados " << carrosReparados << " carros." << endl << endl;
        }
    }

    if (!carrosEncontrados) {                                                                      //caso o veículo não seja encontrado em nenhuma estação
        cout << "Não existe nenhum carro desse modelo/marca nas estações." << endl << endl;
    }
}

void atualiza_tempo_rep(carro* not_added_copy, int NUM_CARROS_CRIADOS) { //SARA
    int tempoRep;
    string marca, modelo;
    bool carrosEncontrados = false;

    cout << endl << "*****Atualizar tempo de reparação*****" << endl;

    cout << "Marca: " << endl;
    cin.ignore();
    getline(cin, marca);

    cout << "Modelo: " << endl;
    getline(cin, modelo);

    for (int i = 0; i < NUM_CARROS_CRIADOS; i++) {                                                     //ciclo percorre os carros que estão na fila de espera
        if (not_added_copy[i].marca == marca && not_added_copy[i].modelo == modelo) {                  //condição que procura o veículo pedido pelo utilizador   
            cout << "Insira o novo tempo de reparacao (em dias): " << endl;
            cin >> tempoRep;                                                                           //utilizador insere o novo tempo
            not_added_copy[i].tempo_reparacao = tempoRep;                                              //tempo de reparação do veículo é alterado
            carrosEncontrados = true;                                                                  //identificação que o carro foi encontrado
        }
    }

    if (!carrosEncontrados) {                                                                          //caso o carro não esteja na fila de espera
        cout << "Não existe nenhum carro desse modelo/marca na fila de espera." << endl << endl;
    }
}

void adiciona_prioridade(carro* not_added, int num_not_added) {
    cout << endl << "Adicionar Prioridade" << endl;
    bool carroEncontrado = false;
    int ID;

    cout << "ID do carro: " << endl;
    cin >> ID;                                                                                  //id do carro escolhido pelo utilizador


    for (int i = 0; i < num_not_added; i++) {                                                   //ciclo que percorre os carros na lista de espera
        if (not_added[i].id == ID) {                                                            //caso o id que o utilizador digitou seja igual a algum id dos carros em espera
            carroEncontrado = true;                                                             //identificador que o carro foi encontrado
            if (not_added[i].prioridade == 1)                                                   //caso o carro já tenha prioridade atribuida
                cout << endl << "Carro já tem prioridade." << endl;
            else {                                                                              //caso o carro não tenha prioridade
                not_added[i].prioridade = 1;                                                    //adicionar prioridade ao veículo
                cout << endl << "Prioridade adicionada." << endl;
            }
        }
    }

    if (!carroEncontrado) {                                                                    //caso o carro não esteja presente na fila de espera
        cout << "Não existe nenhum carro com essa ID na fila de espera." << endl << endl;
    }
}

void menu(ET* estacoes, carro* listadeespera, int NUM_ETS) { //Dá output dos carros presentes nas ETs atualmente 
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

void reparar_carros2(ET* estacoes, int num_estacoes) {
    if (NUM_CARROS_CRIADOS == 0) { //A função não corre caso não tenham sido criados carros ainda
        return;
    }
    for (int i = 0; i < num_estacoes; i++) {
        num_carros_reparados = 0; //Mantem registo do numero de carros reparados durante o ciclo
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            carro* car = &estacoes[i].carros[j];
            if (car->dias_ET <= car->tempo_reparacao) { //Verifica se o o numero de dias que o carro está na ET corresponde é menor tempo máximo de reparação da ET
                int probabilidade = rand() % 100 + 1; //Probabilidade de um carro ser reparado ou não
                if (probabilidade <= 15) { //O carro é reparado
                    estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *car; //O carro é adicionado ao registo de carros reparados da respetiva ET
                    num_carros_reparados++; //O numero de carros reparados é incrementado
                    estacoes[i].faturacao += car->custo_reparacao; //O custo de reparação do carro reparado é adicionao á faturação da ET
                    cout << "O carro com o ID " << car->id << " foi reparado na ET " << estacoes[i].id << "." << endl;
                }
            }
            else { //Adiciona o carro ao registo de carros reparados da ET caso dias_ET = tempo_reparacao
                estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *car;
                num_carros_reparados++;
                cout << "O carro com o ID " << car->id << " foi removido da ET " << estacoes[i].id << " por ter ultrapassado o tempo máximo de reparação." << endl;
            }
        }

        int nova_capacidade_atual = estacoes[i].capacidade_atual - num_carros_reparados; //Subtrai á capacidade atual da ET o número de carros que foram reparados e guarda numa variável
        carro* new_carros = new carro[25]; //Cria um array temporário para guardar os carros que estvam em cada ET e nãao foram reparados
        int new_index = 0;

        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            carro* car = &estacoes[i].carros[j];
            bool carro_removido = false;
            for (int k = 0; k < estacoes[i].carros_reparados; k++) { 
                if (car->id == estacoes[i].regRepCars[k].id) { //Verifica se o carro foi reparado
                    carro_removido = true;
                    break;
                }
            }
            if (!carro_removido) { //Caso não tenha sido reparado, é adicionao a new_carros
                new_carros[new_index++] = *car;
            }
        }

        delete[] estacoes[i].carros; //Apaga o array carros da ET
        estacoes[i].carros = new_carros; //Substitui por new_carros
        estacoes[i].capacidade_atual = nova_capacidade_atual; //Atualiza capacidade atual
    }
    cout << endl;
}

void incrementar_dias_ET(ET* estacoes, int num_estacoes) { //Passa pelas ETs, e incrementa o atributo dias_ET de cada carro em uma unidade
    if (NUM_CARROS_CRIADOS == 0) {
        return;
    }
    for (int i = 0; i < num_estacoes; i++) {
        for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
            estacoes[i].carros[j].dias_ET++;
        }
    }
}

void imprimeOficina(ET* estacoes, carro* listadeespera, int NUM_ETS, int NUM_CARROS_CRIADOS, carro* not_added, int num_not_added) {
    int indexEstacoes = 0;
    int indexListaDeEspera = 0;
    
    carro* carrosEstacoes = new carro[LIMITE]; //Cria um novo array que vai guardar todos os carros que se encontram nas estações
    for (int i = 0; i < NUM_ETS; i++) {
        for (int h = 0; h < estacoes[i].capacidade_atual; h++) {
            carro carroEstacao = estacoes[i].carros[h]; 
            carrosEstacoes[indexEstacoes++] = carroEstacao;
        }
    }

    carro* carrosListaDeEspera = new carro[LIMITE]; //Cria um novo array que vai guardar todos os carros na Lista De Espera
    for (int i = 0; i < num_not_added; i++) {
            carro carroListaDeEspera = not_added[i];
            carrosListaDeEspera[indexListaDeEspera++] = carroListaDeEspera;
    }

    int escolha; //Vai guardar a escolha do utilizador
    cout << "(1). ordenar por marca, por ordem alfabética. \n(2). ordenar por tempo de reparação" << endl;
    cout << ">> ";
    cin >> escolha;

    if (escolha == 1) {
        for (int i = 0; i < indexEstacoes - 1; i++) { //Ordena os carros das estações por ordem alfabética de acordo com a marca
            for (int j = i + 1; j < indexEstacoes; j++) {
                if (carrosEstacoes[i].marca > carrosEstacoes[j].marca) {
                    carro tempEstacoes = carrosEstacoes[i];
                    carrosEstacoes[i] = carrosEstacoes[j];
                    carrosEstacoes[j] = tempEstacoes;
                }
            }
        }
        for (int i = 0; i < indexListaDeEspera - 1; i++) {
            for (int j = i + 1; j < indexListaDeEspera; j++) {
                if (carrosListaDeEspera[i].marca > carrosListaDeEspera[j].marca) {//Ordena os carros da Lista De Espera por ordem alfabética de acordo com a marca
                    carro tempListaDeEspera = carrosListaDeEspera[i];
                    carrosListaDeEspera[i] = carrosListaDeEspera[j];
                    carrosListaDeEspera[j] = tempListaDeEspera;
                }
            }
        }
    }
    if (escolha == 2) {
        for (int i = 0; i < indexEstacoes - 1; i++) { //Ordena os carros das estações por tempo de reparação
            for (int j = i + 1; j < indexEstacoes; j++) {
                if (carrosEstacoes[i].tempo_reparacao > carrosEstacoes[j].tempo_reparacao) {
                    carro tempEstacoes = carrosEstacoes[i];
                    carrosEstacoes[i] = carrosEstacoes[j];
                    carrosEstacoes[j] = tempEstacoes;
                }
            }
        }
        for (int i = 0; i < indexListaDeEspera - 1; i++) { //Ordena os carros da Lista De Espera por tempo de reparação
            for (int j = i + 1; j < indexListaDeEspera; j++) {
                if (carrosListaDeEspera[i].tempo_reparacao > carrosListaDeEspera[j].tempo_reparacao) {
                    carro tempListaDeEspera = carrosListaDeEspera[i];
                    carrosListaDeEspera[i] = carrosListaDeEspera[j];
                    carrosListaDeEspera[j] = tempListaDeEspera;
                }
            }
        }
    }

    if (escolha != 1 && escolha != 2) { //A função termina caso a escolha do utilizador não seja nem 1, nem 2.
        return;
    }

    cout << "----------------------------------------" << endl; //Imprime as ETs
    cout << "CARROS DAS ESTAÇÕES:" << endl;
    for (int i = 0; i < indexEstacoes; i++) {
        cout << "id: " << carrosEstacoes[i].id << " | ";
        cout << carrosEstacoes[i].marca << "-" << carrosEstacoes[i].modelo << " | ";
        cout << "prioritário: ";
        if (carrosEstacoes[i].prioridade == 1) {
            cout << "Sim | ";
        }
        else {
            cout << "Não | ";
        }
        cout << "tempo reparação: " << carrosEstacoes[i].tempo_reparacao << " | ";
        cout << "dias na et: " << carrosEstacoes[i].dias_ET << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "CARROS DA LISTA DE ESPERA:" << endl; //Imprime a lista de espera
    for (int i = 0; i < indexListaDeEspera; i++) {
        cout << "id: " << carrosListaDeEspera[i].id << " | ";
        cout << carrosListaDeEspera[i].marca << "-" << carrosListaDeEspera[i].modelo << " | ";
        cout << "prioritário: ";
        if (carrosListaDeEspera[i].prioridade == 1) {
            cout << "Sim | ";
        }
        else {
            cout << "Não | ";
        }
        cout << "tempo reparação: " << carrosListaDeEspera[i].tempo_reparacao << " | ";
        cout << "dias na et: " << carrosListaDeEspera[i].dias_ET << endl;
    }
    delete[] carrosEstacoes; //Elimina os arrays criados
    delete[] carrosListaDeEspera;
    cout << endl;
}


void removeMecanico(ET* estacoes, int NUM_ETS, string* marcas, string*& marcas_ET, int*& car_ids, int& num_car_ids, carro* listadeespera, int NUM_CARROS_CRIADOS) { //SARA

    string mecanico, novoMecanico;
    bool mecanicoExiste, mecanicoUnicoDaMarca = false;
    int carrosRemovidos = 0;
    int passaPorTodasET = 0;
    cout << "Introduza o nome do mecânico que pretende remover das oficinas: " << endl;
    cin >> mecanico;
    for (int i = 0; i < NUM_ETS; i++) {
        int index = 0;
        mecanicoExiste = false;
        mecanicoUnicoDaMarca = false;
        if (estacoes[i].mecanico == mecanico) {
            mecanicoExiste = true;
        }
        if (mecanicoExiste) {
            for (int j = 0; j < estacoes[i].capacidade_atual; j++) {
                carro* car = &estacoes[i].carros[j];
                estacoes[i].regRepCars[estacoes[i].carros_reparados++] = *car;
                estacoes[i].faturacao += car->custo_reparacao;

            }
            carro* estacaoVazia = new carro[estacoes[i].capacidade];
            estacoes[i].carros = estacaoVazia;
            estacoes[i].capacidade_atual = 0;

            int contador = 0;
            // verificar se mecânico removido seja o único mecânico de uma determinada marca
            for (int k = 0; k < NUM_ETS; k++) {
                if (estacoes[i].marca == marcas_ET[k]) {
                    contador++;
                }
            }
            if (contador == 1) {
                mecanicoUnicoDaMarca = true;
            }
            string* novaMarcas = new string[NUM_MARCAS - 1];
            if (mecanicoUnicoDaMarca) {
                //for (int l = 0; l < NUM_CARROS_CRIADOS; l++) {
                //    carro* car2 = &listadeespera[l];
                //    if (car2 ->marca == estacoes[i].marca) {
                //        car_ids[num_car_ids++] = car2->id; //Os carros nunca sao reparados, sao adicionados a car_ids e nao aparecem no not_added.
                //                                           //MANUEL: PODES POR ISTO EM COMENTARIO, ASSIM, OS CARROS VAO PERMANECER NA LISTA DE ESPERA E NO NOT ADDED PORQUE NAO VAI HAVER OFICINA PARA
                //                                           // ALOJAR. A MENOS QUE A NOVA MARCA SEJA IGUAL.! MANUEl!
                //    }
                //}
                //impossibilita esta marca de ser criada novamente

                for (int m = 0; m < NUM_MARCAS; m++) {
                    if (marcas[m] != estacoes[i].marca) {
                        novaMarcas[index++] = marcas[m];
                    }
                }
                cout << "INDEX: " << index << endl;
                for (int g = 0; g < index; g++) {
                    cout << "NOVAMARCAS_ET: " << novaMarcas[g] << endl;
                }
            }

            cout << "Por favor introduza o nome do novo mecânico para a oficina " << estacoes[i].id << ": " << endl;
            cin >> novoMecanico;
            estacoes[i].mecanico = novoMecanico;
            estacoes[i].marca = novaMarcas[rand() % NUM_MARCAS - 1];
            marcas_ET[i] = estacoes[i].marca; //ocupa o espaco resultante com a nova marca da ET
            //cout << NUM_MARCAS << endl;
        }
        if (!mecanicoExiste) {
            passaPorTodasET++;
        }
        if (passaPorTodasET == NUM_ETS) {
            cout << "O mecânico introduzido não existe!" << endl;
            return;
        }
    }


}

void menuInicial(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET, int NUM_ETS, int* car_ids, string* marcas, caminhosFicheiros* caminhos) {
    //Menu que permite a iteração do utilizador com o programa
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
            reparacaoManual(estacoes, NUM_ETS);
            break;
        case '2':
            atualiza_tempo_rep(listadeespera, NUM_CARROS_CRIADOS);
            break;
        case '3':
            adiciona_prioridade(not_added_copy, num_not_added);
            break;
        case '4':
            removeMecanico(estacoes, NUM_ETS, marcas, marcas_ET, car_ids,num_car_ids,listadeespera,NUM_CARROS_CRIADOS);
            break;
        case '5':
            for (int i = 0; i < num_not_added; i++) {
                cout << not_added_copy[i].id << endl;
            }
            gravarOficina(listadeespera, NUM_CARROS_CRIADOS, not_added_copy, num_not_added, estacoes);
            cout << endl << "A gravação da oficina foi feita com sucesso." << endl << endl;
            break;
        case '6':
            NUM_ETS = numEstacoes();
            NUM_CARROS_CRIADOS = numCarrosCriados();
            num_not_added = numListaDeEspera();
            estacoes = carregarEstacoes(estacoes, caminhos);
            not_added_copy = carregarListaDeEspera(not_added_copy, caminhos);
            listadeespera = carregarCarros(listadeespera, caminhos);
            marcas_ET = obtemMarcasETnova(marcas_ET, estacoes, NUM_ETS);
            car_ids = carregarCarrosId(estacoes, car_ids, NUM_ETS, num_car_ids);
            cout << endl << "O carregamento da oficina foi feito com sucesso." << endl << endl;
            break;
        case '7':
            imprimeOficina(estacoes, listadeespera, NUM_ETS, NUM_CARROS_CRIADOS, not_added_copy, num_not_added);
            break;
        case '9':
            simulateDay(estacoes, listadeespera, not_added_copy, modelos, marcas_ET, NUM_ETS, car_ids, marcas, caminhos);
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

void simulateDay(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET, int NUM_ETS, int* car_ids, string* marcas, caminhosFicheiros* caminhos) {
    //Permite ao utilizador simular um dia ao carregar "S"
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
            adicionarCarrosETs(listadeespera, estacoes, not_added_copy, NUM_ETS, num_not_added, car_ids, num_car_ids);
            menu(estacoes, listadeespera, NUM_ETS);
            break;
        case 'g':
        case 'G':
            menuInicial(estacoes, listadeespera, not_added_copy, modelos, marcas_ET, NUM_ETS, car_ids, marcas, caminhos);
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
