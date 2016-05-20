#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include "rota.h"
#include <vector>

namespace rotas
{
	namespace domain 
	{
		class Caminho 
		{
		public:
			Caminho() {};
			Caminho(std::vector<Rota> route) : distancias_entre_cidades(route) {};
			std::vector<Rota> distancias_entre_cidades;
			Cidade get_origem();
			Cidade get_destino();
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_PATH_H_
