// projeto_menor_caminho.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cli/exibicao.h"
#include "algoritmos/dijkstra.h"
#include "algoritmos/gillet_johnson.h"

using namespace std;
using namespace rotas::algoritmos;
using namespace rotas::domain;
using namespace rotas::cli;

extern vector<Cidade> cidades;
extern vector<Caminho> caminhos;

int main()
{

	Dijkstra dijkstra = Dijkstra();
	GilletJohnson gillet_johnson = GilletJohnson();
	Exibicao::exibe_instrucoes();

	cout << "----- Dijkstra -------" << endl;
	Caminho *menor_caminho = new Caminho[9];
	for (int i = 0; i < 9; i++) {
		menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i),cidades);
	}
	
	cout << "----- Gillet e Johnson -------" << endl;
	//gillet_johnson.atribui_medianas(caminhos, cidades);

	cout << "Pressione qualquer tecla para sair.";
	cin.ignore();
	cin.get();

    return 0;
}