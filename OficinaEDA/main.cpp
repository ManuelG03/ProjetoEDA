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
    std::locale::global(locale(""));
    srand(time(NULL));

    string* marcas = new string[NUM_MARCAS];
    string* modelos = new string[NUM_MODELOS];
    carro* listadeespera = new carro[LIMITE];
    carro* not_added = new carro[LIMITE];
    ET* estacoes = new ET[NUM_ETS];
    
    inicializarEstacoes(estacoes, marcas);
    criarCarros(listadeespera, modelos, marcas);
    criarCarros(listadeespera, modelos, marcas);
    adicionarCarrosETs(listadeespera,estacoes,not_added);
    verNotAdded(not_added);
    criarCarros(listadeespera, modelos, marcas);
    adicionarCarrosETs(listadeespera, estacoes, not_added);
    verNotAdded(not_added);
   //verListaDeEspera(listadeespera);
   
    menu(estacoes, listadeespera);

    return 0;
}