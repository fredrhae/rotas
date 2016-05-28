// test_rotas.cpp : Defines the entry point for the console application.
//

#include "gtest/gtest.h"
#include "algoritmos/gillet_johnson.h"
#include "algoritmos/dijkstra.h"
#include "domain/caminho.h"
#include "cli/manipula_entrada.h"
#include "domain/context.h"

using namespace std;
using namespace rotas;
using namespace domain;
using namespace cli;

class RotasTest : public ::testing::Test {
protected:
	//std::vector<domain::Caminho> caminhos;
	std::vector<domain::Cidade> cidades;
	Context rotas_context;
	
	virtual void SetUp() {
		//Inicializa as cidades		
		string path_do_csv = "../../dados_entrada/cidades_atendidas.csv";
		rotas_context = ManipulaEntrada::inicializa_dados_partir_do_csv(path_do_csv);
		cidades = rotas_context.get_cidades_atendidas();
	}
};

TEST_F(RotasTest, validacaoInicializacaoDoCsv)
{		
	EXPECT_EQ(cidades.size(),32);
	
	vector<vector<Rota>> matriz = rotas_context.get_matriz_distancias();
	for (unsigned int i = 0; i < rotas_context.get_matriz_distancias().size(); i++)
	{
		cout << "Cidade " + cidades[i].get_nome()
			<< " sendo validada..." << endl;
		EXPECT_EQ(matriz[i].size(),32);
	}
	cout << "---------------------------" << endl;
}

class DijkstraTest : public ::RotasTest {
protected:
	int a;
	algoritmos::Dijkstra dijkstra;	

	virtual void SetUp() {
		RotasTest::SetUp();
		
		for (int i = 0; i < 9; i++) {	
			cout << "Calculando as menores rotas partindo de " << cidades[i].get_nome() << "... " << endl;
			dijkstra.dijkstra_menor_caminho(rotas_context, cidades[i]);
		}

		a = 7;
	}
};

TEST_F(DijkstraTest, validacaoTrivial)
{	
	EXPECT_EQ(a, 7);
}

TEST_F(DijkstraTest, validacaoDistanciasGrafoSimples)
{
	vector<double> distancias_origem_a = { 0, 406, 499, 234, 139, 364, 180, 178, 
		                                 429, 566, 627, 248, 318, 169, 731, 626, 
		                                 450, 709, 720, 800, 340, 410, 376, 439, 
		                                 519, 893, 664, 792, 687, 903, 797, 774 };
	
	
	for (int i = 0; i < rotas_context.get_cidades_atendidas().size(); i++)
	{
		cout << "Validando distância de " << cidades[0].get_nome() << " até " << cidades[i].get_nome() << "..." << endl;
		EXPECT_EQ(distancias_origem_a[i], cidades[0].get_rotas()[i].get_distancia());
	}	
	cout << endl;
}
class GilletJohnsonTest : public ::RotasTest {
protected:
	int a;
	algoritmos::GilletJohnson gillet_johnson;

	virtual void SetUp() {
		RotasTest::SetUp();
		cidades = rotas_context.get_cidades_atendidas();

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
	gillet_johnson.encontra_medianas(cidades);

	EXPECT_EQ(a, 5);
}
