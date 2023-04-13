#pragma once

void gravarOficina(carro* listadeespera, int num_carros_criados, carro* not_added, int num_not_added, ET* estacoes);

void carregarOficina(carro* listadeespera, carro* not_added, ET* estacoes);

carro* carregarCarros(carro* listadeespera);

carro* carregarListaDeEspera(carro* not_added);

ET* carregarEstacoes(ET* estacoes);

int numCarrosCriados();

int numListaDeEspera();

int numEstacoes();

string* obtemMarcasETnova(string* marcas_ET, ET* estacoes ,int NUM_ETS2);