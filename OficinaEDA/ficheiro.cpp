#include <iostream>
#include <fstream>
#include <string>
#include "oficina.h"
#include "structs.h"
#include "constantes.h"
#include "ficheiro.h"

using namespace std;

void gravarCarros(carro* carrosCriados, int num_carros_criados) { //Fun��o que grava as informa��es dos carros todos inicializados na oficina
    ofstream fileCarros;
    fileCarros.open("carros.txt");                                //Abrir o ficheiro carros.txt

    fileCarros << num_carros_criados << endl;                     //Gravar o n�mero de carros inicializados na oficina

    for (int i = 0; i < num_carros_criados; i++) {
        fileCarros << carrosCriados[i].id << endl;                //Gravar o id de cada carro inicializado
        fileCarros << carrosCriados[i].marca << endl;             //Gravar a marca de cada carro inicializado
        fileCarros << carrosCriados[i].modelo << endl;            //Gravar o modelo de cada carro inicializado
        if (carrosCriados[i].prioridade) {                        //Gravar a prioridade de cada carro da lista de espera com a condi��o
            fileCarros << "Sim" << endl;                          //Se � true � gravado "Sim"
        }
        else {
            fileCarros << "Nao" << endl;                          //Se � false � gravado "Nao"
        }
        fileCarros << carrosCriados[i].tempo_reparacao << endl;   //Gravar o tempo de repara��o de cada carro inicializado
        fileCarros << carrosCriados[i].dias_ET << endl;           //Gravar a quantidade de dias que o carro esteve na esta��o de trabalho de cada carro 
    }

    fileCarros.close();                                           //Fechar o ficheiro carros.txt
}

carro* carregarCarros(carro* carrosCriados) {      //Fun��o que carrega as informa��es dos carros criados do ficheiro
    ifstream fileCarros;
    fileCarros.open("carros.txt");                 //Abrir o ficheiro carros.txt

    string linha;

    int num_carros_criados;                        //Cria��o da vari�vel para o n�mero de carros criados presentes no ficheiro
    getline(fileCarros, linha);                    //Buscar � primeira linha do ficheiro a string para o n�mero de carros criados
    num_carros_criados = stoi(linha);              //Stoi para converter a string em int e atribuir � vari�vel esse valor

    delete[] carrosCriados;                        //Apagar o conte�do de carrosCriados
    carrosCriados = new carro[LIMITE];             //Criar para o carrosCriados um array do tipo carro com LIMITE de tamanho

    for (int i = 0; i < num_carros_criados; i++) { //Buscar linha a linha e converter as strings necess�rias para int e atribuir os valores para o array carrosCriados
        getline(fileCarros, linha);
        carrosCriados[i].id = stoi(linha);
        getline(fileCarros, carrosCriados[i].marca);
        getline(fileCarros, carrosCriados[i].modelo);
        getline(fileCarros, linha);
        if (linha == "Sim") {
            carrosCriados[i].prioridade = true;
        }
        else if (linha == "Nao") {
            carrosCriados[i].prioridade = false;
        }
        getline(fileCarros, linha);
        carrosCriados[i].tempo_reparacao = stoi(linha);
        getline(fileCarros, linha);
        carrosCriados[i].dias_ET = stoi(linha);
    }

    fileCarros.close();                            //Fechar o ficheiro carros.txt

    return carrosCriados;                          //Retornar o array carrosCriados
}

int numCarrosCriados() {              //Fun��o criada com o objetivo de retornar o n�mero de carros criados
    ifstream fileCarros;
    fileCarros.open("carros.txt");    //Abrir o ficheiro carros.txt

    string linha;

    int num_carros_criados;           //Cria��o da vari�vel para o n�mero de carros criados presentes no ficheiro
    getline(fileCarros, linha);       //Buscar � primeira linha do ficheiro a string para o n�mero de carros criados
    num_carros_criados = stoi(linha); //Stoi para converter a string em int e atribuir � vari�vel esse valor

    fileCarros.close();               //Fechar o ficheiro carros.txt

    return num_carros_criados;        //Retornar o valor de num_carros_criados
}

void gravarListaDeEspera(carro* listaDeEspera, int num_lista_espera) { //Fun��o que grava as informa��es dos carros presentes na lista de espera
    ofstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");                       //Abrir o ficheiro listaDeEspera.txt

    string linha;

    fileListaDeEspera << num_lista_espera << endl;                     //Gravar o n�mero de carros presentes na lista de espera

    for (int i = 0; i < num_lista_espera; i++) {
        fileListaDeEspera << listaDeEspera[i].id << endl;              //Gravar o id de cada carro da lista de espera
        fileListaDeEspera << listaDeEspera[i].marca << endl;           //Gravar a marca de cada carro da lista de espera
        fileListaDeEspera << listaDeEspera[i].modelo << endl;          //Gravar o modelo de cada carro da lista de espera
        if (listaDeEspera[i].prioridade) {                             //Gravar a prioridade de cada carro da lista de espera com a condi��o
            fileListaDeEspera << "Sim" << endl;                        //Se � true � gravado "Sim"
        }
        else {
            fileListaDeEspera << "Nao" << endl;                        //Se � false � gravado "Nao"
        }
        fileListaDeEspera << listaDeEspera[i].tempo_reparacao << endl; //Gravar o tempo de repara��o de cada carro da lista de espera
        fileListaDeEspera << listaDeEspera[i].dias_ET << endl;         //Gravar a quantidade de dias que o carro esteve na esta��o de trabalho de cada carro da lista de espera
    }

    fileListaDeEspera.close();                                         //Fechar o ficheiro listaDeEspera.txt
}

carro* carregarListaDeEspera(carro* listaDeEspera) { //Fun��o que carrega as informa��es dos carros criados do ficheiro
    ifstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt");     //Abrir o ficheiro listaDeEspera.txt

    string linha;

    int num_lista_espera;                            //Cria��o da vari�vel para o n�mero de carros na lista de espera presentes no ficheiro
    getline(fileListaDeEspera, linha);               //Buscar � primeira linha do ficheiro a string para o n�mero de carros na lista de espera
    num_lista_espera = stoi(linha);                  //Stoi para converter a string em int e atribuir � vari�vel esse valor

    delete[] listaDeEspera;                          //Apagar o conte�do de listaDeEspera
    listaDeEspera = new carro[num_lista_espera];     //Criar para o carrosCriados um array do tipo carro com num_lista_espera de tamanho

    for (int i = 0; i < num_lista_espera; i++) {     //Buscar linha a linha e converter as strings necess�rias para int e atribuir os valores para o array listaDeEspera
        getline(fileListaDeEspera, linha);
        listaDeEspera[i].id = stoi(linha);
        getline(fileListaDeEspera, listaDeEspera[i].marca);
        getline(fileListaDeEspera, listaDeEspera[i].modelo);
        getline(fileListaDeEspera, linha);
        if (linha == "Sim") {
            listaDeEspera[i].prioridade = true;
        }
        else if (linha == "Nao") {
            listaDeEspera[i].prioridade = false;
        }
        getline(fileListaDeEspera, linha);
        listaDeEspera[i].tempo_reparacao = stoi(linha);
        getline(fileListaDeEspera, linha);
        listaDeEspera[i].dias_ET = stoi(linha);
    }

    fileListaDeEspera.close();                       //Fechar o ficheiro listaDeEspera.txt

    return listaDeEspera;                            //Retornar o array listaDeEspera
}

int numListaDeEspera() {                         //Fun��o criada com objetivo de retornar o n�mero de carros na lista de espera
    ifstream fileListaDeEspera;
    fileListaDeEspera.open("listaDeEspera.txt"); //Abrir o ficheiro listaDeEspera.txt

    string linha;

    int num_lista_espera;                        //Cria��o da vari�vel para o n�mero de carros na lista de espera presentes no ficheiro
    getline(fileListaDeEspera, linha);           //Buscar � primeira linha do ficheiro a string para o n�mero de carros na lista de espera
    num_lista_espera = stoi(linha);              //Stoi para converter a string em int e atribuir � vari�vel esse valor

    fileListaDeEspera.close();                   //Fechar o ficheiro listaDeEspera.txt

    return num_lista_espera;                     //Retornar o valor de num_lista_espera
}

void gravarEstacoes(ET* estacoes) {                                                   //Fun��o que grava as informa��es dos carros presentes nas esta��es de trabalho e os carros reparados das mesmas
    ofstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");                                                //Abrir o ficheiro estacoes.txt

    ofstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");                                  //Abrir o ficheiro carrosReparados.txt

    fileEstacoes << NUM_ETS << endl;                                                  //Gravar o n�mero de esta��es de trabalho presentes na oficina

    for (int i = 0; i < NUM_ETS; i++)
    {
        fileEstacoes << estacoes[i].id << endl;                                       //Gravar no estacoes.txt o id de cada esta��o
        fileEstacoes << estacoes[i].mecanico << endl;                                 //Gravar no estacoes.txt o mec�nico de cada esta��o
        fileEstacoes << estacoes[i].capacidade << endl;                               //Gravar no estacoes.txt a capacidade de cada esta��o
        fileEstacoes << estacoes[i].capacidade_atual << endl;                         //Gravar no estacoes.txt a capacidade atual de cada esta��o
        fileEstacoes << estacoes[i].marca << endl;                                    //Gravar no estacoes.txt a marca de cada esta��o
        fileEstacoes << estacoes[i].faturacao << endl;                                //Gravar no estacoes.txt a fatura��o de cada esta��o

        for (int h = 0; h < estacoes[i].capacidade_atual; h++)
        {
            fileEstacoes << estacoes[i].carros[h].id << endl;                         //Gravar no estacoes.txt o id de cada carro presente em cada esta��o
            fileEstacoes << estacoes[i].carros[h].marca << endl;                      //Gravar no estacoes.txt a marca de cada carro presente em cada esta��o
            fileEstacoes << estacoes[i].carros[h].modelo << endl;                     //Gravar no estacoes.txt o modelo de cada carro presente em cada esta��o
            if (estacoes[i].carros[h].prioridade) {                                   //Gravar no estacoes.txt a prioridade de cada carro presente em cada esta��o
                fileEstacoes << "Sim" << endl;                                        //Se � true � gravado "Sim"
            }
            else {
                fileEstacoes << "Nao" << endl;                                        //Se � false � gravado "Nao"
            }
            fileEstacoes << estacoes[i].carros[h].tempo_reparacao << endl;            //Gravar no estacoes.txt o tempo de repara��o de cada carro presente em cada esta��o
            fileEstacoes << estacoes[i].carros[h].dias_ET << endl;                    //Gravar no estacoes.txt a quantidade de dias que o carro esteve na esta��o de trabalho de cada carro presente em cada esta��o
        }

        fileCarrosReparados << estacoes[i].carros_reparados << endl;                  //Gravar no carrosReparados.txt o n�mero de carros reparados de cada esta��o de trabalho
        for (int j = 0; j < estacoes[i].carros_reparados; j++)
        {
            fileCarrosReparados << estacoes[i].regRepCars[j].id << endl;              //Gravar no carrosReparados.txt o id de cada carro reparado de cada esta��o de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].marca << endl;           //Gravar no carrosReparados.txt a marca de cada carro reparado de cada esta��o de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].modelo << endl;          //Gravar no carrosReparados.txt o modelo de cada carro reparado de cada esta��o de trabalho
            if (estacoes[i].regRepCars[j].prioridade) {                               //Gravar no carrosReparados.txt a prioridade de cada carro reparado de cada esta��o de trabalho
                fileCarrosReparados << "Sim" << endl;                                 //Se � true � gravado "Sim"
            }
            else {
                fileCarrosReparados << "Nao" << endl;                                 //Se � false � gravado "Nao"
            }
            fileCarrosReparados << estacoes[i].regRepCars[j].tempo_reparacao << endl; //Gravar no carrosReparados.txt o tempo de repara��o de cada carro reparado de cada esta��o de trabalho
            fileCarrosReparados << estacoes[i].regRepCars[j].dias_ET << endl;         //Gravar no carrosReparados.txt a quantidade de dias que o carro esteve na esta��o de trabalho de cada carro reparado de cada esta��o de trabalho
        }
    }

    fileEstacoes.close();                                                             //Fechar o ficheiro estacoes.txt

    fileCarrosReparados.close();                                                      //Fechar o ficheiro carrosReparados.txt
}

ET* carregarEstacoes(ET* estacoes) {                            //Fun��o que carrega as informa��es das esta��es do ficheiro
    ifstream fileEstacoes;
    fileEstacoes.open("estacoes.txt");                          //Abrir o ficheiro estacoes.txt
    ifstream fileCarrosReparados;
    fileCarrosReparados.open("carrosReparados.txt");            //Abrir o ficheiro carrosReparados.txt

    string linha;

    int NUM_ETS;                                                //Cria��o da vari�vel para o n�mero de esta��es presentes no ficheiro
    getline(fileEstacoes, linha);                               //Buscar � primeira linha do ficheiro a string para o n�mero de esta��es
    NUM_ETS = stoi(linha);                                      //Stoi para converter a string em int e atribuir � vari�vel esse valor

    delete[] estacoes;                                          //Apagar o conte�do de estacoes
    estacoes = new ET[NUM_ETS];

    for (int i = 0; i < NUM_ETS; i++)                           //Buscar linha a linha e converter as strings necess�rias para int e atribuir os valores para o array estacoes
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

        estacoes[i].carros = new carro[estacoes[i].capacidade]; //Criar novo array carros para cada esta��o com capacidade de cada esta��o de tamanho
        for (int h = 0; h < estacoes[i].capacidade_atual; h++)  //Buscar linha a linha e converter as strings necess�rias para int e atribuir os valores para o array carros de cada esta��o
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

        estacoes[i].regRepCars = new carro[LIMITE];             //Criar novo array regRepCars para cada esta��o com LIMITE de tamanho
        getline(fileCarrosReparados, linha);
        estacoes[i].carros_reparados = stoi(linha);
        for (int j = 0; j < estacoes[i].carros_reparados; j++)  //Buscar linha a linha e converter as strings necess�rias para int e atribuir os valores para o array regRepCars de cada esta��o
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

    fileEstacoes.close();                                       //Fechar o ficheiro estacoes.txt
    fileCarrosReparados.close();                                //Fechar o ficheiro carrosReparados.txt

    return estacoes;                                            //Retornar o array estacoes
}

int numEstacoes() {                    //Fun��o criada com objetivo de retornar o n�mero de esta��es na lista de espera
    ifstream fileEstacoes;
    fileEstacoes.open("estacoes.txt"); //Abrir o ficheiro estacoes.txt

    string linha;

    int NUM_ETS;                       //Cria��o da vari�vel para o n�mero de esta��es presentes no ficheiro
    getline(fileEstacoes, linha);      //Buscar � primeira linha do ficheiro a string para o n�mero de esta��es
    NUM_ETS = stoi(linha);             //Stoi para converter a string em int e atribuir � vari�vel esse valor

    fileEstacoes.close();              //Fechar o ficheiro estacoes.txt

    return NUM_ETS;                    //Retornar o valor de NUM_ETS
}

string* obtemMarcasETnova(string* marcas_ET, ET* estacoes, int NUM_ETS) { //Fun��o criada com o objetivo de obter o array marcas_ET novo
    for (int i = 0; i < NUM_ETS; i++) {
        marcas_ET[i] = estacoes[i].marca;                                 //Igualar cada posi��o do array marcas_ET �s marcas de cada esta��o
    }

    return marcas_ET;                                                     //Retornar o array marcas_ET
}

void gravarOficina(carro* carrosCriados, int num_carros_criados, carro* listaDeEspera, int num_lista_espera, ET* estacoes) { //Fun��o que executa todas as fun��es de grava��o no ficheiro
    gravarEstacoes(estacoes);
    gravarCarros(carrosCriados, num_carros_criados);
    gravarListaDeEspera(listaDeEspera, num_lista_espera);
}

void carregarOficina(carro* carrosCriados, carro* listaDeEspera, ET* estacoes) { //Fun��o que executa todas as fun��es de carregamento do ficheiro
    carregarEstacoes(estacoes);
    carregarListaDeEspera(listaDeEspera);
    carregarCarros(carrosCriados);
}