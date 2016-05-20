#ifndef ROTAS_ALGORITMOS_GILLET_H_
#define ROTAS_ALGORITMOS_GILLET_H_

#include <vector>
#include "domain/caminho.h"

class GilletJohnson
{
public:
	GilletJohnson() {};
	~GilletJohnson() {};

	void atribui_medianas(std::vector<Caminho> distancias, std::vector<Cidade> cidades);
};

#endif //ROTAS_ALGORITMOS_GILLET_H_
