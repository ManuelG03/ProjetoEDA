#include <iostream>
#include <fstream>
#include <string>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

void gravarCarros(carro* listadeespera, int num_carros_criados) { //Função que grava as informações dos carros todos inicializados na oficina
    ofstream fileCarros;
    fileCarros.open("carros.txt");                                //Abrir o ficheiro carros.txt

    fileCarros << num_carros_criados << endl;                     //Gravar o número de carros inicializados na oficina

    for (int i = 0; i < num_carros_criados; i++) {
        fileCarros << listadeespera[i].id << endl;                //Gravar o id de cada carro inicializado
        fileCarros << listadeespera[i].marca << endl;             //Gravar a marca de cada carro inicializado
        fileCarros << listadeespera[i].modelo << endl;            //Gravar o modelo de cada carro inicializado
        if (listadeespera[i].prioridade) {                        //Gravar a prioridade de cada carro da lista de espera com a condição
            fileCarros << "Sim" << endl;                          //Se é true é gravado "Sim"
        }
        else {
            fileCarros << "Nao" << endl;                          //Se é false é gravado "Nao"
        }
        fileCarros << listadeespera[i].tempo_reparacao << endl;   //Gravar o tempo de reparação de cada carro inicializado
        fileCarros << listadeespera[i].dias_ET << endl;           //Gravar a quantidade de dias que o carro esteve na estação de trabalho de cada carro 
    }

    fileCarros.close();                                           //Fechar o ficheiro carros.txt
}

carro* carregarCarros(carro* listadeespera) {
    ifstream fileCarros;
    fileCarros.open("carros.txt");

    string linha;

    int num_carros_criados;
    getline(fileCarros, linha);
    num_carros_criados = stoi(linha);

    delete[] listadeespera;
    listadeespera = new carro[num_carros_criados];

    for (int i = 0; i < num_carros_criados; i++) {
        getline(fileCarros, linha);
        listadeespera[i].id = stoi(linha);
        getline(fileCarros, listadeespera[i].marca);
        getline(fileCarros, listadeespera[i].modelo);
        getline(fileCarros, linha);
        if (linha == "Sim") {
            listadeespera[i].prioridade = true;
        }
        else if (linha == "Nao") {
            listadeespera[i].prioridade = false;
        }
        getline(fileCarros, linha);
        listadeespera[i].tempo_reparacao = stoi(linha);
        getline(fileCarros, linha);
        listadeespera[i].dias_ET = stoi(linha);
    }

    fileCarros.close();

    return listadeespera;
} 

int numCarrosCriados() {
    ifstream fileCarros;
    fileCarros.open("carros.txt");

    string linha;

    int num_carros_criados;
    getline(fileCarros, linha);
    num_carros_criados = stoi(linha);

    fileCarros.close();

    return num_carros_criados;
}

void gravarListaDeEspera(carro* not_added, int num_not_added) {    //Função que grava as informações dos carros presentes na lista de espera
    ofstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");                   //Abrir o ficheiro listaDeEspera.txt

    string linha;

    fileListaDeEspera << num_not_added << endl;                    //Gravar o número de carros presentes na lista de espera

    for (int i = 0; i < num_not_added; i++) {
        fileListaDeEspera << not_added[i].id << endl;              //Gravar o id de cada carro da lista de espera
        fileListaDeEspera << not_added[i].marca << endl;           //Gravar a marca de cada carro da lista de espera
        fileListaDeEspera << not_added[i].modelo << endl;          //Gravar o modelo de cada carro da lista de espera
        if (not_added[i].prioridade) {                             //Gravar a prioridade de cada carro da lista de espera com a condição
            fileListaDeEspera << "Sim" << endl;                    //Se é true é gravado "Sim"
        }
        else {
            fileListaDeEspera << "Nao" << endl;                    //Se é false é gravado "Nao"
        }
        fileListaDeEspera << not_added[i].tempo_reparacao << endl; //Gravar o tempo de reparação de cada carro da lista de espera
        fileListaDeEspera << not_added[i].dias_ET << endl;         //Gravar a quantidade de dias que o carro esteve na estação de trabalho de cada carro da lista de espera
    }

    fileListaDeEspera.close();                                     //Fechar o ficheiro listaDeEspera.txt
}

carro* carregarListaDeEspera(carro* not_added) {
    ifstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");

    string linha;

    int num_not_added;
    getline(fileListaDeEspera, linha);
    num_not_added = stoi(linha);

    delete[] not_added;
    not_added = new carro[num_not_added];

    for (int i = 0; i < num_not_added; i++) {
        getline(fileListaDeEspera, linha);
        not_added[i].id = stoi(linha);
        getline(fileListaDeEspera, not_added[i].marca);
        getline(fileListaDeEspera, not_added[i].modelo);
        getline(fileListaDeEspera, linha);
        if (linha == "Sim") {
            not_added[i].prioridade = true;
        }
        else if (linha == "Nao") {
            not_added[i].prioridade = false;
        }
        getline(fileListaDeEspera, linha);
        not_added[i].tempo_reparacao = stoi(linha);
        getline(fileListaDeEspera, linha); 
        not_added[i].dias_ET = stoi(linha);
    }

    fileListaDeEspera.close();

    return not_added;
} 

int numListaDeEspera() {
    ifstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");

    string linha;

    int num_not_added;
    getline(fileListaDeEspera, linha);
    num_not_added = stoi(linha);

    fileListaDeEspera.close();

    return num_not_added;
}

void gravarEstacoes(ET* estacoes) {                                                   //Função que grava as informações dos carros presentes nas estações de trabalho e os carros reparados das mesmas
    ofstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");                                                //Abrir o ficheiro estacoes.txt

    ofstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");                                  //Abrir o ficheiro carrosReparados.txt

    fileEstacoes << NUM_ETS << endl;                                                  //Gravar o número de estações de trabalho presentes na oficina

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes << estacoes[i].id << endl;                                       //Gravar no estacoes.txt o id de cada estação
        fileEstacoes << estacoes[i].mecanico << endl;                                 //Gravar no estacoes.txt o mecânico de cada estação
        fileEstacoes << estacoes[i].capacidade << endl;                               //Gravar no estacoes.txt a capacidade de cada estação
        fileEstacoes << estacoes[i].capacidade_atual << endl;                         //Gravar no estacoes.txt a capacidade atual de cada estação
        fileEstacoes << estacoes[i].marca << endl;                                    //Gravar no estacoes.txt a marca de cada estação
        fileEstacoes << estacoes[i].faturacao << endl;                                //Gravar no estacoes.txt a faturação de cada estação

        for (int h = 0; h < estacoes[i].capacidade_atual; h++)
        {
            fileEstacoes << estacoes[i].carros[h].id << endl;                         //Gravar no estacoes.txt o id de cada carro presente em cada estação
            fileEstacoes << estacoes[i].carros[h].marca << endl;                      //Gravar no estacoes.txt a marca de cada carro presente em cada estação
            fileEstacoes << estacoes[i].carros[h].modelo << endl;                     //Gravar no estacoes.txt o modelo de cada carro presente em cada estação
            if (estacoes[i].carros[h].prioridade) {                                   //Gravar no estacoes.txt a prioridade de cada carro presente em cada estação
                fileEstacoes << "Sim" << endl;                                        //Se é true é gravado "Sim"
            }
            else {
                fileEstacoes << "Nao" << endl;                                        //Se é false é gravado "Nao"
            }
            fileEstacoes << estacoes[i].carros[h].tempo_reparacao << endl;            //Gravar no estacoes.txt o tempo de reparação de cada carro presente em cada estação
            fileEstacoes << estacoes[i].carros[h].dias_ET << endl;                    //Gravar no estacoes.txt a quantidade de dias que o carro esteve na estação de trabalho de cada carro presente em cada estação
        }

        fileCarrosReparados << estacoes[i].carros_reparados << endl;                  //Gravar no carrosReparados.txt o número de carros reparados de cada estação de trabalho
        for (int j = 0; j < estacoes[i].carros_reparados; j++)
        {
            fileCarrosReparados << estacoes[i].regRepCars[j].id << endl;              //Gravar no carrosReparados.txt o id de cada carro reparado de cada estação de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].marca << endl;           //Gravar no carrosReparados.txt a marca de cada carro reparado de cada estação de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].modelo << endl;          //Gravar no carrosReparados.txt o modelo de cada carro reparado de cada estação de trabalho
            if (estacoes[i].regRepCars[j].prioridade) {                               //Gravar no carrosReparados.txt a prioridade de cada carro reparado de cada estação de trabalho
                fileCarrosReparados << "Sim" << endl;                                 //Se é true é gravado "Sim"
            }
            else {
                fileCarrosReparados << "Nao" << endl;                                 //Se é false é gravado "Nao"
            }
            fileCarrosReparados << estacoes[i].regRepCars[j].tempo_reparacao << endl; //Gravar no carrosReparados.txt o tempo de reparação de cada carro reparado de cada estação de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].dias_ET << endl;         //Gravar no carrosReparados.txt a quantidade de dias que o carro esteve na estação de trabalho de cada carro reparado de cada estação de trabalho
        }
    }

    fileEstacoes.close();                                                             //Fechar o ficheiro estacoes.txt

    fileCarrosReparados.close();                                                      //Fechar o ficheiro carrosReparados.txt
}

ET* carregarEstacoes(ET* estacoes) {
    ifstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");
    ifstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    string linha;

    int NUM_ETS;
    getline(fileEstacoes, linha);
    NUM_ETS = stoi(linha);

    delete[] estacoes;
    estacoes = new ET[NUM_ETS];

    for (int i = 0; i < NUM_ETS; i++)
    {
        getline(fileEstacoes, linha);
        estacoes[i].id = stoi(linha); 
        getline(fileEstacoes, estacoes[i].mecanico); 
        getline(fileEstacoes, linha); 
        estacoes[i].capacidade = stoi(linha);
        getline(fileEstacoes, linha);
        estacoes[i].capacidade_atual = stoi(linha); 
        getline(fileEstacoes, estacoes[i].marca);
        getline(fileEstacoes, linha); 
        estacoes[i].faturacao = stoi(linha);

        estacoes[i].carros = new carro[estacoes[i].capacidade];
        for (int h = 0; h < estacoes[i].capacidade_atual; h++)  
        {
            getline(fileEstacoes, linha); 
            estacoes[i].carros[h].id = stoi(linha); 
            getline(fileEstacoes, estacoes[i].carros[h].marca);
            getline(fileEstacoes, estacoes[i].carros[h].modelo); 
            getline(fileEstacoes, linha);
            if (linha == "Sim") {
                estacoes[i].carros[h].prioridade = true;
            }
            else if (linha == "Nao") {
                estacoes[i].carros[h].prioridade = false;
            }
            getline(fileEstacoes, linha); 
            estacoes[i].carros[h].tempo_reparacao = stoi(linha);
            getline(fileEstacoes, linha); 
            estacoes[i].carros[h].dias_ET = stoi(linha);
        }

        estacoes[i].regRepCars = new carro[LIMITE];
        getline(fileCarrosReparados, linha);
        estacoes[i].carros_reparados = stoi(linha); 
        for (int j = 0; j < estacoes[i].carros_reparados; j++) 
        {
            getline(fileCarrosReparados, linha); 
            estacoes[i].regRepCars[j].id = stoi(linha);
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].marca);
            getline(fileCarrosReparados, estacoes[i].regRepCars[j].modelo); 
            getline(fileCarrosReparados, linha);
            if (linha == "Sim") {
                estacoes[i].regRepCars[j].prioridade = true;
            }
            else if (linha == "Nao") {
                estacoes[i].regRepCars[j].prioridade = false;
            }
            getline(fileCarrosReparados, linha);
            estacoes[i].regRepCars[j].tempo_reparacao = stoi(linha);
            getline(fileCarrosReparados, linha);
            estacoes[i].regRepCars[j].dias_ET = stoi(linha);
        }
    }

    fileEstacoes.close();
    fileCarrosReparados.close();

    return estacoes;
}

int numEstacoes() {
    ifstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");
    ifstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");

    string linha;

    int NUM_ETS;
    getline(fileEstacoes, linha);
    NUM_ETS = stoi(linha);

    fileEstacoes.close();

    return NUM_ETS;
}

void gravarOficina(carro* listadeespera, int num_carros_criados, carro* not_added, int num_not_added, ET* estacoes) {
    gravarEstacoes(estacoes);
    gravarCarros(listadeespera, num_carros_criados);
    gravarListaDeEspera(not_added, num_not_added);
}

void carregarOficina(carro* listadeespera, carro* not_added, ET* estacoes) {
    carregarEstacoes(estacoes);
    carregarListaDeEspera(not_added);
    carregarCarros(listadeespera);
}