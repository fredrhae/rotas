// test_rotas.cpp : Defines the entry point for the console application.
//

#include "algoritmos/gillet_johnson.h"
#include "algoritmos/dijkstra.h"
#include "algoritmos/teitz_bart.h"
#include "algoritmos/clarke_wright.h"
#include "cli/manipula_entrada.h"
#include "domain/context.h"
#include "gtest/gtest.h"

using namespace std;
using namespace rotas;
using namespace domain;
using namespace cli;
using namespace algoritmos;

#define DIJKSTRA true
#define GILLET_JOHNSON true
#define TEITZ_BART true
#define CLARKE_WRIGHT true

class RotasTest : public ::testing::Test {
protected:
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
	EXPECT_EQ(cidades.size(), 32);

	vector<vector<Rota>> matriz = rotas_context.get_matriz_distancias();
	for (unsigned int i = 0; i < rotas_context.get_matriz_distancias().size(); i++)
	{
		cout << "Cidade " + cidades[i].get_nome()
			<< " sendo validada..." << endl;
		EXPECT_EQ(matriz[i].size(), 32);
	}
	cout << "---------------------------" << endl;
}
#if DIJKSTRA

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


	for (int i = 0; i < cidades.size(); i++)
	{
		cout << "Validando distância de " << cidades[0].get_nome() << " até " << cidades[i].get_nome() << "..." << endl;
		EXPECT_EQ(distancias_origem_a[i], cidades[0].get_rotas()[i].get_distancia());
	}
	cout << endl;
}

#endif // DIJKSTRA

#if GILLET_JOHNSON

class GilletJohnsonTest : public ::RotasTest {
protected:
	int a;
	algoritmos::GilletJohnson gillet_johnson;

	virtual void SetUp() {
		RotasTest::SetUp();

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
	EXPECT_EQ(a, 5);
}

TEST_F(GilletJohnsonTest, testGetDistancia)
{
	//double get_distancia(Cidade a, Cidade b);
	Cidade cidade_a = cidades[0];
	Cidade cidade_b = cidades[1];
	double distancia_encontrada = cidade_a.get_distancia(cidade_b);

	EXPECT_EQ(406, distancia_encontrada);

	cidade_a = cidades[6];
	cidade_b = cidades[22];

	distancia_encontrada = cidade_a.get_distancia(cidade_b);
	EXPECT_EQ(211, distancia_encontrada);
}

TEST_F(GilletJohnsonTest, testEncontraMaisProxima)
{
	Cidade origem = cidades[10];
	Cidade destino1 = cidades[21];
	Cidade destino2 = cidades[12];
	Cidade destino3 = cidades[30];
	Cidade destino4 = cidades[20];
	Cidade destino5 = cidades[0];

	vector<Cidade> destinos = vector<Cidade>();

	destinos.push_back(cidades[21]);
	destinos.push_back(cidades[12]);
	destinos.push_back(cidades[30]);
	destinos.push_back(cidades[20]);
	destinos.push_back(cidades[0]);

	Cidade mais_proxima = gillet_johnson.encontra_mais_proxima(origem, destinos);

	EXPECT_EQ(21, mais_proxima.get_id());
}

TEST_F(GilletJohnsonTest, testOrdenaPorDistancia)
{
	Cidade origem = cidades[10];
	Cidade destino1 = cidades[21];
	Cidade destino2 = cidades[12];
	Cidade destino3 = cidades[30];
	Cidade destino4 = cidades[20];
	Cidade destino5 = cidades[0];

	vector<Cidade> destinos = vector<Cidade>();

	destinos.push_back(cidades[21]);
	destinos.push_back(cidades[12]);
	destinos.push_back(cidades[30]);
	destinos.push_back(cidades[20]);
	destinos.push_back(cidades[0]);

	vector<Cidade> cidades_ordenadas = gillet_johnson.ordena_por_distancia(origem, destinos);

	EXPECT_EQ(21, cidades_ordenadas[0].get_id());
	EXPECT_EQ(20, cidades_ordenadas[1].get_id());
	EXPECT_EQ(0, cidades_ordenadas[2].get_id());
	EXPECT_EQ(12, cidades_ordenadas[3].get_id());
	EXPECT_EQ(30, cidades_ordenadas[4].get_id());
}

TEST_F(GilletJohnsonTest, testDesignaMedianas)
{
	//Escolhe 3 medianas ao acaso
	cidades[10].set_mediana(true);
	cidades[20].set_mediana(true);
	cidades[30].set_mediana(true);

	gillet_johnson.encontra_medianas(cidades);

	cout << "Cidades atendidas por " << cidades[10].get_nome() << ": " << endl;
	for (unsigned int i = 0; i < cidades.size(); i++) {
		if (cidades[i].get_id_mediana() == 10) {
			cout << cidades[i].get_nome() << ", Distancia: " << cidades[10].get_distancia(cidades[i]) << "km" << endl;
		}
	}

	cout << "-------------------------------------" << endl;

	cout << "Cidades atendidas por " << cidades[20].get_nome() << ": " << endl;
	for (unsigned int i = 0; i < cidades.size(); i++) {
		if (cidades[i].get_id_mediana() == 20) {
			cout << cidades[i].get_nome() << ", Distancia: " << cidades[20].get_distancia(cidades[i]) << "km" << endl;
		}
	}

	cout << "-------------------------------------" << endl;

	cout << "Cidades atendidas por " << cidades[30].get_nome() << ": " << endl;
	for (unsigned int i = 0; i < cidades.size(); i++) {
		if (cidades[i].get_id_mediana() == 30) {
			cout << cidades[i].get_nome() << ", Distancia: " << cidades[30].get_distancia(cidades[i]) << "km" << endl;
		}
	}

	//TODO verificar quais cidades deveriam ser atendidas por quais sedes
	EXPECT_EQ(0, 0);
}

#endif //GILLET_JOHNSON

#if TEITZ_BART

class TeitzBartTest : public ::RotasTest
{
protected:
	algoritmos::TeitzBart teitz_bart;

	virtual void SetUp()
	{
		RotasTest::SetUp();
	}
};

TEST_F(TeitzBartTest, inicializaVertices)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices = algoritmos::TeitzBart::inicializa_vertices(cidades);
	cout << "Numero total de vertices: " << todos_os_vertices.size() << endl;

	ASSERT_EQ(cidades.size(), todos_os_vertices.size());
}

TEST_F(TeitzBartTest, selecionaMedianasAleatoriamente)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices = algoritmos::TeitzBart::inicializa_vertices(cidades);
	lista_vertices_t medianas = teitz_bart.seleciona_medianas_aleatoriamente(todos_os_vertices, 10);

	ASSERT_EQ(medianas.size(), 10);
}

TEST_F(TeitzBartTest, contemVertice)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices;

	vertice_t v1(Cidade("c1", 1));
	vertice_t v2(Cidade("c2", 2));
	vertice_t v3(Cidade("c3", 3));
	vertice_t v4(Cidade("c4", 4));
	vertice_t v5(Cidade("c5", 5));

	todos_os_vertices.push_back(v1);
	todos_os_vertices.push_back(v2);
	todos_os_vertices.push_back(v3);
	todos_os_vertices.push_back(v4);
	todos_os_vertices.push_back(v5);

	lista_vertices_t medianas;

	medianas.push_back(v1);
	medianas.push_back(v2);

	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(todos_os_vertices, v1));
	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(todos_os_vertices, v2));
	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(todos_os_vertices, v3));
	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(todos_os_vertices, v4));
	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(todos_os_vertices, v5));

	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(medianas, v1));
	ASSERT_TRUE(algoritmos::TeitzBart::contem_vertice(medianas, v2));
	ASSERT_FALSE(algoritmos::TeitzBart::contem_vertice(medianas, v3));
	ASSERT_FALSE(algoritmos::TeitzBart::contem_vertice(medianas, v4));
	ASSERT_FALSE(algoritmos::TeitzBart::contem_vertice(medianas, v5));
}

TEST_F(TeitzBartTest, rotulaNaoAnalisados)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices = algoritmos::TeitzBart::inicializa_vertices(cidades);

	lista_vertices_t medianas = teitz_bart.seleciona_medianas_aleatoriamente(todos_os_vertices, 10);

	teitz_bart.rotula_nao_analisados(todos_os_vertices, medianas);

	int qtd_nao_analisados = 0;

	for (size_t i = 0; i < todos_os_vertices.size(); i++)
	{
		if (todos_os_vertices.at(i).analisado == false)
		{
			qtd_nao_analisados++;
		}
	}

	cout << "Numero total de vertices: " << todos_os_vertices.size() << endl;
	cout << "Quantidade aleatoria de medianas: " << medianas.size() << endl;
	cout << "Quantidade de vertices nao analisados: " << qtd_nao_analisados << endl;

	ASSERT_EQ(qtd_nao_analisados, (todos_os_vertices.size() - medianas.size()));
}

TEST_F(TeitzBartTest, existeNaoAnalisados)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices = algoritmos::TeitzBart::inicializa_vertices(cidades);

	lista_vertices_t medianas = teitz_bart.seleciona_medianas_aleatoriamente(todos_os_vertices, 5);
	teitz_bart.rotula_nao_analisados(todos_os_vertices, medianas);
	ASSERT_TRUE(teitz_bart.existe_nao_analisados(todos_os_vertices));

	medianas = teitz_bart.seleciona_medianas_aleatoriamente(todos_os_vertices, todos_os_vertices.size());
	teitz_bart.rotula_nao_analisados(todos_os_vertices, medianas);
	ASSERT_FALSE(teitz_bart.existe_nao_analisados(todos_os_vertices));
}

TEST_F(TeitzBartTest, verticesParaCidades)
{
	using namespace teitz_bart;

	lista_vertices_t todos_os_vertices = algoritmos::TeitzBart::inicializa_vertices(cidades);
	std::vector<Cidade> cidades = TeitzBart::vertices_para_cidades(todos_os_vertices);

	ASSERT_EQ(cidades.size(), todos_os_vertices.size());
}

TEST_F(TeitzBartTest, calculaNumeroTransmissaoPadrao)
{
	using namespace teitz_bart;

	// TODO
}

TEST_F(TeitzBartTest, calculaNumeroTransmissaoAlterandoVetor)
{
	using namespace teitz_bart;

	// TODO
}

TEST_F(TeitzBartTest, localizaMedianas)
{
	using namespace teitz_bart;

	unsigned int p = 1;

	cout << "Total de cidades: " << cidades.size() << endl;

	std::vector<Cidade> cidades = teitz_bart.localiza_medianas(rotas_context.get_cidades_atendidas(), p);

	cout << "Cidades sedes: " << endl;

	for (size_t i = 0; i < cidades.size(); i++)
	{
		cout << "\t* " << cidades.at(i).get_nome() << endl;
	}

	ASSERT_EQ(cidades.size(), p);
}

#endif // TEITZ_BART

#if CLARKE_WRIGHT

class ClarkeWrightTest : public ::RotasTest {
protected:
	int a;
	algoritmos::ClarkeWright clarke_wright;
	algoritmos::GilletJohnson gillet_johnson;

	virtual void SetUp() {
		RotasTest::SetUp();
		clarke_wright = algoritmos::ClarkeWright();
		gillet_johnson = algoritmos::GilletJohnson();
		a = 10;
	}
};

TEST_F(ClarkeWrightTest, validacaoTrivial)
{
	EXPECT_EQ(a, 10);
}

TEST_F(ClarkeWrightTest, testGetDistancia)
{
	Cidade cidade_a = cidades[0];
	Cidade cidade_b = cidades[1];
	double distancia_encontrada = clarke_wright.get_distancia(cidade_a, cidade_b);

	EXPECT_EQ(406, distancia_encontrada);

	cidade_a = cidades[6];
	cidade_b = cidades[22];

	distancia_encontrada = clarke_wright.get_distancia(cidade_a, cidade_b);
	EXPECT_EQ(211, distancia_encontrada);

}

TEST_F(ClarkeWrightTest, testOrdenaSavingsMaiorProMenor)
{
	EXPECT_EQ(a, 10);
}

TEST_F(ClarkeWrightTest, testEncontraRoteamentos)
{
	//Escolhe 3 medianas ao acaso
	cidades[10].set_mediana(true);
	cidades[20].set_mediana(true);
	cidades[30].set_mediana(true);

	gillet_johnson.encontra_medianas(cidades);

	vector<vector<Rota>> savings = clarke_wright.encontra_roteamentos(cidades);

	cout << "Savings extraidos da cidade sede " << cidades[10].get_nome() << ": " << endl;
	for (unsigned int i = 0; i < savings[0].size(); i++) {
			cout <<"S"<< savings[0][i].get_id_origem() << "," << savings[0][i].get_id_destino() <<
				"= " << savings[0][i].get_distancia() << "km" << endl;
		
	}

	cout << "-------------------------------------" << endl;

	EXPECT_EQ(0, 0);
}
	
#endif // CLARKE_WRIGHT

