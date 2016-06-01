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

		bool Rota::rota_contem_cidade(int id_cidade)
		{
			if(id_origem == id_cidade || id_destino == id_cidade)
				return true;
			return false;
		}
	} // domain
} // rotas
