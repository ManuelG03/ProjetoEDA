#pragma once
#include <string>

using namespace std;
struct carro {
    int id;
    string marca = "";
    string modelo;
    int tempo_reparacao;
    int dias_ET;
    string prioridade;
};

struct ET {
    int id;
    int capacidade;
    string mecanico;
    string marca;
    carro* carros;
    int capacidade_atual;
};