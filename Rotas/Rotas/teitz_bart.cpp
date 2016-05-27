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

					bool modificou = analisa_vertice(vertice, medianas, para_analisar);

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
					// Se a cidade n�o est� presente nas medianas, deve ser analisada.

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
			vertice_t& vertice /* Vi */,
			lista_medianas_t& medianas /* Conjunto 'S' */,
			lista_vertices_t& para_analisar /* Conjunto { V - S } */)
		{
			// TODO

			/// (a) selecione um v�rtice 'Vi' pertencente a { V - S }, "n�o analisado", 
			///		e calcule a redu��o A do n�mero de transmiss�o, para todo 'Vj'
			///		pertencente a 'S': Aij = NT(S) - NT(S U{ Vi } -{Vj})
			/// (b) fa�a Aij0 = Max[Aij];
			/// (c) se Aij0 > 0 fa�a S = S U{ Vi } -{Vj0} e rotule Vj0 como "analisado";
			/// (d) se Aij0 <= 0, rotule Vi como "analisado"

			double * reducoes = new double[medianas.size()];
			double maximo = 0; // Aij0

			for (unsigned int i = 0; i < medianas.size(); i++)
			{
				mediana_t vj = medianas.at(i);
				/// N�mero de Transmiss�o (NT): � a soma das menores dist�ncias existentes entre o v�rtice Vj e todos os outros v�rtices
				/// TODO: Aij = NT(S) - NT(S U { Vi } - { Vj })
				//reducoes[i] = TeitzBart::soma_menores_distancias(vertice.cidade, medianas) - TeitzBart::soma_menores_distancias(cidade, ); 

				if (reducoes[i] > maximo)
				{
					// Fa�a Aij0 = Max[Aij];

					maximo = reducoes[i];
				}

				if (maximo > 0)
				{
					// Se Aij0 > 0 fa�a S = S U { Vi } - { Vj0 } e rotule Vj0 como "analisado";

					return true; // Houve modifica��o no conjunto 'S'
				}
				else
				{
					// Se Aij0 <= 0, rotule Vi como "analisado"

					vertice.analisado = true;
				}
			}

			return false; // O conjunto 'S' N�O foi modificado
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

		double TeitzBart::soma_menores_distancias(const Cidade& cidade, const std::vector<Cidade>& cidades)
		{
			// TODO

			return 0.0;
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
