#pragma once
#include "structs.h"

void inicializarEstacoes(ET* estacoes, string* marcas);

void criarCarros(carro* listadeespera, string* modelos, string* marcas_ET);

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro*& not_added_copy, int NUM_ETS, int& num_not_added, int* car_ids, int& num_car_ids);

bool comparaCarros(const carro& a, const carro& b);

void menu(ET* estacoes, carro* listadeespera, int NUM_ETS);

void menuInicial(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET, int NUM_ETS, int* car_ids, string* marcas);

void obtemMarcasET(string* marcas, string* marcas_ET, ET* estacoes);

void simulateDay(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET, int NUM_ETS, int* car_ids, string* marcas, caminhosFicheiros* caminhos);

void reparar_carros2(ET* estacoes, int num_estacoes);
	
void incrementar_dias_ET(ET* estacoes, int num_estacoes);

