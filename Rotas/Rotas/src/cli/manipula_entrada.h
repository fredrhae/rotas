#ifndef ROTAS_CLI_MANIPULA_ENTRADA_H_
#define ROTAS_CLI_MANIPULA_ENTRADA_H_

#include <string>
#include <vector>
#include "domain/context.h"

using namespace rotas::domain;

namespace rotas
{
	namespace cli
	{
		class ManipulaEntrada {
			public:
				static Context inicializa_dados_partir_do_csv(std::string path);
		};
	}
}
#endif //ROTAS_CLI_MANIPULA_ENTRADA_H_
