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
#define TEITZ_BART true
#define GILLET_JOHNSON true
#define CLARKE_WRIGHT true
#define INTEGRACAO true

class RotasTest : public ::testing::Test {
protected:
	std::vector<domain::Cidade> cidades;
	Context rotas_context;

	virtual void SetUp() {
		//Inicializa as cidades		
		//string path_do_csv = "../../dados_entrada/matriz_distancias_real_alfabetica.csv";
		string path_do_csv = "../../dados_entrada/matriz_distancias_real.csv";
		string path_do_csv_demandas = "../../dados_entrada/lista_demandas.csv";
		//rotas_context = ManipulaEntrada::inicializa_dados_partir_do_csv(path_do_csv);
		rotas_context = ManipulaEntrada::inicializa_dados_partir_do_csv_com_demanda(path_do_csv,path_do_csv_demandas);
		cidades = rotas_context.get_cidades_atendidas();
	}
};

TEST_F(RotasTest, validacaoInicializacaoDoCsv)
{
	EXPECT_EQ(cidades.size(), 93);

	vector<vector<Rota>> matriz = rotas_context.get_matriz_distancias();
	for (unsigned int i = 0; i < rotas_context.get_matriz_distancias().size(); i++)
	{
		cout << "Cidade " + cidades[i].get_nome()
			<< " sendo validada..." << endl;
		EXPECT_EQ(matriz[i].size(), 93);
	}
	cout << "---------------------------" << endl;
}

TEST_F(RotasTest, validacaoInicializacaoCsvComDemandas)
{
	EXPECT_EQ(cidades.size(), 93);

	vector<vector<Rota>> matriz = rotas_context.get_matriz_distancias();
	for (unsigned int i = 0; i < rotas_context.get_matriz_distancias().size(); i++)
	{
		cout << "Cidade " + cidades[i].get_nome()
			<< " sendo validada..." << endl;
		EXPECT_EQ(matriz[i].size(), 93);
		if(i > 0)
			ASSERT_GT(cidades[i].get_demanda(),0);
		else
			ASSERT_EQ(cidades[i].get_demanda(),0);
	}
	cout << "---------------------------" << endl;
}
#if DIJKSTRA

class DijkstraTest : public ::RotasTest {
protected:
	int a;
	algoritmos::Dijkstra dijkstra;
	string path_do_csv_simples = "../../dados_entrada/cidades_atendidas.csv";
	std::vector<domain::Cidade> cidades_teste_pequeno;
	Context rotas_context_teste_pequeno;

	virtual void SetUp() {
		RotasTest::SetUp();

		cout << "---------------------------" << endl;
		cout << "Calculando Dijkstra todas as cidades teste completo..." << endl;

		for (unsigned int i = 0; i < cidades.size(); i++) {
			cout << "Calculando as menores rotas partindo de " << cidades[i].get_nome() << "... " << endl;
			dijkstra.dijkstra_menor_caminho(rotas_context, cidades[i]);
		}

		cout << "---------------------------" << endl;

		cout << "Calculando Dijkstra todas as cidades teste pequeno..." << endl;

		rotas_context_teste_pequeno = ManipulaEntrada::inicializa_dados_partir_do_csv(path_do_csv_simples);
		cidades_teste_pequeno = rotas_context_teste_pequeno.get_cidades_atendidas();

		for (unsigned int i = 0; i < cidades_teste_pequeno.size(); i++) {
			cout << "Calculando as menores rotas partindo de " << cidades_teste_pequeno[i].get_nome() << "... " << endl;
			dijkstra.dijkstra_menor_caminho(rotas_context_teste_pequeno, cidades_teste_pequeno[i]);
		}

		cout << "---------------------------" << endl;

		a = 7;
	}
};

TEST_F(DijkstraTest, validacaoTrivial)
{
	EXPECT_EQ(a, 7);
}

TEST_F(DijkstraTest, validacaoDistanciasPoucasCidades)
{
	vector<double> distancias_origem_primeira_cidade = { 0, 406, 499, 234, 139, 364, 180, 178,
										 429, 566, 627, 248, 318, 169, 731, 626,
										 450, 709, 720, 800, 340, 410, 376, 439,
										 519, 893, 664, 792, 687, 903, 797, 774 };


	for (unsigned int i = 0; i < cidades_teste_pequeno.size(); i++)
	{
		cout << "Validando distância de " << cidades_teste_pequeno[0].get_nome() << " até " << cidades_teste_pequeno[i].get_nome() << "..." << endl;
		EXPECT_EQ(distancias_origem_primeira_cidade[i], cidades_teste_pequeno[0].get_rotas()[i].get_distancia());
	}
	cout << endl;
}

#endif // DIJKSTRA


#if TEITZ_BART

class TeitzBartTest : public ::RotasTest
{
protected:
	algoritmos::TeitzBart teitz_bart;
	algoritmos::Dijkstra dijkstra;

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

	unsigned int p = 6;

	cout << "Total de cidades: " << cidades.size() << endl;

	std::vector<Cidade> cidades_dijkstra;

	for (size_t i = 0; i < cidades.size(); i++)
	{
		Cidade c = cidades.at(i);

		c.set_rotas(dijkstra.dijkstra_menor_caminho(rotas_context, c));

		cidades_dijkstra.push_back(c);
	}

	teitz_bart.define_medianas(cidades_dijkstra, p);

	cout << "Cidades sedes: " << endl;

	unsigned int qtd_medianas = 0;

	for (size_t i = 0; i < cidades_dijkstra.size(); i++)
	{
		Cidade& c = cidades_dijkstra[i];

		if (c.is_mediana())
		{
			cout << "\t* " << c.get_nome() << endl;
			qtd_medianas++;
		}
	}

	ASSERT_EQ(qtd_medianas, p);
}

#endif // TEITZ_BART



#if GILLET_JOHNSON

class GilletJohnsonTest : public ::RotasTest {
protected:
	int a;
	unsigned int num_atribuidas = 0;
	unsigned int num_pontos_demanda = 0;
	unsigned int qtd_sedes = 7;
	vector<Cidade*> pontos_atendimento = vector<Cidade*>();

	algoritmos::GilletJohnson gillet_johnson;
	/*
	void set_demandas() {
		double demandas[] = { 403.20, 152, 646.2, 639.8, 1159.7, 49.2, 110.5, 231.5, 150, 328.8, 604, 343, 61.85, 156, 225.7,
							 505.85, 238, 356.98, 77.4, 597, 70, 882.25, 795.5, 300, 207.6, 127.8, 302.9, 194.5, 77.5, 150.5,
							 137.8, 105, 297.2, 409.4, 427.1, 216, 661.4, 1520, 649.5, 614.5, 60, 200.6, 839.95, 568.95, 3762.9,
							 292.2, 397.9, 589.8, 95.4, 696.55, 211.6, 217.4, 141, 531.82, 570.1, 91, 132, 551, 145.1, 260.63,
							 267.9, 46.2, 253, 1034.5, 486.2, 207.9, 910.5, 269.55, 225.1, 377.3, 133.8, 242.3, 337.5, 192.0,
							 105.7, 1446.5, 618.4, 506.2, 385.35, 532.55, 226.6, 398, 323.5, 90.6, 360.4, 282, 631, 2013.2, 94.8,
							 250.6, 160.8, 87.5 };

		for (unsigned int i = 0; i < cidades.size(); i++) {
			cidades[i].set_demanda(demandas[i]);
		}
	}*/

	std::vector<Cidade> cidades_dijkstra;
	virtual void SetUp() {
		RotasTest::SetUp();

		using namespace teitz_bart;
		Dijkstra dijkstra = Dijkstra();
		TeitzBart teitz_bart = TeitzBart();

		cout << "Total de cidades: " << cidades.size() << endl;


		for (size_t i = 0; i < cidades.size(); i++)
		{
			Cidade c = cidades.at(i);

			c.set_rotas(dijkstra.dijkstra_menor_caminho(rotas_context, c));

			cidades_dijkstra.push_back(c);
		}

		teitz_bart.define_medianas(cidades_dijkstra, qtd_sedes);

		cout << "Cidades sedes: " << endl;

		unsigned int qtd_medianas = 0;

		for (size_t i = 0; i < cidades_dijkstra.size(); i++)
		{
			Cidade& c = cidades_dijkstra[i];

			if (c.is_mediana())
			{
				cout << "\t* " << c.get_nome() << endl;
				qtd_medianas++;
			}
		}

		gillet_johnson = algoritmos::GilletJohnson();
		
		a = 5;

		

		for (unsigned int i = 0; i < cidades_dijkstra.size(); i++) {
			if (cidades_dijkstra[i].is_mediana()) {
				pontos_atendimento.push_back(&(cidades_dijkstra[i]));
			}
		}

		

		// Capacidades dos 3 caminhões
		double capacidades[] = { 6200, 8300, 11000 };

		for (size_t i = 0; i < pontos_atendimento.size(); i++) {
			pontos_atendimento[i]->set_capacidade(capacidades[i % 3]);
		}

		gillet_johnson.encontra_medianas(cidades_dijkstra);

	}
};

TEST_F(GilletJohnsonTest, testTodasCidadesAtribuidas)
{
	ASSERT_EQ(qtd_sedes, pontos_atendimento.size());

	for (unsigned int i = 0; i < cidades_dijkstra.size(); i++) {
		if (!cidades_dijkstra[i].is_mediana()) {
			num_pontos_demanda++;
			if (cidades_dijkstra[i].get_id_mediana() != -1) {
				num_atribuidas++;
			}
		}
	}

	EXPECT_NE(0, num_pontos_demanda);
	EXPECT_EQ(num_pontos_demanda, num_atribuidas);
	EXPECT_LT(num_pontos_demanda, cidades_dijkstra.size());
}

TEST_F(GilletJohnsonTest, testDesignaMedianas)
{	
	for (unsigned int i = 0; i < pontos_atendimento.size(); i++) {
		cout << "Cidades atendidas por " << pontos_atendimento[i]->get_nome() << ": " << endl;
		for (unsigned int j = 0; j < cidades_dijkstra.size(); j++) {
			if (cidades_dijkstra[j].get_id_mediana() == pontos_atendimento[i]->get_id()) {
				cout << cidades_dijkstra[j].get_nome() << ", Distancia: " << pontos_atendimento[i]->get_distancia(cidades_dijkstra[j]) << "km" << endl;
			}
		}

		cout << "-------------------------------------" << endl;
	}

	//Sobra capacidade em todas as cidades sede?
	double demanda_cidade;
	for (unsigned int i = 0; i < pontos_atendimento.size(); i++) {	
		demanda_cidade = 0;
		Cidade *ponto_atendimento = pontos_atendimento[i];
		for (unsigned int j = 0; j < cidades_dijkstra.size(); j++) {
			Cidade ponto_demanda = cidades_dijkstra[j];
			if (ponto_demanda.get_id_mediana() == ponto_atendimento->get_id()) {
				demanda_cidade += ponto_demanda.get_demanda();
			}
		}
		cout << "Capacidade de " << ponto_atendimento->get_nome() << ": " << ponto_atendimento->get_capacidade() << endl;
		cout << "Demanda para " << ponto_atendimento->get_nome() << ": " << demanda_cidade << endl;
		EXPECT_LE(demanda_cidade, ponto_atendimento->get_capacidade());
	}

	//A soma da demanda de todas as cidades atendidas é menor que a capacidade da respectiva cidade sede?
	//Imprime a capacidade total atendida por cada cidade sede

	//TODO verificar quais cidades deveriam ser atendidas por quais sedes
	ASSERT_TRUE(cidades[19].get_id_mediana() != 0);
	ASSERT_TRUE(cidades[29].get_id_mediana() != 0);
}


#if 0
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

	Cidade mais_proxima = origem.encontra_mais_proxima(destinos);

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

	vector<Cidade> cidades_ordenadas = origem.ordena_por_distancia(destinos);

	EXPECT_EQ(21, cidades_ordenadas[0].get_id());
	EXPECT_EQ(20, cidades_ordenadas[1].get_id());
	EXPECT_EQ(0, cidades_ordenadas[2].get_id());
	EXPECT_EQ(12, cidades_ordenadas[3].get_id());
	EXPECT_EQ(30, cidades_ordenadas[4].get_id());
}
#endif

#endif //GILLET_JOHNSON

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
	double distancia_encontrada = cidade_a.get_distancia(cidade_b);

	EXPECT_EQ(638, distancia_encontrada);

	cidade_a = cidades[6];
	cidade_b = cidades[22];

	distancia_encontrada = cidade_a.get_distancia(cidade_b);
	EXPECT_EQ(158, distancia_encontrada);

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

	vector<vector<vector<Rota>>> savings = clarke_wright.encontra_roteamentos(cidades);

	for (unsigned int w = 0; w < savings.size(); w++)
	{
		cout << "Savings extraidos da cidade sede :" << endl;
		for (unsigned int i = 0; i < savings[w].size(); i++) {
			for (unsigned int j = 0; j < savings[w][i].size(); j++)
			{
				cout << "S" << savings[w][i][j].get_id_origem() << "," << savings[w][i][j].get_id_destino() <<
					"= " << savings[w][i][j].get_distancia() << "km" << endl;
			}
		}
	}

	cout << "-------------------------------------" << endl;

	EXPECT_EQ(0, 0);
}

#endif // CLARKE_WRIGHT

#if INTEGRACAO

class IntegracaoTest : public ::RotasTest
{
protected:
	algoritmos::Dijkstra dijkstra;
	algoritmos::TeitzBart teitz_bart;
	algoritmos::GilletJohnson gillet_johnson;
	algoritmos::ClarkeWright clarke_wright;

	virtual void SetUp()
	{
		RotasTest::SetUp();
	}
};

TEST_F(IntegracaoTest, testIntegracao)
{
	using namespace teitz_bart;

	unsigned int qtd_sedes = 7; // Quantidade de medianas (cidades sede)

	//
	// Dijkstra

	size_t qtd_cidades = cidades.size();

	cout << "[Dijkstra] Carregando rotas mais curtas para " << qtd_cidades << " cidades..." << endl;

	for (size_t i = 0; i < qtd_cidades; i++)
	{
		Cidade& c = cidades[i];

		c.set_rotas(dijkstra.dijkstra_menor_caminho(rotas_context, c));
	}

	//
	// Teitz & Bart

	cout << "[Teitz & Bart] Definindo " << qtd_sedes << " sedes..." << endl;

	teitz_bart.define_medianas(cidades, qtd_sedes);

	std::vector<Cidade> medianas;

	for (size_t i = 0; i < cidades.size(); i++)
	{
		Cidade& c = cidades[i];

		if (c.is_mediana())
		{
			cout << "\t- " << c.get_nome() << endl;
			medianas.push_back(c);
		}
	}

	//
	// Gillett & Johnson

	cout << "[Gillett & Johnson] Localizando clusters..." << endl;
	
	vector<Cidade*> pontos_atendimento = vector<Cidade*>();

	for (unsigned int i = 0; i < cidades.size(); i++) {
		if (cidades[i].is_mediana()) {
			pontos_atendimento.push_back(&(cidades[i]));
		}
	}

	ASSERT_EQ(qtd_sedes, pontos_atendimento.size());

	// Setando 2 caminhões por cidade, conforme acordado
	// Capacidades dos 3 caminhões
	double capacidades[] = { 6200, 8300, 11000 };

	for (size_t i = 0; i < pontos_atendimento.size(); i++) {
		pontos_atendimento[i]->set_capacidade(capacidades[i % 3]);
	}
	
	gillet_johnson.encontra_medianas(cidades);

	for (size_t i = 0; i < cidades.size(); i++)
	{
		Cidade& mediana = cidades[i];

		if (mediana.is_mediana() == false)
		{
			continue;
		}

		cout << "[Gillett & Johnson] Cidades atendidas por " << mediana.get_nome() << endl;

		for (size_t j = 0; j < cidades.size(); j++)
		{
			Cidade& c = cidades[j];

			if (c.get_id_mediana() != mediana.get_id())
			{
				continue;
			}

			cout << "\t- " << c.get_nome() << ", Distancia: " << mediana.get_distancia(c) << "km" << endl;
		}
	}

	//
	// Clarke & Wright

	cout << "[Clarke & Wright] Localizando rotas nos clusters..." << endl;

	vector<vector<vector<Rota>>> savings = clarke_wright.encontra_roteamentos(cidades);

	for (size_t w = 0; w < savings.size(); w++)
	{
		cout << "Savings extraidos da cidade sede " << medianas[w].get_nome() << ":" << endl;
		for (size_t i = 0; i < savings[w].size(); i++) {
			for (size_t j = 0; j < savings[w][i].size(); j++)
			{
				cout << "\t- S" << savings[w][i][j].get_id_origem() << "," << savings[w][i][j].get_id_destino() <<
					"= " << savings[w][i][j].get_distancia() << "km" << endl;
			}
		}
	}
}

#endif // INTEGRACAO

