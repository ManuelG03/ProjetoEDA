#pragma once
#include "structs.h"

void inicializarEstacoes(ET* estacoes, string* marcas);

void criarCarros(carro* listadeespera, string* modelos, string* marcas);

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro* not_added_copy);

bool comparaCarros(const carro& a, const carro& b);

void menu(ET* estacoes, carro* listadeespera);

void verListaDeEspera(carro* listadeespera);

int menuInicio();

void verNotAdded(carro* not_added);

void obtemMarcasET(string* marcas, string* marcas_ET, ET* estacoes);

void simulateDay();

void reparar_carros(ET estacoes[], int num_estacoes);
	
