#include "teitz_bart.h"

#include <algorithm>
#include <ctime>

#include "dijkstra.h"

namespace rotas
{
	namespace algoritmos
	{
		std::vector<Cidade> TeitzBart::localiza_medianas(Context& context)
		{
			lista_vertices_t todos_os_vertices /* { V } */ = TeitzBart::inicializa_vertices(context);

			//
			// Passo 1: Contruir um conjunto inicial 'S', com 'p' elementos de 'V'

			lista_vertices_t medianas /* { S } */ = seleciona_medianas_aleatoriamente(todos_os_vertices);

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
					// a) 'Vi' é um vértice "não-analisado. Calcular redução R do número de transmissão
					//	  para todo 'Vj' pertencente à { S }. Rij = NT(S) - NT(S u { Vi } - { Vj })

					// TODO TODO TODO

					//
					// b) Faça Rij0 = Max[Rij].

					// TODO TODO TODO

					//
					// c) Se Rij0 > 0, faça: S = S u { Vi } - { Vj0 } e rotule Vj0 como "analisado".

					// TODO TODO TODO

					//
					// d) Se Rij0 <= 0, rotule 'Vi' como "analisado".

					// TODO TODO TODO
				}

				//
				// Passo 4: Se durante a execução do passo 3 ocorrer modificações no conjunto S, volte para o passo 2.
				//          Caso contrário PARE. O conjunto { S } será uma aproximação para o problema das p-medianas.
			} while (
				existe_nao_analisados(todos_os_vertices) /* 'existe_nao_analisados()' pertence ao Passo 3 */ ||
				modificou == true /* 'modificou' pertence ao Passo 4 */);

			return vertices_para_cidades(medianas);
		}

		lista_vertices_t TeitzBart::seleciona_medianas_aleatoriamente(lista_vertices_t& vertices)
		{
			srand((unsigned int)time(NULL));

			lista_vertices_t medianas;

			unsigned int tamanho = rand() % vertices.size();

			for (unsigned int i = 0; i < tamanho; i++)
			{
				unsigned int index = rand() % (vertices.size() - 1);

				medianas.push_back(medianas[index]);
			}

			return medianas;
		}

		void TeitzBart::rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas)
		{
			for each (vertice_t vertice in todos_os_vertices)
			{
				if (TeitzBart::contem_vertice(medianas, vertice) == false)
				{
					vertice.analisado = false;
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
	} // algoritmos
} // rotas
