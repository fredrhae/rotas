#include "teitz_bart.h"

#include <algorithm>
#include <ctime>
#include <iostream>

#include "dijkstra.h"

namespace rotas
{
	namespace algoritmos
	{
		std::vector<Cidade> TeitzBart::localiza_medianas(Context& context, const unsigned int& p)
		{
			lista_vertices_t todos_os_vertices /* { V } */ = TeitzBart::inicializa_vertices(context);

			//
			// Passo 1: Contruir um conjunto inicial 'S', com 'p' elementos de 'V'

			lista_vertices_t medianas /* { S } */ = seleciona_medianas_aleatoriamente(todos_os_vertices, p);

			bool modificou;

			do
			{
				//
				// Passo 2: Rotular todos os pontos 'Vi' não pertencentes à { S } como "não-analisados"

				rotula_nao_analisados(todos_os_vertices, medianas);

				//
				// Passo 3: Enquanto existirem pontos "não-analisados" no conjunto { V - S }, faça:

				modificou = false;

				for (size_t i = 0; i < todos_os_vertices.size(); i++)
				{
					vertice_t Vi = todos_os_vertices[i];

					if (Vi.analisado == true)
					{
						continue;
					}

					//
					// a) 'Vi' é um vértice "não-analisado". Calcular redução 'R' do número de transmissão
					//	  para todo 'Vj' pertencente à { S }. Rij = NT(S) - NT(S u { Vi } - { Vj })

					double ntS = calcula_numero_transmissao(Vi, context);
					double * reducoes = new double[medianas.size()];
					int VjCidade_id = -1;
					int VjMax_index = -1;
					double max = std::numeric_limits<double>::min();

					for (size_t j = 0; j < medianas.size(); j++)
					{
						vertice_t Vj = medianas[j];

						reducoes[j] = ntS - calcula_numero_transmissao(Vj, context, Vi, Vj);

						if (reducoes[j] > max)
						{
							//
							// b) Faça Rij0 = Max[Rij].

							VjCidade_id = Vj.cidade.get_id();
							VjMax_index = j;
							max = reducoes[j];
						}
					}

					if (VjMax_index > 0 && max > 0)
					{
						//
						// c) Se Rij0 > 0, faça: S = S u { Vi } - { Vj0 } e rotule Vj0 como "analisado".

						// Remove Vj0
						medianas.erase(medianas.begin() + VjMax_index);
						
						// Adiciona Vi
						medianas.push_back(Vi);

						// Rotula Vj0 como "analisado"
						for (size_t aux = 0; aux < todos_os_vertices.size(); aux++)
						{
							vertice_t v = todos_os_vertices[aux];

							if (v.cidade.get_id() == VjCidade_id)
							{
								v.analisado = true;
								break;
							}
						}

						modificou = true;
					}
					else
					{
						//
						// d) Se Rij0 <= 0, rotule 'Vi' como "analisado".

						Vi.analisado = true;
					}
				}

				//
				// Passo 4: Se durante a execução do passo 3 ocorrer modificações no conjunto S, volte para o passo 2.
				//          Caso contrário PARE. O conjunto { S } será uma aproximação para o problema das p-medianas.
			} while (
				existe_nao_analisados(todos_os_vertices) /* 'existe_nao_analisados()' pertence ao Passo 3 */ ||
				modificou == true /* 'modificou' pertence ao Passo 4 */);

			return vertices_para_cidades(medianas);
		}

		lista_vertices_t TeitzBart::seleciona_medianas_aleatoriamente(lista_vertices_t& vertices, const unsigned int& p)
		{
			srand((unsigned int)time(NULL));

			lista_vertices_t medianas;

			for (unsigned int i = 0; i < p; i++)
			{
				unsigned int index = rand() % vertices.size();

				vertice_t& vertice = vertices[index];

				if (TeitzBart::contem_vertice(medianas, vertice) == true)
				{
					i--;
					continue;
				}

				medianas.push_back(vertice);
			}

			return medianas;
		}

		void TeitzBart::rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas)
		{
			for (size_t i = 0; i < todos_os_vertices.size(); i++)
			{
				vertice_t& vertice = todos_os_vertices[i];

				if (TeitzBart::contem_vertice(medianas, vertice) == false)
				{
					vertice.analisado = false;
				}
				else
				{
					vertice.analisado = true;
				}
			}
		}

		bool TeitzBart::existe_nao_analisados(lista_vertices_t& vertices)
		{
			for (size_t i = 0; i < vertices.size(); i++)
			{
				if (vertices[i].analisado == false)
				{
					return true;
				}
			}

			return false;
		}

		lista_vertices_t TeitzBart::inicializa_vertices(Context& context)
		{
			std::vector<Cidade> cidades = context.get_cidades_atendidas();
			lista_vertices_t vertices;

			for (size_t i = 0; i < cidades.size(); i++)
			{
				vertices.push_back(vertice_t(cidades.at(i)));
			}

			return vertices;
		}

		std::vector<Cidade> TeitzBart::vertices_para_cidades(const  lista_vertices_t& vertices)
		{
			std::vector<Cidade> cidades;

			for (unsigned int i = 0; i < vertices.size(); i++)
			{
				cidades.push_back(vertices[i].cidade);
			}

			return cidades;
		}

		bool TeitzBart::contem_vertice(const lista_vertices_t& vertices, vertice_t& vertice)
		{
			for each (vertice_t v in vertices)
			{
				if (v.cidade.get_id() == vertice.cidade.get_id())
				{
					return true;
				}
			}

			return false;
		}

		double TeitzBart::calcula_numero_transmissao(vertice_t& vertice, Context& context)
		{
			Dijkstra dijkstra;
			std::vector<Rota> rotas = dijkstra.dijkstra_menor_caminho(context, vertice.cidade);
			double soma = 0.0;

			for (unsigned int i = 0; i < rotas.size(); i++)
			{
				soma += rotas.at(i).get_distancia();
			}

			return soma;
		}

		double TeitzBart::calcula_numero_transmissao(vertice_t& vertice, Context& context, vertice_t& adicionar, vertice_t& remover)
		{
			std::vector<std::vector<Rota>> matriz_distancias = context.get_matriz_distancias();
			std::vector<Cidade> cidades_atendidas = context.get_cidades_atendidas();

			int index = -1;

			for (size_t i = 0; i < cidades_atendidas.size(); i++)
			{
				if (cidades_atendidas[i].get_id() == remover.cidade.get_id())
				{
					index = i;
					break;
				}
			}

			if (index >= 0)
			{
				cidades_atendidas.erase(cidades_atendidas.begin() + index);
				cidades_atendidas.push_back(adicionar.cidade);
			}
			else
			{
				return 0.0;
			}

			Context copia(cidades_atendidas, matriz_distancias);

			return calcula_numero_transmissao(vertice, copia);
		}
	} // algoritmos
} // rotas
