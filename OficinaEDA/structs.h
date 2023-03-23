#pragma once

struct ET {
    int id;
    int capacidade;
    string mecanico;
    string marca;
};

struct carro {
    int id;
    string marca;
    string modelo;
    int tempo_reparacao;
    int dias_ET;
    string prioridade;
};