#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include "rota.h"
#include <vector>

class Caminho {
	std::vector<Rota> caminho;
	double distancia_total;
public:
	Caminho() {};
	Caminho(std::vector<Rota> route) : caminho(route){};
	Cidade get_origem();
	Cidade get_destino();
	double get_distancia_total();
};

#endif // ROTAS_DOMAIN_PATH_H_
