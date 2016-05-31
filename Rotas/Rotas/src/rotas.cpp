// projeto_menor_caminho.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include "cli\exibicao.h"
#include "cli\manipula_entrada.h"
#include "algoritmos\dijkstra.h"
#include "algoritmos\gillet_johnson.h"

using namespace std;
using namespace rotas::algoritmos;
using namespace rotas::domain;
using namespace rotas::cli;

int main()
{

	Dijkstra dijkstra = Dijkstra();
	GilletJohnson gillet_johnson = GilletJohnson();
	Exibicao::exibe_instrucoes();

	cout << "----- Dijkstra -------" << endl;

	cout << endl;
	
	cout << "----- Gillet e Johnson -------" << endl;
	//gillet_johnson.atribui_medianas(caminhos, cidades);

	cout << endl;

	cout << "Pressione qualquer tecla para sair.";
	cin.ignore();
	cin.get();

    return 0;
}