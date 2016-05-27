#include "teitz_bart.h"

#include <ctime>

#include "dijkstra.h"

namespace rotas
{
	namespace algoritmos
	{
		std::vector<Cidade> TeitzBart::localiza_medianas(Context& context)
		{
			std::vector<Cidade> cidades = context.get_cidades_atendidas(); // Conjunto 'V'
			lista_medianas_t medianas = seleciona_medianas_aleatoriamente(cidades); // Conjunto 'S'
			lista_vertices_t para_analisar = vertices_para_analisar(cidades, medianas); // Conjunto { V - S }

			while (todos_foram_analisados(para_analisar) == false)
			{
				for (unsigned int i = 0; i < para_analisar.size(); i++)
				{
					vertice_t vertice = para_analisar.at(i);

					bool modificou = analisa_vertice(vertice, medianas, para_analisar, context);

					if (modificou == true)
					{
						para_analisar = vertices_para_analisar(cidades, medianas);
					}
				}
			}

			return medianas;
		}

		lista_medianas_t TeitzBart::seleciona_medianas_aleatoriamente(const std::vector<Cidade>& cidades)
		{
			srand((unsigned int)time(NULL));

			lista_medianas_t medianas;

			unsigned int tamanho = rand() % cidades.size();

			for (unsigned int i = 0; i < tamanho; i++)
			{
				unsigned int index = rand() % (cidades.size() - 1);

				medianas.push_back(cidades.at(index));
			}

			return medianas;
		}

		lista_vertices_t TeitzBart::vertices_para_analisar(const std::vector<Cidade>& cidades /* Conjunto 'V' */, const lista_medianas_t& medianas /* Conjunto 'S' */)
		{
			lista_vertices_t vertices;

			for (unsigned int i = 0; i < cidades.size(); i++)
			{
				Cidade cidade = cidades.at(i);

				if (procura_mediana(medianas, cidade) < 0)
				{
					//
					// Se a cidade não está presente nas medianas, deve ser analisada.

					vertices.push_back(vertice_t(cidade));
				}
			}

			return vertices;
		}

		bool TeitzBart::todos_foram_analisados(const lista_vertices_t& vertices)
		{
			for (unsigned int i = 0; i < vertices.size(); i++)
			{
				vertice_t v = vertices.at(i);

				if (v.analisado == false)
				{
					return false;
				}
			}

			return true;
		}

		bool TeitzBart::analisa_vertice(
			vertice_t& vertice, /* Vi */
			lista_medianas_t& medianas, /* Conjunto 'S' */
			lista_vertices_t& para_analisar, /* Conjunto { V - S } */
			Context& context)
		{
			double * reducoes = new double[medianas.size()];
			double maximo = 0; // Aij0

			for (unsigned int i = 0; i < medianas.size(); i++)
			{
				mediana_t vj = medianas.at(i);
				
				// Número de Transmissão (NT): é a soma das menores distâncias existentes entre o vértice Vj e todos os outros vértices
				// TODO: Aij = NT(S) - NT(S U { Vi } - { Vj })
				// TODO: CORRETO?
				reducoes[i] = TeitzBart::soma_menores_distancias(vertice.cidade, context) - TeitzBart::soma_menores_distancias(vj, context); 

				if (reducoes[i] > maximo)
				{
					// Faça Aij0 = Max[Aij];

					maximo = reducoes[i];
				}

				if (maximo > 0)
				{
					// Se Aij0 > 0 faça S = S U { Vi } - { Vj0 } e rotule Vj0 como "analisado";

					medianas.assign(i, vj); // TODO: CORRETO?

					return true; // Houve modificação no conjunto 'S'
				}
				else
				{
					// Se Aij0 <= 0, rotule Vi como "analisado"

					vertice.analisado = true;
				}
			}

			return false; // O conjunto 'S' NÃO foi modificado
		}

		int TeitzBart::procura_mediana(const lista_medianas_t& medianas, const mediana_t& mediana)
		{
			Cidade cidade_mediana = (Cidade)mediana;

			for (unsigned int i = 0; i < medianas.size(); i++)
			{
				Cidade c = medianas.at(i);

				if (cidade_mediana.get_id() == c.get_id() && (cidade_mediana.get_nome().compare(c.get_nome()) == 0))
				{
					return i;
				}
			}

			return -1;
		}

		double TeitzBart::soma_menores_distancias(Cidade& cidade, Context& context)
		{
			Dijkstra dijkstra;
			std::vector<Rota> rotas = dijkstra.dijkstra_menor_caminho(context, cidade);
			double soma = 0.0;

			for (unsigned int i = 0; i < rotas.size(); i++)
			{
				soma += rotas.at(i).get_distancia();
			}

			return soma;
		}

		std::vector<Cidade> TeitzBart::vertices_para_cidades(const  lista_vertices_t& vertices)
		{
			std::vector<Cidade> cidades;

			for (unsigned int i = 0; i < vertices.size(); i++)
			{
				cidades.push_back(vertices.at(i).cidade);
			}

			return cidades;
		}
	} // algoritmos
} // rotas
