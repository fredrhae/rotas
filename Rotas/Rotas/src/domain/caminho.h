#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include "rota.h"
#include <vector>

class Caminho {
	public:
		Caminho() {};
		Caminho(std::vector<Rota> route) : distancias_entre_cidades(route){};
		std::vector<Rota> distancias_entre_cidades;
		Cidade get_origem();
		Cidade get_destino();
};

#endif // ROTAS_DOMAIN_PATH_H_
