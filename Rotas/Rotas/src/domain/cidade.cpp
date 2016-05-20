
#include "cidade.h"

using namespace std;

string Cidade::get_nome() {
	return nome;
}

int Cidade::get_id() {
	return id;
}

bool Cidade::is_mediana() {
	return mediana;
}

void Cidade::set_mediana(bool is_mediana) {
	mediana = is_mediana;
}

int Cidade::get_id_mediana() {
	return id_mediana;
}

void Cidade::set_id_mediana(int id) {
	id_mediana = id;
}