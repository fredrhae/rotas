#ifndef ROTAS_ALGORITMOS_TEITZ_BART_H_
#define ROTAS_ALGORITMOS_TEITZ_BART_H_

#include <vector>
#include "domain/caminho.h"
#include "domain/cidade.h"

namespace rotas
{
	namespace algoritmos
	{
		namespace teitz_bart
		{
			typedef struct vertice_t
			{
				domain::Cidade cidade;
				bool analisado;

				vertice_t() : analisado(false) {}
				vertice_t(const domain::Cidade& c, bool a = false) : cidade(c), analisado(a) {}
			} vertice_t;

			typedef std::vector<vertice_t> lista_vertices_t;

			typedef domain::Cidade mediana_t;

			typedef std::vector<mediana_t> lista_medianas_t;
		}

		using namespace domain;
		using namespace teitz_bart;

		class TeitzBart
		{
		public:
			inline TeitzBart() { }
			inline ~TeitzBart() { }

			std::vector<Cidade> localiza_medianas(const std::vector<Cidade>& cidades);

		private:

			/**
			 * Seleciona aleatoriamente um conjunto 'S', com tamanho 'p' (número de cidades utilizadas como medianas)
			 * para formar uma aproximação inicial para as p-medianas.
			 */
			lista_medianas_t seleciona_medianas_aleatoriamente(const std::vector<Cidade>& cidades);

			/**
			 * Recupera a lista de vértices para serem analisadas pelo algoritmo.
			 */
			lista_vertices_t vertices_para_analisar(const lista_medianas_t& medianas);

			/**
			 * Informa se todos os vértices foram analisados.
			 */
			bool todos_foram_analisados(const lista_vertices_t& vertices);

			/**
			 * Analisa se é uma mediana melhor. Retorna true se houve modificações no conjunto 'S'.
			 */
			bool analisa_vertice(vertice_t& vertice, lista_medianas_t& medianas);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_TEITZ_BART_H_

