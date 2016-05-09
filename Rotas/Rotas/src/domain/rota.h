#ifndef ROTAS_DOMAIN_ROTA_H_
#define ROTAS_DOMAIN_ROTA_H_

#include "cidade.h"

class Rota {
	Cidade origem;
	Cidade destino;
	double distancia;
public:
	Rota() {};
	Rota(Cidade origem, Cidade destino, double distancia) : origem(origem),
		destino(destino), distancia(distancia){};
	Cidade get_origem();
	Cidade get_destino();
	double get_distancia();
};

#endif // ROTAS_DOMAIN_ROTA_H_
