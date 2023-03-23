#pragma once
#include "structs.h"

void inicializarEstacoes(ET* estacoes, string* marcas);

void criarCarros(carro* listadeespera, string* modelos, string* marcas);

void adicionarCarrosETs(carro* listadeespera, ET* estacoes);

bool comparaCarros(const carro& a, const carro& b);

void menu(ET* estacoes, carro* listadeespera);

void verListaDeEspera(carro* listadeespera);

void ciclo(carro* listadeespera, string* modelos, string* marcas);

void gravarOficina(ET* estacoes, carro* listadeespera);

int menuInicio(ET* estacoes, carro* listadeespera);