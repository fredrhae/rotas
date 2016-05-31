#ifndef ROTAS_ALGORITMOS_TEITZ_BART_H_
#define ROTAS_ALGORITMOS_TEITZ_BART_H_

#include <vector>
#include "domain/cidade.h"
#include "domain/context.h"

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

				vertice_t(domain::Cidade& c, bool a = true) : cidade(c), analisado(a) {}
			} vertice_t;

			typedef std::vector<vertice_t> lista_vertices_t;
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
			std::vector<Cidade> localiza_medianas(std::vector<Cidade> cidades, const unsigned int& p);
		
#ifndef GTEST
		private:
#endif // !GTEST
			/**
			 * Seleciona aleatoriamente um conjunto 'S', com tamanho 'p' (número de cidades utilizadas como medianas)
			 * para formar uma aproximação inicial para as p-medianas.
			 */
			lista_vertices_t seleciona_medianas_aleatoriamente(lista_vertices_t& vertices, const unsigned int& p);
			
			/**
			 * Rotula todos os vértices que não são medianas como "não-analisados".
			 */
			void rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas);

			/**
			 * Informa se existe vértices não analisados.
			 */
			bool existe_nao_analisados(lista_vertices_t& vertices);

			/**
			 * Inicializa uma lista de vértices.
			 */
			static lista_vertices_t inicializa_vertices(std::vector<Cidade>& cidades);

			/**
			 * Converte uma lista de vertices para uma lista de cidades;
			 */
			static std::vector<Cidade> vertices_para_cidades(const lista_vertices_t& vertices);

			/**
			 * Verifica se uma lista de vértice possui um vértice específico.
			 */
			static bool contem_vertice(const lista_vertices_t& vertices, vertice_t& vertice);

			/**
			 *Verifica se uma lista de vértice possui um id específico.
			 */
			static bool contem_id(const lista_vertices_t& vertices, const int& id);

			/**
			 * Calcula o número de transmissão (soma das menores distâncias) entre um vértice e todos os demais.
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& grafo);

			/**
			 *
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& vertices, vertice_t& adicionar, vertice_t& remover);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_TEITZ_BART_H_

