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

		void inicializa_rotas() {
			caminhos = std::vector<Caminho>();
			init_cidades();

			for (int i = 0; i < 9; i++)
			{
				std::vector<Rota> rotas_cidade_atual = std::vector<Rota>();
				for (int j = 0; j < 9; j++)
				{
					Rota rota_para_cidade = Rota(cidades[j], graph[i][j]);
					rotas_cidade_atual.push_back(rota_para_cidade);
				}

				caminhos.push_back(rotas_cidade_atual);
			}
		}

		virtual void SetUp() {
			inicializa_rotas();
		}
};

class DijkstraTest : public ::RotasTest {
protected:
	int a;
	Dijkstra dijkstra;

	virtual void SetUp() {
		RotasTest::SetUp();
				
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
			gillet_johnson = GilletJohnson();
			a = 5;
		}
};

TEST_F(GilletJohnsonTest, validacaoTrivial)
{	
	gillet_johnson.atribui_medianas(caminhos, cidades);
	
	EXPECT_EQ(a, 5);
}