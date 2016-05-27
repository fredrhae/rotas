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

			/**
			 * Localizas as cidades que são medianas considerando a distância entre as demais.
			 */
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
			lista_vertices_t vertices_para_analisar(const std::vector<Cidade>& cidades, const lista_medianas_t& medianas);

			/**
			 * Informa se todos os vértices foram analisados.
			 */
			bool todos_foram_analisados(const lista_vertices_t& vertices);

			/**
			 * Analisa se é uma mediana melhor. Retorna true se houve modificações no conjunto 'S'.
			 */
			bool analisa_vertice(vertice_t& vertice, lista_medianas_t& medianas, lista_vertices_t& para_analisar);

			/**
			 * Procura uma mediana em uma lista. Retorna -1 se não encontrar.
			 */
			int procura_mediana(const lista_medianas_t& medianas, const mediana_t& mediana);

			/**
			 * É soma das menores distâncias existentes entre uma cidade e todos as outras.
			 */
			static double soma_menores_distancias(const Cidade& cidade, const std::vector<Cidade>& cidades);

			/**
			 * Converte uma lista de vertices para uma lista de cidades;
			 */
			static std::vector<Cidade> vertices_para_cidades(const  lista_vertices_t& vertices);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_TEITZ_BART_H_

