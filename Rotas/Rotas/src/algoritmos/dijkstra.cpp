#include "dijkstra.h"
#include <iostream>
#include <string>

namespace rotas
{
	namespace algoritmos
	{
		// Variaveis globais usadas pela maioria das funcoes
		static std::vector<Cidade> cidades;
		static Cidade origem;
		
		// Uma funcao auxiliar que acha a cidade com menor distância de um 
		// conjunto de cidades ainda não inclusos na rota
		int Dijkstra::minima_distancia_partindo_da_origem(double distancias[], bool marcador_distancia_encontrada[])
		{
			// Initialize min value
			double min = Dijkstra::max_distance;
			int min_index;

			for (unsigned int v = 0; v < cidades.size(); v++)
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
			std::string nome_origem = origem.get_nome();
			std::cout << "Menores caminhos encontrados partindo da origem " + nome_origem + ":" << std::endl;
			for (unsigned int i = 0; i < menor_caminho.get_trajeto().size(); i++)
				std::cout << cidades[menor_caminho.get_trajeto()[i].get_id_destino()].get_nome() << "(" <<
				i << ") - \t\t " << menor_caminho.get_trajeto()[i].get_distancia() << std::endl;
		}

		double* Dijkstra::inicializa_distancias_encontradas()
		{
			// Vetor com as menores distancias encontradas a partir da origem pra todas as demais cidades
			double *distancias_encontradas = new double[cidades.size()];

			for (unsigned int i = 0; i < cidades.size(); i++)
			{
				distancias_encontradas[i] = max_distance;
			}

			return distancias_encontradas;
		}

		bool* inicializa_marcador_cidades_processadas()
		{
			// Vetor com a marcacao das cidades que ja foram incluidas no menor caminho ou todas
			// as distancias foram encontradas
			bool *menor_distancia_encontrada = new bool[cidades.size()];

			for (unsigned int i = 0; i < cidades.size(); i++)
			{
				menor_distancia_encontrada[i] = false;
			}

			return menor_distancia_encontrada;
		}

		Caminho gera_menor_caminho_dijkstra(double distancias[])
		{
			Caminho menores_distancias;

			vector<Rota> rotas_menor_caminho;
			for (unsigned int index = 0; index < cidades.size(); index++)
			{
				Rota rota_atual = Rota(origem.get_id(),index, distancias[index]);
				rotas_menor_caminho.push_back(rota_atual);
			}

			Cidade origem_rota = cidades[rotas_menor_caminho.front().get_id_origem()];
			Cidade destino_rota = cidades[rotas_menor_caminho.back().get_id_destino()];
			menores_distancias = Caminho(origem_rota, destino_rota, rotas_menor_caminho);

			return menores_distancias;
		}

		// Funcao que implementa algoritmo de menor caminho de origem única do Dijkstra
		// para um grafo dado representado como matriz de adjacência
		Caminho Dijkstra::dijkstra_menor_caminho(std::vector<Caminho> distancias, Cidade origem_entrada, std::vector<Cidade> cidades_entrada)
		{
			// Se matriz de adjacencia for vazia, nao ha nada a fazer
			if (distancias.size() < 1)
				return Caminho();
			
			//Inicializa as variaveis globais
			cidades = cidades_entrada;
			origem = origem_entrada;

			// Vetor com as menores distancias encontradas a partir da origem pra todas as demais cidades
			double *distancias_encontradas = inicializa_distancias_encontradas();


			bool *marcador_distancia_encontrada = inicializa_marcador_cidades_processadas();

			// Distancia para a cidade de origem sempre e 0
			distancias_encontradas[origem.get_id()] = 0;

			// Acha menor caminho para todas as cidades
			for (unsigned int count = 0; count < distancias.size() - 1; count++)
			{
				// Pega a menor distancia para a cidade do conjunto de cidades ainda nao processados.
				// u e igual a origem na primeira iteracao
				int u = minima_distancia_partindo_da_origem(distancias_encontradas, marcador_distancia_encontrada);

				// Marca a cidade escolhida como processada
				marcador_distancia_encontrada[u] = true;

				// Atualiza o valor da distancia das cidades adjacentes a cidade escolhida nessa iteracao
				for (unsigned int v = 0; v < distancias.size(); v++)
				{
					// Atualiza distancias encontradas apenas se ela tiver marcada como 
					// como nao encontrada, se tiver um caminho da cidade u para v, e a distancia
					// da origem apara cidade v passando por u for menor que a menor distancia
					// atualmente setada em v

					double distancia_para_cidade_sendo_processada = distancias[u].get_trajeto()[v].get_distancia();

					double nova_distancia = distancias_encontradas[u] + distancia_para_cidade_sendo_processada;

					bool distancia_menor_encontrada = nova_distancia < distancias_encontradas[v];

					bool menor_distancia_nao_encontrada = !marcador_distancia_encontrada[v];

					if (menor_distancia_nao_encontrada && distancia_para_cidade_sendo_processada && distancias_encontradas[u] != max_distance
						&& distancia_menor_encontrada)
						distancias_encontradas[v] = nova_distancia;
				}
			}

			// Gera o caminho com as rotas encontradas
			Caminho menor_caminho = gera_menor_caminho_dijkstra(distancias_encontradas);

			// print the constructed distance array
			imprime_caminho_curto_dijkstra(menor_caminho);

			// Libera memoria de vetores alocados
			delete[] distancias_encontradas;
			delete[] marcador_distancia_encontrada;

			return menor_caminho;
		}
	} // algoritmos
} // rotas