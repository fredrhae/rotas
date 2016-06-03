#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "cli\manipula_entrada.h"

using namespace rotas::domain;
using namespace rotas::cli;
using namespace std;

vector<Cidade> cidades;
vector<vector<Rota>> matriz_distancias;


//############  Funcoes relacionadas a inicializacao da matriz de distancias   ###########

void inicializa_cidades(vector<string> vetor_nomes_cidades)
{
	cidades = vector<Cidade>();

	int size_vetor_cidades = vetor_nomes_cidades.size();

	for (unsigned int i = 0; i < size_vetor_cidades; i++)
	{
		Cidade cidade_atual = Cidade(vetor_nomes_cidades.at(i), i);
		cidades.push_back(cidade_atual);
	}
}

void inicializa_rotas(vector<vector<string>> matriz_distancias_string)
{
	matriz_distancias = vector<vector<Rota>>();

	int size_matriz_distancias = matriz_distancias_string.size();

	for (unsigned int i = 0; i < size_matriz_distancias; i++)
	{
		vector<Rota> rotas_cidade_atual = vector<Rota>();
		int size_linha_atual = matriz_distancias_string[i].size();

		for (unsigned int j = 0; j < size_linha_atual; j++)
		{
			Rota rota_para_cidade = Rota(i, j, std::stod(matriz_distancias_string[i][j]));
			rotas_cidade_atual.push_back(rota_para_cidade);
		}

		matriz_distancias.push_back(rotas_cidade_atual);
	}
}

void inicializa_rotas_em_cidades()
{
	int size_cidades = cidades.size();

	for (unsigned int i = 1; i < size_cidades; i++)
	{
		cidades[i].set_rotas(matriz_distancias[i]);
	}
}

bool checa_matriz_quadrada(vector<vector<string>> matriz_distancias)
{
	bool e_quadrada = true;
	int size_matriz_distancias = matriz_distancias.size();
	int size_cidades = cidades.size();

	for (unsigned int i = 1; i < size_matriz_distancias; i++)
	{
		if (matriz_distancias.at(i).size() != size_cidades)
		{
			e_quadrada = false;
			break;
		}
	}

	return e_quadrada;
}

bool checa_matriz_simetrica(vector<vector<string>> matriz_distancias)
{
	bool e_simetrica = true;
	int size_matriz_distancias = matriz_distancias.size();

	for (unsigned int i = 0; i < size_matriz_distancias; i++)
	{
		for (unsigned int j = 0; j < size_matriz_distancias; j++)
		{
			if (matriz_distancias[i][j] != matriz_distancias[j][i])
			{
				e_simetrica = false;
				break;
			}
		}
	}

	return e_simetrica;
}

bool checa_matriz_diagonal(vector<vector<string>> matriz_distancias)
{
	bool diagonal_e_zero = true;
	int size_matriz_distancias = matriz_distancias.size();

	for (unsigned int i = 0; i < size_matriz_distancias; i++)
	{
		if (matriz_distancias[i][i] != "0")
		{
			diagonal_e_zero = false;
			break;
		}
	}

	return diagonal_e_zero;
}

void remove_elementos_desnecessarios_matriz_distancia(vector<vector<string>> &matriz_distancias)
{
	int size_matriz_distancias = matriz_distancias.size();

	// Remove a primeira coluna de todas as linhas
	for (unsigned int i = 0; i < size_matriz_distancias; i++)
	{
		matriz_distancias[i].erase(matriz_distancias[i].begin());
	}
}

//###############  Funcoes relacionadas a matriz de demandas   ################3

void inicializa_demandas(vector<vector<string>> matriz_demandas)
{
	int size_matriz_demandas = matriz_demandas.size();

	for (unsigned int i = 0; i < size_matriz_demandas; i++)
	{
		cidades[i].set_demanda(std::stod(matriz_demandas[i][1]));
	}
}

//############################################################

vector<string> extrai_colunas_matriz(string linha_matriz)
{
	stringstream linha_matriz_stream(linha_matriz);
	string word = "";
	vector<string> colunas_da_linha;
	while (getline(linha_matriz_stream, word, ';'))
	{
		colunas_da_linha.push_back(word);
	}

	return colunas_da_linha;
}

vector<vector<string>> extrai_matriz_dados(string path)
{
	ifstream infile(path);
	string line = "";
	vector<vector<string>> matriz_dados_em_string;
	while (getline(infile, line))
	{
		vector<string> colunas_matriz = extrai_colunas_matriz(line);
		matriz_dados_em_string.push_back(colunas_matriz);
	}

	return matriz_dados_em_string;
}

bool checa_path_e_invalido(string path)
{
	ifstream test(path);
	if (!test)
	{
		return true;
	}

	return false;
}

Context ManipulaEntrada::inicializa_dados_partir_do_csv(string path)
{

	if(checa_path_e_invalido(path))
		return Context();

	vector<vector<string>> matriz_distancias_string = extrai_matriz_dados(path);
	
	remove_elementos_desnecessarios_matriz_distancia(matriz_distancias_string);

	inicializa_cidades(matriz_distancias_string.front());

	// Remove a primeira linha com os nomes das cidades
	matriz_distancias_string.erase(matriz_distancias_string.begin());

	bool matriz_e_quadrada, diagonal_e_zero;
	
	matriz_e_quadrada = checa_matriz_quadrada(matriz_distancias_string);
	diagonal_e_zero = checa_matriz_diagonal(matriz_distancias_string);

	if(!matriz_e_quadrada || !diagonal_e_zero)
		return Context();

	inicializa_rotas(matriz_distancias_string);

	inicializa_rotas_em_cidades();

	Context context_inicializado = Context(cidades, matriz_distancias);

	return context_inicializado;
}

Context ManipulaEntrada::inicializa_dados_partir_do_csv_com_demanda(string path_matriz, string path_demandas)
{

	if (checa_path_e_invalido(path_demandas) || checa_path_e_invalido(path_matriz))
		return Context();

	inicializa_dados_partir_do_csv(path_matriz);

	vector<vector<string>> matriz_demandas = extrai_matriz_dados(path_demandas);

	// Remove a primeira linha com os nomes de cidade e demanda
	matriz_demandas.erase(matriz_demandas.begin());

	inicializa_demandas(matriz_demandas);

	Context context_inicializado = Context(cidades, matriz_distancias);

	return context_inicializado;
}

