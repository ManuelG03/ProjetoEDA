#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "constantes.h"
#include "structs.h"
#include "oficina.h"

using namespace std;

int main() {
    locale::global(locale(""));
    srand(time(NULL));

    string* marcas = new string[NUM_MARCAS];
    string* marcas_ET = new string[NUM_ETS + 1];
    string* modelos = new string[NUM_MODELOS];
    carro* listadeespera = new carro[LIMITE];
    carro* not_added = new carro[LIMITE];
    carro* not_added_copy = new carro[LIMITE];
    ET* estacoes = new ET[NUM_ETS];
    
    inicializarEstacoes(estacoes, marcas);
    obtemMarcasET(marcas,marcas_ET,estacoes);

    simulateDay(estacoes,listadeespera,not_added_copy/*, modelos, marcas_ET*/);
    
    return 0;
}