#ifndef ROTAS_ALGORITMOS_GILLET_H_
#define ROTAS_ALGORITMOS_GILLET_H_

#include <vector>
#include "domain/caminho.h"

namespace rotas
{
	namespace algoritmos
	{
		using namespace domain;

		class GilletJohnson
		{
		public:
			GilletJohnson() {};
			~GilletJohnson() {};
			vector<Cidade> ordena_por_distancia(Cidade origem, vector<Cidade> destinos);
			void encontra_medianas(std::vector<Cidade> & cidades);

#ifndef GTEST
		private:
#endif //!GTEST
			double get_distancia(Cidade a, Cidade b);
			Cidade encontra_mais_proxima(Cidade origem, vector<Cidade> destinos);
		};
	} // algoritmos
} // rotas

#endif //ROTAS_ALGORITMOS_GILLET_H_
