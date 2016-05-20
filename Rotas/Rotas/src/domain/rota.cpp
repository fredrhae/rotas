#include "rota.h"

namespace rotas 
{
	namespace domain 
	{
		double Rota::get_distancia()
		{
			return distancia;
		}

		void Rota::set_distancia(double nova_distancia)
		{
			distancia = nova_distancia;
		}

		Cidade Rota::get_destino() {
			return destino;
		}
	} // domain
} // rotas
