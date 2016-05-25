#include "teitz_bart.h"

namespace rotas
{
	namespace algoritmos
	{
		std::vector<Cidade> TeitzBart::localiza_medianas(const std::vector<Cidade>& cidades)
		{
			lista_medianas_t medianas = seleciona_medianas_aleatoriamente(cidades); // conjunto 'S'
			lista_vertices_t para_analisar = vertices_para_analisar(cidades, medianas); // { V - S }

			while (todos_foram_analisados(para_analisar) == false)
			{
				for (unsigned int i = 0; i < para_analisar.size(); i++)
				{
					vertice_t vertice = para_analisar.at(i);

					bool modificou = analisa_vertice(vertice, medianas);

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
			// TODO

			return lista_medianas_t();
		}

		lista_vertices_t TeitzBart::vertices_para_analisar(const std::vector<Cidade>& cidades, const lista_medianas_t& medianas)
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

		bool TeitzBart::analisa_vertice(vertice_t& vertice, lista_medianas_t& medianas)
		{
			// TODO

			return false;
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
	} // algoritmos
} // rotas
