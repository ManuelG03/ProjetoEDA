#pragma once

void gravarOficina(carro* listadeespera, int num_carros_criados, carro* not_added, int num_not_added, ET* estacoes);

void carregarOficina(carro* listadeespera, carro* not_added, ET* estacoes, caminhosFicheiros* caminhos);

carro* carregarCarros(carro* listadeespera, caminhosFicheiros* caminhos);

carro* carregarListaDeEspera(carro* listaDeEspera, caminhosFicheiros* caminhos);

ET* carregarEstacoes(ET* estacoes, caminhosFicheiros* caminhos);

int numCarrosCriados();

int numListaDeEspera();

int numEstacoes();

string* obtemMarcasETnova(string* marcas_ET, ET* estacoes ,int NUM_ETS2);