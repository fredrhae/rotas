#include "caminho.h"

namespace rotas 
{
	namespace domain 
	{
		Cidade Caminho::get_origem()
		{
			return origem;
		}

		Cidade Caminho::get_destino()
		{
			return destino;
		}
		
		double Caminho::get_distancia()
		{
			//TODO: implementar a soma das distâncias
			return 0.0;
		}
	} // domain
} // rotas