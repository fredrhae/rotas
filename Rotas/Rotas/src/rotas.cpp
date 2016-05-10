// projeto_menor_caminho.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cli/exibicao.h"
#include "algoritmos/dijkstra.h"

using namespace std;

int main()
{

	Dijkstra objeto = Dijkstra();
	
	/* Let us create the example graph discussed above */
	double graph[9][9] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 0, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 14, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};

	objeto.dijkstra_menor_caminho(graph, 0);

	Exibicao::exibe_instrucoes();
	cout << "Pressione qualquer tecla para sair.";
	cin.get();

    return 0;
}