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
			 * @param cidades referência para a lista de cidades com as menores rotas definidas
			 * @param p quantidade de cidades sedes
			 */
			void define_medianas(std::vector<Cidade>& cidades, const unsigned int& p);
		
#ifndef GTEST
		private:
#endif // !GTEST
			/**
			 * Seleciona aleatoriamente um conjunto 'S', com tamanho 'p' (número de cidades utilizadas como medianas)
			 * para formar uma aproximação inicial para as p-medianas.
			 * @param vertices todos os vértices (cidades)
			 * @param p quantidade de medianas para sortear
			 * @return lista de vértices sorteados
			 */
			lista_vertices_t seleciona_medianas_aleatoriamente(lista_vertices_t& vertices, const unsigned int& p);
			
			/**
			 * Rotula todos os vértices que não são medianas como "não-analisados".
			 * @param todos_os_vertices todos os vértices (cidades)
			 * @param medianas vértices que são medianas
			 */
			void rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas);

			/**
			 * Informa se existe vértices não analisados.
			 * @param vertices lista de vértices
			 * @return true se existem vértices não analisados
			 */
			bool existe_nao_analisados(lista_vertices_t& vertices);

			/**
			 * Inicializa uma lista de vértices.
			 * @param cidades lista de cidades com as menores rotas já definidas
			 * @return lista de vértices inicializados todos como "não-analisados"
			 */
			static lista_vertices_t inicializa_vertices(std::vector<Cidade>& cidades);

			/**
			 * Verifica se uma lista de vértice possui um vértice específico.
			 * @param vertices lista de vértices
			 * @param vertice vértice para procurar
			 * @return true se o vértice está presente na lista
			 */
			static bool contem_vertice(lista_vertices_t& vertices, vertice_t& vertice);

			/**
			 * Verifica se uma lista de vértice possui um id específico.
			 * @param vertices lista de vértices
			 * @param id id da cidade para procurar
			 * @return true se a cidade está presente na lista de vértices
			 */
			static bool contem_id(lista_vertices_t& vertices, const int& id);

			/**
			 * Calcula o número de transmissão (soma das menores distâncias) entre um vértice e todos os demais.
			 * @param vertice vertice de origem
			 * @param grafo gravo de vértices com todas as rotas disponíveis
			 * @return soma das menores distâncias do vertice até os outros vértices presentes no grafo
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& grafo);

			/**
			 * Calcula o número de transmissão (soma das menores distâncias) entre um vértice e todos os demais.
			 * @param vertice vertice de origem
			 * @param grafo gravo de vértices com todas as rotas disponíveis
			 * @param adicionar vértice para adicionar ao grafo
			 * @param remover vértice para remover do grafo
			 * @return soma das menores distâncias do vertice até os outros vértices presentes no grafo
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& grafo, vertice_t& adicionar, vertice_t& remover);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_TEITZ_BART_H_

