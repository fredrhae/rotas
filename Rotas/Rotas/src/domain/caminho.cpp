#include "caminho.h"

namespace rotas 
{
	namespace domain 
	{
		int Caminho::get_id_origem()
		{
			return trajeto.front().get_id_origem();
		}

		int Caminho::get_id_destino()
		{
			return trajeto.back().get_id_destino();
		}

		std::vector<Rota> Caminho::get_trajeto()
		{
			return trajeto;
		}
		
		double Caminho::get_distancia()
		{
			double distancia_total = 0;
			for (unsigned int i = 0; i < trajeto.size(); i++)
			{
				distancia_total += trajeto[i].get_distancia();
			}
			return distancia_total;
		}

		size_t Caminho::quantidade_rotas_trajeto()
		{
			return trajeto.size();
		}

		Rota Caminho::get_rota_indice(int index)
		{
			return trajeto.at(index);
		}

		void Caminho::adiciona_rota_fim_trajeto(int id_cidade_origem, int id_cidade_destino, double distancia)
		{
			trajeto.push_back(Rota(id_cidade_origem, id_cidade_destino, distancia));
		}

		void Caminho::adiciona_rota_comeco_trajeto(int id_cidade_origem, int id_cidade_destino, double distancia)
		{
			trajeto.insert(trajeto.begin(),Rota(id_cidade_origem, id_cidade_destino, distancia));
		}

		void Caminho::adiciona_rota_fim_trajeto(Rota rota)
		{
			trajeto.push_back(rota);
		}

		void Caminho::adiciona_rota_comeco_trajeto(Rota rota)
		{
			trajeto.insert(trajeto.begin(),rota);
		}

		void Caminho::apaga_rota_comeco()
		{
			trajeto.erase(trajeto.begin());
		}

		void Caminho::apaga_rota_fim()
		{
			trajeto.pop_back();
		}

		bool Caminho::cidade_existe_na_rota(int id_cidade)
		{
			for each(Rota rota_atual in trajeto)
			{
				if (rota_atual.rota_contem_cidade(id_cidade))
					return true;
			}
			return false;
		}

		bool Caminho::cidade_no_fim_excluindo_facilidade(int id_cidade)
		{
			if (trajeto.rbegin()[1].get_id_destino() == id_cidade)
				return true;
			return false;
		}

		bool Caminho::cidade_no_comeco_excluindo_facilidade(int id_cidade)
		{
			if (trajeto.begin()[1].get_id_origem() == id_cidade)
				return true;
			return false;
		}

		bool Caminho::cidade_esta_no_fim_ou_comeco_rota(int id_cidade)
		{
			return cidade_no_fim_excluindo_facilidade(id_cidade) || 
				cidade_no_comeco_excluindo_facilidade(id_cidade);
		}
	} // domain
} // rotas