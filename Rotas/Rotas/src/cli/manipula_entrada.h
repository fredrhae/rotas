#ifndef ROTAS_CLI_MANIPULA_ENTRADA_H_
#define ROTAS_CLI_MANIPULA_ENTRADA_H_

#include <string>
#include <vector>

namespace rotas
{
	namespace cli
	{
		static class ManipulaEntrada {
			public:
				static bool inicializa_dados_partir_do_csv(std::string path);
		};
	}
}
#endif //ROTAS_CLI_MANIPULA_ENTRADA_H_
