// test_rotas.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "algoritmos/gillet_johnson.h"
#include "algoritmos/dijkstra.h"
#include "domain/caminho.h"

using namespace std;
using namespace rotas;
using namespace domain;

class RotasTest : public ::testing::Test {
protected:
	std::vector<domain::Caminho> caminhos;
	std::vector<domain::Cidade> cidades;

	double graph[9][9] = {
		{  0,  4,  0,  0,  0,  0,  0,  8,  0 },
		{  4,  0,  8,  0,  0,  0,  0, 11,  0 },
		{  0,  8,  0,  7,  0,  4,  0,  0,  2 },
		{  0,  0,  7,  0,  9, 14,  0,  0,  0 },
		{  0,  0,  0,  9,  0, 10,  0,  0,  0 },
		{  0,  0,  4,  0, 10,  0,  2,  0,  0 },
		{  0,  0,  0, 14,  0,  2,  0,  1,  6 },
		{  8, 11,  0,  0,  0,  0,  1,  0,  7 },
		{  0,  0,  2,  0,  0,  0,  6,  7,  0 }
	};

	double graph2[9][9] = {
		{  0, 18,  3, 22,  4, 23, 27,  1, 25 },
		{ 18,  0, 23,  6, 20,  8, 12, 24,  7 },
		{  3, 23,  0, 22,  1, 20, 26,  2, 23 },
		{ 22,  6, 22,  0, 22,  2,  5, 24,  4 },
		{  4, 20,  1, 22,  0, 20, 20,  3, 21 },
		{ 23,  8, 20,  2, 20,  0,  7, 22,  3 },
		{ 27, 12, 26,  5, 20,  7,  0, 23,  4 },
		{  1, 24,  2, 24,  3, 22, 23,  0, 25 },
		{ 25,  7, 23,  4, 21,  3,  4, 25,  0 }
	};

	void init_cidades() {
		cidades = std::vector<domain::Cidade>();

		cidades.push_back(domain::Cidade("A", 0));
		cidades.push_back(domain::Cidade("B", 1));
		cidades.push_back(domain::Cidade("C", 2));
		cidades.push_back(domain::Cidade("D", 3));
		cidades.push_back(domain::Cidade("E", 4));
		cidades.push_back(domain::Cidade("F", 5));
		cidades.push_back(domain::Cidade("G", 6));
		cidades.push_back(domain::Cidade("H", 7));
		cidades.push_back(domain::Cidade("I", 8));
	}

	void inicializa_rotas(double distancias[9][9]) {

		caminhos = std::vector<domain::Caminho>();
		init_cidades();

		for (int i = 0; i < 9; i++)
		{
			std::vector<domain::Rota> rotas_cidade_atual = std::vector<domain::Rota>();
			for (int j = 0; j < 9; j++)
			{
				domain::Rota rota_para_cidade = domain::Rota(i, j, distancias[i][j]);
				rotas_cidade_atual.push_back(rota_para_cidade);
			}
			Cidade origem_rota = cidades[rotas_cidade_atual.front().get_id_origem()];
			Cidade destino_rota = cidades[rotas_cidade_atual.back().get_id_destino()];
			caminhos.push_back(Caminho(origem_rota, destino_rota, rotas_cidade_atual));
		}
	}
	virtual void SetUp() {
		//Inicializa as cidades		
		string nomes[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
		for (unsigned int i = 0; i < 9; i++) {
			vector<Rota> rotas = vector<Rota>();
			for (unsigned int j = 0; j < 9; j++) {
				Rota nova_rota = Rota(i, j, graph2[i][j]);
				rotas.push_back(nova_rota);
			}
			Cidade nova_cidade = Cidade(nomes[i], i, rotas);
			cidades.push_back(nova_cidade);
		}
	}
};

class DijkstraTest : public ::RotasTest {
protected:
	int a;
	algoritmos::Dijkstra dijkstra;

	virtual void SetUp() {
		RotasTest::SetUp();
		inicializa_rotas(graph);

		domain::Caminho *menor_caminho = new domain::Caminho[9];
		for (int i = 0; i < 9; i++) {
			menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i), cidades);
		}

		a = 7;
	}
};

TEST_F(RotasTest, validacaoCidades)
{
	cout << "Cidades testadas :" << endl;
	for (unsigned int i = 0; i < cidades.size(); i++) {
		cout << cidades[i].get_nome() << " ";
	}
	cout << endl;

	cout << "---------------------------" << endl;

	for (unsigned int i = 0; i < cidades.size(); i++) {
		Cidade cidade = cidades[i];
		vector<Rota> rotas = cidade.get_rotas();
		cout << "Rotas partindo de " << cidade.get_nome() << ":" << endl;
		for (unsigned int j = 0; j < rotas.size(); j++) {
			Rota rota = rotas[j];
			cout << rota.get_id_origem() << " até " << rota.get_id_destino() << " = " << rota.get_distancia() << endl;
		}
		cout << endl;
	}
}

TEST_F(DijkstraTest, validacaoTrivial)
{
	domain::Caminho *menor_caminho = new domain::Caminho[9];
	for (int i = 0; i < 9; i++) {
		menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i), cidades);
	}

	EXPECT_EQ(a, 7);
}

class GilletJohnsonTest : public ::RotasTest {
protected:
	int a;
	algoritmos::GilletJohnson gillet_johnson;

	virtual void SetUp() {
		RotasTest::SetUp();
		inicializa_rotas(graph2);

		//A e C são as medianas do graph2
		domain::Cidade cidade_C = cidades.at(2);
		cidade_C.set_mediana(true);
		domain::Cidade cidade_F = cidades.at(5);
		cidade_F.set_mediana(true);

		gillet_johnson = algoritmos::GilletJohnson();
		a = 5;
	}
};

TEST_F(GilletJohnsonTest, validacaoTrivial)
{
	gillet_johnson.atribui_medianas(caminhos, cidades);

	EXPECT_EQ(a, 5);
}

