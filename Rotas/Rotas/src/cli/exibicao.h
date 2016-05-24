#ifndef ROTAS_CLI_EXIBICAO_H_
#define ROTAS_CLI_EXIBICAO_H_

#include <string>


namespace rotas
{
	namespace cli
	{
		class Exibicao {

		public:
				const static std::string kOutputHeader;
				const static std::string kInstructionsHeader;
				const static std::string kInstructionsInputData;
				const static std::string kInstructionsAlgorithms;
				const static std::string kDijkstra;
				const static std::string kPCV;
				const static std::string kTeitzBart;
				const static std::string kGilletJohnson;
				const static std::string kClarkeWright;
				const static std::string kTodos;
				static void exibe_instrucoes();
				static void exibe_saida(std::string texto_saida);
		};
	}
}
#endif //ROTAS_CLI_EXIBICAO_H_