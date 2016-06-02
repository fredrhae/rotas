#include "algoritmos/clarke_wright.h"
#include "algoritmos/gillet_johnson.h"
#include "domain/rota.h"
#include <vector>
#include <algorithm>
#include <set>

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

		bool cidade_existe_na_rota(int id_cidade, vector<Rota> rotas_encontradas)
		{
			for each(Rota rota_atual in rotas_encontradas)
			{
				if(rota_atual.rota_contem_cidade(id_cidade))
					return true;
			}
			return false;
		}

		bool cidade_no_fim(int id_cidade, vector<Rota> rota)
		{
			if (rota.rbegin()[1].get_id_destino() == id_cidade)
				return true;
			return false;
		}

		bool cidade_no_comeco(int id_cidade, vector<Rota> rota)
		{
			if (rota.begin()[1].get_id_origem() == id_cidade)
				return true;
			return false;
		}

		bool cidade_esta_no_fim_ou_comeco_rota(int id_cidade, vector<Rota> rota)
		{
			return cidade_no_fim(id_cidade,rota) || cidade_no_comeco(id_cidade,rota);
		}

		int acha_rota_com_cidade(int id_cidade, vector<vector<Rota>> &rotas)
		{
			for (unsigned int i = 0; i < rotas.size(); i++)
			{
				if(cidade_existe_na_rota(id_cidade,rotas[i]))
					return i;
			}
			return -1;
		}

		void adiciona_rota_fim(int id_cidade_origem,int id_cidade_destino, vector<Rota> &rotas_encontradas)
		{
			Cidade origem = cidades_entrada[id_cidade_origem];
			Cidade destino = cidades_entrada[id_cidade_destino];

			rotas_encontradas.push_back(Rota(id_cidade_origem, id_cidade_destino, origem.get_distancia(destino)));
		}

		void adiciona_rota_comeco(int id_cidade_origem, int id_cidade_destino, vector<Rota> &rotas_encontradas)
		{
			Cidade origem = cidades_entrada[id_cidade_origem];
			Cidade destino = cidades_entrada[id_cidade_destino];

			rotas_encontradas.insert(rotas_encontradas.begin(),
									Rota(id_cidade_origem, id_cidade_destino, origem.get_distancia(destino)));
		}

		void adiciona_saving_na_rota(Rota saving, vector<vector<Rota>> &rotas_encontradas)
		{
			int index_ciclo_origem = acha_rota_com_cidade(saving.get_id_origem(),rotas_encontradas);
			int index_ciclo_destino = acha_rota_com_cidade(saving.get_id_destino(), rotas_encontradas);

			bool pertence_rotas_diferentes = false;
			bool origem_esta_apta_ser_adicionada = false;
			bool destino_esta_apto_ser_adicionado = false;

			if(index_ciclo_origem > -1)
			{
				pertence_rotas_diferentes = !cidade_existe_na_rota(saving.get_id_destino(),rotas_encontradas[index_ciclo_origem]);
				origem_esta_apta_ser_adicionada = cidade_esta_no_fim_ou_comeco_rota(saving.get_id_origem(), rotas_encontradas[index_ciclo_origem]);
			}
			if (index_ciclo_destino > -1)
			{
				destino_esta_apto_ser_adicionado = cidade_esta_no_fim_ou_comeco_rota(saving.get_id_destino(), rotas_encontradas[index_ciclo_destino]);
			}

			// TODO: colocar checagem de exceder capacidade do veiculo aqui
			
			if (pertence_rotas_diferentes && origem_esta_apta_ser_adicionada && destino_esta_apto_ser_adicionado)
			{
				int index_ciclo_join, index_ciclo_removido, id_origem, id_destino;
				bool dois_ciclos_comeco = false;
				bool dois_ciclos_fim = false;
				if (cidade_no_fim(saving.get_id_origem(), rotas_encontradas[index_ciclo_origem]) && 
					cidade_no_comeco(saving.get_id_destino(),rotas_encontradas[index_ciclo_destino]))
				{
					index_ciclo_join = index_ciclo_origem;
					index_ciclo_removido = index_ciclo_destino;
					id_origem = saving.get_id_origem();
					id_destino = saving.get_id_destino();
				}
				else if (cidade_no_comeco(saving.get_id_origem(), rotas_encontradas[index_ciclo_origem]) &&
					cidade_no_fim(saving.get_id_destino(), rotas_encontradas[index_ciclo_destino])) {
					index_ciclo_join = index_ciclo_destino;
					index_ciclo_removido = index_ciclo_origem;
					id_origem = saving.get_id_destino();
					id_destino = saving.get_id_origem();
				}
				else if (cidade_no_comeco(saving.get_id_origem(), rotas_encontradas[index_ciclo_origem]) &&
					cidade_no_comeco(saving.get_id_destino(), rotas_encontradas[index_ciclo_destino])) {
					dois_ciclos_comeco = true;
					index_ciclo_join = index_ciclo_origem;
					index_ciclo_removido = index_ciclo_destino;
					id_origem = saving.get_id_destino(); 
					id_destino = saving.get_id_origem();
				}
				else {
					dois_ciclos_fim = true;
					index_ciclo_join = index_ciclo_origem;
					index_ciclo_removido = index_ciclo_destino;
					id_origem = saving.get_id_origem(); 
					id_destino = saving.get_id_destino();
				}
		
				if (dois_ciclos_comeco)
				{
					// Remove a ultima rota e a primeira dos ciclos
					rotas_encontradas[index_ciclo_join].erase(rotas_encontradas[index_ciclo_join].begin());
					rotas_encontradas[index_ciclo_removido].erase(rotas_encontradas[index_ciclo_removido].begin());

					// Adiciona a rota do saving ao ciclo que recebera o join
					adiciona_rota_comeco(id_origem, id_destino, rotas_encontradas[index_ciclo_join]);
				}
				else if (dois_ciclos_fim)
				{
					// Remove a ultima rota e a primeira dos ciclos
					rotas_encontradas[index_ciclo_join].pop_back();
					rotas_encontradas[index_ciclo_removido].pop_back();

					// Adiciona a rota do saving ao ciclo que recebera o join
					adiciona_rota_fim(id_origem, id_destino, rotas_encontradas[index_ciclo_join]);
				}
				else
				{
					// Remove a ultima rota e a primeira dos ciclos
					rotas_encontradas[index_ciclo_join].pop_back();
					rotas_encontradas[index_ciclo_removido].erase(rotas_encontradas[index_ciclo_removido].begin());

					// Adiciona a rota do saving ao ciclo que recebera o join
					adiciona_rota_fim(id_origem, id_destino, rotas_encontradas[index_ciclo_join]);

					// Adiciona as rotas que estavam no ciclo que sera removido da lista
					for (unsigned int i = 0; i < rotas_encontradas[index_ciclo_removido].size(); i++)
					{
						rotas_encontradas[index_ciclo_join].push_back(rotas_encontradas[index_ciclo_removido][i]);
					}
				}


				if (dois_ciclos_comeco || dois_ciclos_fim)
				{
					// Adiciona as rotas que estavam no ciclo que sera removido da lista
					for (unsigned int i = 0; i < rotas_encontradas[index_ciclo_removido].size(); i++)
					{
						Rota rota_atual = rotas_encontradas[index_ciclo_removido][i];
						// Adiciona a rota do saving ao ciclo que recebera o join
						adiciona_rota_comeco(rota_atual.get_id_destino(), rota_atual.get_id_origem(), rotas_encontradas[index_ciclo_join]);

					}
				}
				
				// Apaga o ciclo de rota que foi incorporado
				rotas_encontradas.erase(rotas_encontradas.begin() + index_ciclo_removido);
				
			}
		}

		void inicializa_rotas_demandas(vector<vector<Rota>> &rotas_demandas, Cidade facilidade)
		{
			vector<Cidade> demandas = encontra_pontos_demandas(facilidade);

			rotas_demandas = vector<vector<Rota>>(demandas.size(), vector<Rota>());

			for (unsigned int i = 0; i < demandas.size(); i++)
			{
				adiciona_rota_fim(facilidade.get_id(),demandas[i].get_id(), rotas_demandas[i]);
				adiciona_rota_fim(demandas[i].get_id(),facilidade.get_id(), rotas_demandas[i]);
			}
		}

		vector<vector<Rota>> encontra_rota_partindo_dos_savings(vector<Rota> &savings_atual, Cidade facilidade)
		{
			vector<vector<Rota>> melhores_rotas_encontradas;

			
			inicializa_rotas_demandas(melhores_rotas_encontradas,facilidade);
			
			for (unsigned int i = 0;  i < savings_atual.size(); i++)
			{
				if (saving_e_valido(savings_atual[i]))
				{
					adiciona_saving_na_rota(savings_atual[i], melhores_rotas_encontradas);
				}
			}

			return melhores_rotas_encontradas;
		}

		vector<vector<vector<Rota>>> ClarkeWright::encontra_roteamentos(std::vector<Cidade> & cidades)
		{
			cidades_entrada = cidades;

			vector<Cidade> facilidades = encontra_facilidades();
			
			vector<vector<vector<Rota>>> melhores_rotas_encontradas = vector<vector<vector<Rota>>>();

			todos_savings = vector<vector<Rota>>();

			for (unsigned int i = 0; i < facilidades.size(); i++)
			{
				vector<Rota> saving_atual = inicializa_savings(facilidades[i]);
				
				ordena_maior_pro_menor(saving_atual);

				todos_savings.push_back(saving_atual);
			}

			for (unsigned int i = 0; i < todos_savings.size(); i ++)
			{
				vector<vector<Rota>> melhor_rota_atual = vector<vector<Rota>>();

				melhor_rota_atual = encontra_rota_partindo_dos_savings(todos_savings[i], facilidades[i]);
				
				melhores_rotas_encontradas.push_back(melhor_rota_atual);
			}

			return melhores_rotas_encontradas;
		}
	}
}