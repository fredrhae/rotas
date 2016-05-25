#include "cli\exibicao.h"
#include "cli\manipula_entrada.h"
#include <iostream>


using namespace std;
using namespace rotas::cli;

const string Exibicao::kDijkstra = "Dijkstra";
const string Exibicao::kPCV = "Problema do Caixeiro Viajante";
const string Exibicao::kTeitzBart = "Teitz e Bart";
const string Exibicao::kGilletJohnson = "Gillet e Johnson";
const string Exibicao::kClarkeWright = "Clarke e Wright";
const string Exibicao::kTodos = "Todos os algoritmos";
 
const string Exibicao::kOutputHeader = "\n\n#################  OUTPUT RESULTS #################\n\n";
const string Exibicao::kInstructionsHeader = "\n ##################  ROTEAMENTO DE PRODUTOS ##################\n";
const string Exibicao::kInstructionsInputData = "\nEntre com o path dos dados de entrada dos algoritmos utilizando \"/\"\n\
para separar as pastas (Ex: C:/Users/fulano/Documentos):\n";
const string Exibicao::kInstructionsAlgorithms = "\nSelecione o algoritmo que sera utilizado para calcular o menor caminho:\
									   \n1 - " + kDijkstra + "\n2 - " + kPCV + "\n3 - " + kTeitzBart + "\n4 - "
									   + kGilletJohnson + "\n5 - " + kClarkeWright + "\n6 - " + kTodos + "\n";

void Exibicao::exibe_instrucoes()
{
	cout << kInstructionsHeader;
	cout << Exibicao::kInstructionsInputData;
	std::string input;
	cin >> input;
	ManipulaEntrada::inicializa_dados_partir_do_csv(input);
}

void Exibicao::exibe_saida(string texto_saida)
{
	cout << "Não implementado ainda.";
}