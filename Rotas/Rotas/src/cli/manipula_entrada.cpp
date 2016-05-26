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


void inicializa_cidades(vector<string> vetor_nomes_cidades)
{
	cidades = vector<Cidade>();

	for (unsigned int i = 0; i < vetor_nomes_cidades.size(); i++)
	{
		Cidade cidade_atual = Cidade(vetor_nomes_cidades.at(i), i);
		cidades.push_back(cidade_atual);
	}
}

void inicializa_rotas(vector<vector<string>> matriz_distancias_string)
{
	matriz_distancias = vector<vector<Rota>>();

	for (unsigned int i = 0; i < matriz_distancias_string.size(); i++)
	{
		vector<Rota> rotas_cidade_atual = vector<Rota>();

		for (unsigned int j = 0; j < matriz_distancias_string[i].size(); j++)
		{
			Rota rota_para_cidade = Rota(i, j, std::stod(matriz_distancias_string[i][j]));
			rotas_cidade_atual.push_back(rota_para_cidade);
		}

		matriz_distancias.push_back(rotas_cidade_atual);
	}
}

void inicializa_rotas_em_cidades()
{
	for (unsigned int i = 0; i < cidades.size(); i++)
	{
		cidades[i].set_rotas(matriz_distancias[i]);
	}
}

bool checa_path_e_valido(string path)
{
	ifstream test(path);
	if (!test)
	{
		return false;
	}

	return true;
}

bool checa_matriz_quadrada(vector<vector<string>> matriz_distancias)
{
	bool e_quadrada = true;
	for (unsigned int i = 1; i < matriz_distancias.size(); i++)
	{
		if (matriz_distancias.at(i).size() != cidades.size())
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
	for (unsigned int i = 0; i < matriz_distancias.size(); i++)
	{
		for (unsigned int j = 0; j < matriz_distancias.size(); j++)
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
	for (unsigned int i = 0; i < matriz_distancias.size(); i++)
	{
		if (matriz_distancias[i][i] != "0")
		{
			diagonal_e_zero = false;
			break;
		}
	}

	return diagonal_e_zero;
}

vector<vector<string>> remove_elementos_desnecessarios(vector<vector<string>> matriz_distancias)
{
	vector<vector<string>> nova_matriz_distancias = matriz_distancias;

	// Remove a primeira coluna de todas as linhas
	for (unsigned int i = 0; i < nova_matriz_distancias.size(); i++)
	{
		nova_matriz_distancias[i].erase(nova_matriz_distancias[i].begin());
	}
	
	return nova_matriz_distancias;
}
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

vector<vector<string>> extrai_matriz_distancia(string path)
{
	ifstream infile(path);
	string line = "";
	vector<vector<string>> matriz_distancias_string;
	while (getline(infile, line))
	{
		vector<string> colunas_matriz = extrai_colunas_matriz(line);
		matriz_distancias_string.push_back(colunas_matriz);
	}

	return matriz_distancias_string;
}
Context ManipulaEntrada::inicializa_dados_partir_do_csv(string path)
{

	if(!checa_path_e_valido(path))
		return Context();

	vector<vector<string>> matriz_distancias_string = extrai_matriz_distancia(path);
	
	matriz_distancias_string =	remove_elementos_desnecessarios(matriz_distancias_string);

	inicializa_cidades(matriz_distancias_string.front());

	// Remove a primeira linha com os nomes das cidades
	matriz_distancias_string.erase(matriz_distancias_string.begin());

	bool matriz_e_quadrada, matriz_e_simetrica, diagonal_e_zero;
	
	matriz_e_quadrada = checa_matriz_quadrada(matriz_distancias_string);
	//matriz_e_simetrica = checa_matriz_simetrica(matriz_distancias_string);
	diagonal_e_zero = checa_matriz_diagonal(matriz_distancias_string);

	if(!matriz_e_quadrada || !diagonal_e_zero)
		return Context();

	inicializa_rotas(matriz_distancias_string);

	inicializa_rotas_em_cidades();

	Context context_inicializado = Context(cidades, matriz_distancias);
	
	vector<Rota> teste = context_inicializado.get_cidades_atendidas()[0].get_rotas();

	return context_inicializado;
}

