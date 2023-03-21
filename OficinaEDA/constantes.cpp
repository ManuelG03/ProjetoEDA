#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "constantes.h"

using namespace std;

int contarMarcas() {
	string file = "marcas.txt";
	ifstream fileMarcas(file);
	string marca;
	int num_marcas = 0;
	if (fileMarcas.is_open()) {
		while (getline(fileMarcas, marca)) {
			num_marcas++;
		}
	}
	return num_marcas;
}

int contarModelos() {
	string file = "modelos.txt";
	ifstream fileModelos(file);
	string modelo;
	int num_modelos = 0;
	if (fileModelos.is_open()) {
		while (getline(fileModelos, modelo)) {
			num_modelos++;
		}
	}
	return num_modelos;
}

int contarEstacoes() {
	int num_ETs;
	num_ETs = rand() % 6 + 3;

	return num_ETs;
}