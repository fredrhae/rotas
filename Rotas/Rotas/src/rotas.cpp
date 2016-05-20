// projeto_menor_caminho.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "cli/exibicao.h"
#include "algoritmos/dijkstra.h"
#include "algoritmos/gillet_johnson.h"

using namespace std;
using namespace rotas::algoritmos;
using namespace rotas::domain;

vector<Cidade> cidades;
vector<Caminho> caminhos;

void inicializa_cidades()
{
	cidades = vector<Cidade>();

	Cidade aux = Cidade("A",0);
	cidades.push_back(aux);
	aux = Cidade("B",1);
	cidades.push_back(aux);
	aux = Cidade("C", 2);
	cidades.push_back(aux);
	aux = Cidade("D", 3);
	cidades.push_back(aux);
	aux = Cidade("E", 4);
	cidades.push_back(aux);
	aux = Cidade("F", 5);
	cidades.push_back(aux);
	aux = Cidade("G", 6);
	cidades.push_back(aux);
	aux = Cidade("H", 7);
	cidades.push_back(aux);
	aux = Cidade("I", 8);
	cidades.push_back(aux);
}

void inicializa_rotas(double rotas[9][9])
{
	caminhos = vector<Caminho>();

	for (int i = 0; i < 9; i++)
	{
		vector<Rota> rotas_cidade_atual = vector<Rota>();
		for (int j = 0; j < 9; j++)
		{
			Rota rota_para_cidade = Rota(cidades[j],rotas[i][j]);
			rotas_cidade_atual.push_back(rota_para_cidade);
		}
		
		caminhos.push_back(rotas_cidade_atual);
	}

}

void inicializa_dados()
{
	
}

int main()
{

	Dijkstra dijkstra = Dijkstra();
	GilletJohnson gillet_johnson = GilletJohnson();
	
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

	inicializa_cidades();

	inicializa_rotas(graph);

	cout << "----- Dijkstra -------" << endl;
	Caminho *menor_caminho = new Caminho[9];
	for (int i = 0; i < 9; i++) {
		menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i),cidades);
	}
	
	cout << "----- Gillet e Johnson -------" << endl;
	//gillet_johnson.atribui_medianas(caminhos, cidades);

	//Exibicao::exibe_instrucoes();
	cout << "Pressione qualquer tecla para sair.";
	cin.get();

    return 0;
}