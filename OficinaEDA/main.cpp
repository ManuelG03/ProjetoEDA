#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "constantes.h"
#include "structs.h"
#include "oficina.h"

using namespace std;

int main(int argc, char* argv[]) {
    locale::global(locale(""));
    srand(time(NULL));

    string* marcas = new string[NUM_MARCAS];
    string* marcas_ET = new string[NUM_ETS + 1];
    string* modelos = new string[NUM_MODELOS];
    carro* listadeespera = new carro[LIMITE];
    carro* not_added = new carro[LIMITE];
    carro* not_added_copy = new carro[LIMITE];
    ET* estacoes = new ET[NUM_ETS];
    int* car_ids = new int[LIMITE];

    caminhosFicheiros* caminhos = new caminhosFicheiros;
    
    if ((argv[1] && argv[2] && argv[3] && argv[4]) == NULL) {
        caminhos->caminhoCarros = "carros.txt";
        caminhos->caminhoListaDeEspera = "listaDeEspera.txt";
        caminhos->caminhoEstacoes = "estacoes.txt";
        caminhos->caminhoCarrosReparados = "carrosReparados.txt";
    }
    else {
        caminhos->caminhoCarros = argv[1];
        caminhos->caminhoListaDeEspera = argv[2];
        caminhos->caminhoEstacoes = argv[3];
        caminhos->caminhoCarrosReparados = argv[4];
    }

    inicializarEstacoes(estacoes, marcas);
    obtemMarcasET(marcas, marcas_ET, estacoes);

    simulateDay(estacoes,listadeespera,not_added_copy, modelos, marcas_ET, NUM_ETS, car_ids, marcas, caminhos);
    
    return 0;
}