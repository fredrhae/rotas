// test_rotas.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "algoritmos/gillet_johnson.h"
#include "algoritmos/dijkstra.h"
#include "domain/caminho.h"

class RotasTest : public ::testing::Test {
	protected:
		std::vector<Caminho> caminhos;
		std::vector<Cidade> cidades;

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
			cidades = std::vector<Cidade>();

			cidades.push_back(Cidade("A", 0));
			cidades.push_back(Cidade("B", 1));
			cidades.push_back(Cidade("C", 2));
			cidades.push_back(Cidade("D", 3));
			cidades.push_back(Cidade("E", 4));
			cidades.push_back(Cidade("F", 5));
			cidades.push_back(Cidade("G", 6));
			cidades.push_back(Cidade("H", 7));
			cidades.push_back(Cidade("I", 8));
		}

		void inicializa_rotas(double distancias[9][9]) {
			caminhos = std::vector<Caminho>();
			init_cidades();

			for (int i = 0; i < 9; i++)
			{
				std::vector<Rota> rotas_cidade_atual = std::vector<Rota>();
				for (int j = 0; j < 9; j++)
				{
					Rota rota_para_cidade = Rota(cidades[j], distancias[i][j]);
					rotas_cidade_atual.push_back(rota_para_cidade);
				}

				caminhos.push_back(rotas_cidade_atual);
			}
		}

		virtual void SetUp() {
			
		}
};

class DijkstraTest : public ::RotasTest {
protected:
	int a;
	Dijkstra dijkstra;

	virtual void SetUp() {
		RotasTest::SetUp();
		inicializa_rotas(graph);
				
		Caminho *menor_caminho = new Caminho[9];
		for (int i = 0; i < 9; i++) {
			menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i), cidades);
		}

		a = 7;
	}
};

TEST_F(DijkstraTest, validacaoTrivial)
{
	Caminho *menor_caminho = new Caminho[9];
	for (int i = 0; i < 9; i++) {
		menor_caminho[i] = dijkstra.dijkstra_menor_caminho(caminhos, cidades.at(i), cidades);
	}

	EXPECT_EQ(a, 7);	
}

class GilletJohnsonTest : public ::RotasTest {
	protected:
		int a;
		GilletJohnson gillet_johnson;

		virtual void SetUp() {
			RotasTest::SetUp();
			inicializa_rotas(graph2);

			//A e C são as medianas do graph2
			Cidade cidade_C = cidades.at(2);
			cidade_C.set_mediana(true);
			Cidade cidade_F = cidades.at(5);
			cidade_F.set_mediana(true);
			
			gillet_johnson = GilletJohnson();
			a = 5;
		}
};

TEST_F(GilletJohnsonTest, validacaoTrivial)
{	
	gillet_johnson.atribui_medianas(caminhos, cidades);
	
	EXPECT_EQ(a, 5);
}