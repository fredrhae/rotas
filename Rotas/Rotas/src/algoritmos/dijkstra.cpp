#include "dijkstra.h"
#include <iostream>
#include <string>

// Uma funcao auxiliar que acha a cidade com menor distância de um 
// conjunto de cidades ainda não inclusos na rota
int Dijkstra::minima_distancia_partindo_da_origem(double distancias[], bool marcador_distancia_encontrada[], int numero_cidades)
{
	// Initialize min value
	double min = Dijkstra::max_distance;
	int min_index;

	for (int v = 0; v < numero_cidades; v++)
	{
		if (marcador_distancia_encontrada[v] == false && distancias[v] <= min)
		{
			min = distancias[v];
			min_index = v;
		}
	}
	return min_index;
}

// A utility function to print the constructed MST stored in parent[]
void Dijkstra::imprime_caminho_curto_dijkstra(Caminho menor_caminho)
{
	std::string nome_origem = menor_caminho.get_origem().get_nome();
	std::cout << "Menores caminhos encontrados partindo da origem " + nome_origem +":" << std::endl;
	for (int i = 0; i < menor_caminho.distancias_entre_cidades.size(); i++)
		std::cout << menor_caminho.distancias_entre_cidades[i].get_destino().get_nome() << "(" <<
		 i << ") - \t\t " << menor_caminho.distancias_entre_cidades[i].get_distancia() << std::endl;
}

double* Dijkstra::inicializa_distancias_encontradas(int total_cidades)
{
	// Vetor com as menores distancias encontradas a partir da origem pra todas as demais cidades
	double *distancias_encontradas = new double[total_cidades];
	
	for (int i = 0; i < total_cidades; i++)
	{
		distancias_encontradas[i] = max_distance;
	}

	return distancias_encontradas;
}

bool* inicializa_marcador_cidades_processadas(int total_cidades)
{
	// Vetor com a marcacao das cidades que ja foram incluidas no menor caminho ou todas
	// as distancias foram encontradas
	bool *menor_distancia_encontrada = new bool[total_cidades];

	for (int i = 0; i < total_cidades; i++)
	{
		menor_distancia_encontrada[i] = false;
	}

	return menor_distancia_encontrada;
}

Caminho gera_menor_caminho_dijkstra(double distancias[], int n, std::vector<Cidade> cidades)
{
	Caminho menores_distancias;
	for (int index = 0; index < n; index++)
	{
		Rota rota_atual = Rota(cidades[index], distancias[index]);
		menores_distancias.distancias_entre_cidades.push_back(rota_atual);
	}
	
	return menores_distancias;
}

// Funcao que implementa algoritmo de menor caminho de origem única do Dijkstra
// para um grafo dado representado como matriz de adjacência
Caminho Dijkstra::dijkstra_menor_caminho(std::vector<Caminho> distancias, Cidade origem, std::vector<Cidade> cidades)
{
	// Se matriz de adjacencia for vazia, nao ha nada a fazer
	if(distancias.size() < 1)
		return Caminho();

	// Vetor com as menores distancias encontradas a partir da origem pra todas as demais cidades
	double *distancias_encontradas = inicializa_distancias_encontradas(distancias.size()); 


	bool *marcador_distancia_encontrada = inicializa_marcador_cidades_processadas(distancias.size());

	// Distancia para a cidade de origem sempre e 0
	distancias_encontradas[origem.get_id()] = 0;

	// Acha menor caminho para todas as cidades
	for (int count = 0; count < distancias.size() - 1; count++)
	{
		// Pega a menor distancia para a cidade do conjunto de cidades ainda nao processados.
		// u e igual a origem na primeira iteracao
		int u = minima_distancia_partindo_da_origem(distancias_encontradas, marcador_distancia_encontrada, distancias.size());

		// Marca a cidade escolhida como processada
		marcador_distancia_encontrada[u] = true;

		// Atualiza o valor da distancia das cidades adjacentes a cidade escolhida nessa iteracao
		for (int v = 0; v < distancias.size(); v++)
		{
			// Atualiza distancias encontradas apenas se ela tiver marcada como 
			// como nao encontrada, se tiver um caminho da cidade u para v, e a distancia
			// da origem apara cidade v passando por u for menor que a menor distancia
			// atualmente setada em v
			double distancia_para_cidade_sendo_processada = distancias[u].distancias_entre_cidades[v].get_distancia();

			double nova_distancia = distancias_encontradas[u] + distancia_para_cidade_sendo_processada;

			bool distancia_menor_encontrada = nova_distancia < distancias_encontradas[v];

			bool menor_distancia_nao_encontrada = !marcador_distancia_encontrada[v];
			
			if (menor_distancia_nao_encontrada && distancia_para_cidade_sendo_processada && distancias_encontradas[u] != max_distance
				&& distancia_menor_encontrada)
				distancias_encontradas[v] = nova_distancia;
		}
	}

	// Gera o caminho com as rotas encontradas
	Caminho menor_caminho = gera_menor_caminho_dijkstra(distancias_encontradas, distancias.size(), cidades);

	// print the constructed distance array
	imprime_caminho_curto_dijkstra(menor_caminho);

	// Libera memoria de vetores alocados
	delete[] distancias_encontradas;
	delete[] marcador_distancia_encontrada;

	return menor_caminho;
}