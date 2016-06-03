#ifndef _ROTAS_ALGORITMOS_CLARKE_WRIGHT_H_
#define _ROTAS_ALGORITMOS_CLARKE_WRIGHT_H_

#include <vector>
#include "domain/cidade.h"
#include "domain/caminho.h"

namespace rotas 
{
	namespace algoritmos 
	{
		using namespace domain;

		class ClarkeWright {
				
			public:
				ClarkeWright(){};
				vector<Caminho> encontra_roteamentos(std::vector<Cidade> & cidades, Cidade facilidade);
		};
	}
}

#endif // _ROTAS_ALGORITMOS_CLARKE_WRIGHT_H_
