#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include <vector>
#include "cidade.h"

namespace rotas
{
	namespace domain 
	{
		class Caminho 
		{
			Cidade origem;
			Cidade destino;
			std::vector<Rota> trajeto;
		public:
			Caminho() {};
			Caminho(Cidade origem, Cidade destino, std::vector<Rota> trajeto) : origem(origem), destino(destino), trajeto(trajeto) {};
			Cidade get_origem();
			Cidade get_destino();
			std::vector<Rota> get_trajeto();
			double get_distancia();
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_PATH_H_
