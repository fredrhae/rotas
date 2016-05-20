#ifndef ROTAS_DOMAIN_ROTA_H_
#define ROTAS_DOMAIN_ROTA_H_

#include "cidade.h"

namespace rotas
{
	namespace domain
	{
		class Rota
		{
			Cidade destino;
			double distancia;
		public:
			Rota() {};
			Rota(Cidade destino, double distancia) :
				destino(destino), distancia(distancia) {};
			Cidade get_destino();
			double get_distancia();
			void set_distancia(double nova_distancia);
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_ROTA_H_
