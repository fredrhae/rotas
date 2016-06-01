#include "algoritmos/clarke_wright.h"
#include "algoritmos/gillet_johnson.h"
#include "domain/rota.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace rotas::algoritmos;

namespace rotas {
	namespace algoritmos {

		static vector<Cidade> cidades_entrada;
		static vector<vector<Rota>> todos_savings;

		vector<Cidade> encontra_pontos_demandas(Cidade facilidade)
		{
			vector<Cidade> pontos_demanda = vector<Cidade>();
			for (unsigned int i = 0; i < cidades_entrada.size(); i++) {
				if (!cidades_entrada[i].is_mediana() &&
					cidades_entrada[i].get_id_mediana() == facilidade.get_id()) {
					pontos_demanda.push_back(cidades_entrada[i]);
				}
			}

			return pontos_demanda;
		}

		vector<Cidade> encontra_facilidades()
		{
			vector<Cidade> facilidades = vector<Cidade>();
			for (unsigned int i = 0; i < cidades_entrada.size(); i++) {
				if (cidades_entrada[i].is_mediana()) {
					facilidades.push_back(cidades_entrada[i]);
				}
			}

			return facilidades;
		}

		bool compara_rotas(Rota rota_a, Rota rota_b)
		{
			return rota_a.get_distancia() > rota_b.get_distancia();
		}

		void ordena_maior_pro_menor(vector<Rota> &savings)
		{
			sort(savings.begin(), savings.end(), compara_rotas);
		}

		vector<Rota> inicializa_savings(Cidade facilidade)
		{
			vector<Cidade> pontos_demanda = encontra_pontos_demandas(facilidade);

			vector<Rota> savings = vector<Rota>();

			ClarkeWright clarke = ClarkeWright();

			for (unsigned int i = 0; i < pontos_demanda.size(); i++)
			{
				int id_cidade_origem_atual = pontos_demanda[i].get_id();
				for (unsigned int j = i; j < pontos_demanda.size(); j++)
				{
					if (i != j)
					{	
						int id_cidade_destino = pontos_demanda[j].get_id();
						double distancia_origem_facilidade = cidades_entrada[id_cidade_origem_atual].get_distancia(facilidade);
						double distancia_facilidade_destino = facilidade.get_distancia(cidades_entrada[id_cidade_destino]);
						double distancia_origem_destino = cidades_entrada[id_cidade_origem_atual].get_distancia(cidades_entrada[id_cidade_destino]);
						double distancia_saving_atual = distancia_origem_facilidade + distancia_facilidade_destino - distancia_origem_destino;

						savings.push_back(Rota(id_cidade_origem_atual,id_cidade_destino,distancia_saving_atual));
					}
				}
			}

			return savings;
		}

		bool saving_e_valido(Rota rota_saving)
		{
			if(rota_saving.get_distancia() < 0)
				return false;
			return true;
		}

		void adiciona_saving_na_rota(Rota saving, vector<Rota> &rota_encontradas)
		{

		}

		void incrementa_demandas_cobertas(vector<Rota> &rota_encontrada, int *contador_atual)
		{

		}

		vector<Rota> encontra_rota_partindo_dos_savings(vector<Rota> &savings_atual, Cidade facilidade)
		{
			vector<Rota> melhor_rota_encontrada = vector<Rota>();

			size_t total_demandas = encontra_pontos_demandas(facilidade).size();

			Cidade destino = cidades_entrada[savings_atual[0].get_id_origem()];
			
			// Adiciona a rota da origem pra primeira cidade do saving
			melhor_rota_encontrada.push_back(Rota(facilidade.get_id(),destino.get_id(),facilidade.get_distancia(destino)));
			
			int demandas_cobertas = 1;
			
			for (unsigned int i = 0; demandas_cobertas < total_demandas || i < savings_atual.size(); i++)
			{
				if (saving_e_valido(savings_atual[i]))
				{
					//adiciona_saving_na_rota(savings_atual[i], melhor_rota_encontrada);
					//incrementa_demandas_cobertas(melhor_rota_encontrada, demandas_cobertas);
				}
			}

			// Adiciona a rota da ultima cidade de destino retornando pra facilidade
			Cidade ultima_cidade_demanda = cidades_entrada[melhor_rota_encontrada.back().get_id_destino()];
			melhor_rota_encontrada.push_back(Rota(ultima_cidade_demanda.get_id(), facilidade.get_id(), ultima_cidade_demanda.get_distancia(facilidade)));
		}

		vector<vector<Rota>> ClarkeWright::encontra_roteamentos(std::vector<Cidade> & cidades)
		{
			cidades_entrada = cidades;

			vector<Cidade> facilidades = encontra_facilidades();
			
			vector<vector<Rota>> melhores_rotas_encontradas = vector<vector<Rota>>();

			todos_savings = vector<vector<Rota>>();

			for (unsigned int i = 0; i < facilidades.size(); i++)
			{
				vector<Rota> saving_atual = inicializa_savings(facilidades[i]);
				
				ordena_maior_pro_menor(saving_atual);

				todos_savings.push_back(saving_atual);
			}

			//for (unsigned int i = 0; i < todos_savings.size(); i ++)
			//{
			//	vector<Rota> melhor_rota_atual = vector<Rota>();

			//	melhor_rota_atual = encontra_rota_partindo_dos_savings(todos_savings[i], facilidades[i]);
			//	
			//	melhores_rotas_encontradas.push_back(melhor_rota_atual);
			//}

			return todos_savings;
		}
	}
}