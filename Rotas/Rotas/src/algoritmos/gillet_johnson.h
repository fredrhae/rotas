#ifndef ROTAS_ALGORITMOS_GILLET_H_
#define ROTAS_ALGORITMOS_GILLET_H_

#include <vector>
#include "domain/cidade.h"

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
			void encontra_medianas(std::vector<Cidade> & cidades);

#ifndef GTEST
		private:
#endif //!GTEST
			
		};
	} // algoritmos
} // rotas

#endif //ROTAS_ALGORITMOS_GILLET_H_
