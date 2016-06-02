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
			 * Localizas as cidades que s�o medianas considerando a dist�ncia entre as demais.
			 * @param cidades refer�ncia para a lista de cidades com as menores rotas definidas
			 * @param p quantidade de cidades sedes
			 */
			void define_medianas(std::vector<Cidade>& cidades, const unsigned int& p);
		
#ifndef GTEST
		private:
#endif // !GTEST
			/**
			 * Seleciona aleatoriamente um conjunto 'S', com tamanho 'p' (n�mero de cidades utilizadas como medianas)
			 * para formar uma aproxima��o inicial para as p-medianas.
			 * @param vertices todos os v�rtices (cidades)
			 * @param p quantidade de medianas para sortear
			 * @return lista de v�rtices sorteados
			 */
			lista_vertices_t seleciona_medianas_aleatoriamente(lista_vertices_t& vertices, const unsigned int& p);
			
			/**
			 * Rotula todos os v�rtices que n�o s�o medianas como "n�o-analisados".
			 * @param todos_os_vertices todos os v�rtices (cidades)
			 * @param medianas v�rtices que s�o medianas
			 */
			void rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas);

			/**
			 * Informa se existe v�rtices n�o analisados.
			 * @param vertices lista de v�rtices
			 * @return true se existem v�rtices n�o analisados
			 */
			bool existe_nao_analisados(lista_vertices_t& vertices);

			/**
			 * Inicializa uma lista de v�rtices.
			 * @param cidades lista de cidades com as menores rotas j� definidas
			 * @return lista de v�rtices inicializados todos como "n�o-analisados"
			 */
			static lista_vertices_t inicializa_vertices(std::vector<Cidade>& cidades);

			/**
			 * Verifica se uma lista de v�rtice possui um v�rtice espec�fico.
			 * @param vertices lista de v�rtices
			 * @param vertice v�rtice para procurar
			 * @return true se o v�rtice est� presente na lista
			 */
			static bool contem_vertice(lista_vertices_t& vertices, vertice_t& vertice);

			/**
			 * Verifica se uma lista de v�rtice possui um id espec�fico.
			 * @param vertices lista de v�rtices
			 * @param id id da cidade para procurar
			 * @return true se a cidade est� presente na lista de v�rtices
			 */
			static bool contem_id(lista_vertices_t& vertices, const int& id);

			/**
			 * Calcula o n�mero de transmiss�o (soma das menores dist�ncias) entre um v�rtice e todos os demais.
			 * @param vertice vertice de origem
			 * @param grafo gravo de v�rtices com todas as rotas dispon�veis
			 * @return soma das menores dist�ncias do vertice at� os outros v�rtices presentes no grafo
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& grafo);

			/**
			 * Calcula o n�mero de transmiss�o (soma das menores dist�ncias) entre um v�rtice e todos os demais.
			 * @param vertice vertice de origem
			 * @param grafo gravo de v�rtices com todas as rotas dispon�veis
			 * @param adicionar v�rtice para adicionar ao grafo
			 * @param remover v�rtice para remover do grafo
			 * @return soma das menores dist�ncias do vertice at� os outros v�rtices presentes no grafo
			 */
			static double calcula_numero_transmissao(vertice_t& vertice, lista_vertices_t& grafo, vertice_t& adicionar, vertice_t& remover);
		};
	} // algoritmos
} // rotas

#endif // ROTAS_ALGORITMOS_TEITZ_BART_H_

