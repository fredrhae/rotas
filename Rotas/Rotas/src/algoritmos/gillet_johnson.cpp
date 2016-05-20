#include "gillet_johnson.h"
#include <iostream>
#include <string>


void GilletJohnson::atribui_medianas(std::vector<Caminho> distancias, std::vector<Cidade> cidades) {
	std::cout << "Cidades: " << std::endl;
	for (int i = 0; i < 9; i++) {
		Cidade cidade = cidades.at(i);
		std::cout << cidade.get_nome() << " ";
	}
	std::cout << std::endl;
}
