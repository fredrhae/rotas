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
			 */
			std::vector<Cidade> localiza_medianas(std::vector<Cidade> cidades, const unsigned int& p);
		
#ifndef GTEST
		private:
#endif // !GTEST
			/**
			 * Seleciona aleatoriamente um conjunto 'S', com tamanho 'p' (n�mero de cidades utilizadas como medianas)
			 * para formar uma aproxima��o inicial para as p-medianas.
			 */
			lista_vertices_t seleciona_medianas_aleatoriamente(lista_vertices_t& vertices, const unsigned int& p);
			
			/**
			 * Rotula todos os v�rtices que n�o s�o medianas como "n�o-analisados".
			 */
			void rotula_nao_analisados(lista_vertices_t& todos_os_vertices, lista_vertices_t& medianas);

			/**
			 * Informa se existe v�rtices n�o analisados.
			 */
			bool existe_nao_analisados(lista_vertices_t& vertices);

			/**
			 * Inicializa uma lista de v�rtices.
			 */
			static lista_vertices_t inicializa_vertices(std::vector<Cidade>& cidades);

			/**
			 * Converte uma lista de vertices para uma lista de cidades;
			 */
			static std::vector<Cidade> vertices_para_cidades(const lista_vertices_t& vertices);

			/**
			 * Verifica se uma lista de v�rtice possui um v�rtice espec�fico.
			 */
			static bool contem_vertice(const lista_vertices_t& vertices, vertice_t& vertice);

			/**
			 *Verifica se uma lista de v�rtice possui um id espec�fico.
			 */
			static bool contem_id(const lista_vertices_t& vertices, const int& id);

			/**
			 * Calcula o n�mero de transmiss�o (soma das menores dist�ncias) entre um v�rtice e todos os demais.
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

