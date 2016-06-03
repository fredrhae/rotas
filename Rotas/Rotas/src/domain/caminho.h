#ifndef ROTAS_DOMAIN_PATH_H_
#define ROTAS_DOMAIN_PATH_H_

#include <vector>
#include "domain/cidade.h"
#include "domain/context.h"

namespace rotas
{
	namespace domain 
	{
		class Caminho 
		{
			int id_cidade_origem;
			int id_cidade_destino;
			std::vector<Rota> trajeto;
		public:
			Caminho() {};
			Caminho(int origem, int destino, std::vector<Rota> trajeto) 
					: id_cidade_origem(origem), id_cidade_destino(destino), trajeto(trajeto) {};
			int get_id_origem();
			int get_id_destino();
			std::vector<Rota> get_trajeto();
			double get_distancia();
			size_t Caminho::quantidade_rotas_trajeto();
			Rota Caminho::get_rota_indice(int index);
			bool cidade_no_fim_excluindo_facilidade(int id_cidade);
			bool cidade_no_comeco_excluindo_facilidade(int id_cidade);
			bool cidade_esta_no_fim_ou_comeco_rota(int id_cidade);
			bool cidade_existe_na_rota(int id_cidade);
			void adiciona_rota_fim_trajeto(int id_cidade_origem, int id_cidade_destino, double distancia);
			void adiciona_rota_fim_trajeto(Rota rota);
			void adiciona_rota_comeco_trajeto(int id_cidade_origem, int id_cidade_destino, double distancia);
			void adiciona_rota_comeco_trajeto(Rota rota);
			void apaga_rota_comeco();
			void apaga_rota_fim();
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_PATH_H_
