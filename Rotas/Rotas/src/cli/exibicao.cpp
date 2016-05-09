#include "exibicao.h"
#include <iostream>


using namespace std;

const string Exibicao::kDijkstra = "Dijkstra";
const string Exibicao::kPCV = "Problema do Caixeiro Viajante";
const string Exibicao::kTeitzBart = "Teitz e Bart";
const string Exibicao::kGilletJohnson = "Gillet e Johnson";
const string Exibicao::kClarkeWright = "Clarke e Wright";
const string Exibicao::kTodos = "Todos os algoritmos";
 
const string Exibicao::kOutputHeader = "\n\n#################  OUTPUT RESULTS #################\n\n";
const string Exibicao::kInstructionsHeader = "\n ##################  ROTEAMENTO DE PRODUTOS ##################\n";
const string Exibicao::kInstructionsInputData = "\nEntre com os dados de entrada do algoritmo: \n1 - Digitar dados\
	 										   \n2 - Selecionar arquivo de entrada\n";
const string Exibicao::kInstructionsAlgorithms = "\nSelecione o algoritmo que será utilizado para calcular o menor caminho:\
									   \n1 - " + kDijkstra + "\n2 - " + kPCV + "\n3 - " + kTeitzBart + "\n4 - "
									   + kGilletJohnson + "\n5 - " + kClarkeWright + "\n6 - " + kTodos + "\n";

void Exibicao::exibe_instrucoes()
{
	cout << kInstructionsHeader;
	cout << Exibicao::kInstructionsInputData;
	char input = cin.get();
	cout << Exibicao::kInstructionsAlgorithms;
	char algorithm = cin.get();
	//TODO: fazer classe que faz o handle do input
}

void Exibicao::exibe_saida(string texto_saida)
{
	cout << "Não implementado ainda.";
}