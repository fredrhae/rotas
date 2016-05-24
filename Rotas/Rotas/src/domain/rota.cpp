#include "rota.h"

namespace rotas 
{
	namespace domain 
	{
		double Rota::get_distancia()
		{
			return distancia;
		}

		int Rota::get_id_origem() {
			return id_origem;
		}

		int Rota::get_id_destino() {
			return id_destino;
		}
	} // domain
} // rotas
