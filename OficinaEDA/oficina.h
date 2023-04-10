#pragma once
#include "structs.h"

void inicializarEstacoes(ET* estacoes, string* marcas);

void criarCarros(carro* listadeespera, string* modelos, string* marcas);

void adicionarCarrosETs(carro* listadeespera, ET* estacoes, carro*& not_added_copy);

bool comparaCarros(const carro& a, const carro& b);

void menu(ET* estacoes, carro* listadeespera);

void verListaDeEspera(carro* listadeespera);

void menuInicial(ET* estacoes, carro* listadeespera, carro* not_added);

void verNotAdded(carro* not_added);

void obtemMarcasET(string* marcas, string* marcas_ET, ET* estacoes);

void simulateDay(ET* estacoes, carro* listadeespera, carro* not_added_copy, string* modelos, string* marcas_ET);

void reparar_carros(ET* estacoes, int num_estacoes);

void reparar_carros2(ET* estacoes, int num_estacoes);
	
void incrementar_dias_ET(ET* estacoes, int num_estacoes);

void imprimeOficina(ET* estacoes, carro* listadeespera, carro* imprime);

void printAllCarsInRegRepCars(ET* estacoes);