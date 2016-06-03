#include "algoritmos/clarke_wright.h"
#include "algoritmos/gillet_johnson.h"
#include "domain/rota.h"
#include "domain/caminho.h"
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
using namespace rotas::algoritmos;

namespace rotas {
	namespace algoritmos {

		static vector<Cidade> cidades_entrada;
		static Cidade facilidade;

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

		bool rota_a_maior_que_b(Rota rota_a, Rota rota_b)
		{
			return rota_a.get_distancia() > rota_b.get_distancia();
		}

		void ordena_maior_pro_menor(vector<Rota> &savings)
		{
			sort(savings.begin(), savings.end(), rota_a_maior_que_b);
		}

		vector<Rota> inicializa_savings(Cidade facilidade)
		{
			vector<Cidade> pontos_demanda = encontra_pontos_demandas(facilidade);

			vector<Rota> savings = vector<Rota>();

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

		int acha_rota_com_cidade(int id_cidade, vector<Caminho> &rotas)
		{
			int size_rotas = rotas.size();
			for (unsigned int i = 0; i < size_rotas; i++)
			{
				if(rotas[i].cidade_existe_na_rota(id_cidade))
					return i;
			}
			return -1;
		}

		void adiciona_saving_na_rota(Rota saving, vector<Caminho> &rotas_encontradas)
		{
			int index_ciclo_origem = acha_rota_com_cidade(saving.get_id_origem(),rotas_encontradas);
			int index_ciclo_destino = acha_rota_com_cidade(saving.get_id_destino(), rotas_encontradas);

			bool pertence_rotas_diferentes = false;
			bool origem_esta_apta_ser_adicionada = false;
			bool destino_esta_apto_ser_adicionado = false;

			if(index_ciclo_origem > -1)
			{
				pertence_rotas_diferentes = !rotas_encontradas[index_ciclo_origem].cidade_existe_na_rota(saving.get_id_destino());
				origem_esta_apta_ser_adicionada = rotas_encontradas[index_ciclo_origem].cidade_esta_no_fim_ou_comeco_rota(saving.get_id_origem());
			}
			if (index_ciclo_destino > -1)
			{
				destino_esta_apto_ser_adicionado = rotas_encontradas[index_ciclo_destino].cidade_esta_no_fim_ou_comeco_rota(saving.get_id_destino());
			}

			// TODO: colocar checagem de exceder capacidade do veiculo aqui
			
			if (pertence_rotas_diferentes && origem_esta_apta_ser_adicionada && destino_esta_apto_ser_adicionado)
			{
				int index_ciclo_join, index_ciclo_removido, id_origem, id_destino;
				bool dois_ciclos_comeco = false;
				bool dois_ciclos_fim = false;
				if (rotas_encontradas[index_ciclo_origem].cidade_no_fim_excluindo_facilidade(saving.get_id_origem()) &&
					rotas_encontradas[index_ciclo_destino].cidade_no_comeco_excluindo_facilidade(saving.get_id_destino()))
				{
					index_ciclo_join = index_ciclo_origem;
					index_ciclo_removido = index_ciclo_destino;
					id_origem = saving.get_id_origem();
					id_destino = saving.get_id_destino();
				}
				else if (rotas_encontradas[index_ciclo_origem].cidade_no_comeco_excluindo_facilidade(saving.get_id_origem()) &&
					rotas_encontradas[index_ciclo_destino].cidade_no_fim_excluindo_facilidade(saving.get_id_destino())) {
					index_ciclo_join = index_ciclo_destino;
					index_ciclo_removido = index_ciclo_origem;
					id_origem = saving.get_id_destino();
					id_destino = saving.get_id_origem();
				}
				else if (rotas_encontradas[index_ciclo_origem].cidade_no_comeco_excluindo_facilidade(saving.get_id_origem()) &&
					rotas_encontradas[index_ciclo_destino].cidade_no_comeco_excluindo_facilidade(saving.get_id_destino())) {
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
					// Remove a primeira rota dos dois ciclos
					rotas_encontradas[index_ciclo_join].apaga_rota_comeco();
					rotas_encontradas[index_ciclo_removido].apaga_rota_comeco();

					// Adiciona a rota do saving ao ciclo que recebera o join
					//adiciona_rota_comeco(id_origem, id_destino, rotas_encontradas[index_ciclo_join]);
					rotas_encontradas[index_ciclo_join].adiciona_rota_fim_trajeto(id_origem, id_destino,
						cidades_entrada[id_origem].get_distancia(id_destino));
				}
				else if (dois_ciclos_fim)
				{
					// Remove as ultimas rotas dos dois ciclos
					rotas_encontradas[index_ciclo_join].apaga_rota_fim();
					rotas_encontradas[index_ciclo_removido].apaga_rota_fim();

					// Adiciona a rota do saving ao ciclo que recebera o join
					rotas_encontradas[index_ciclo_join].adiciona_rota_fim_trajeto(id_origem, id_destino,
						cidades_entrada[id_origem].get_distancia(id_destino));
				}
				else
				{
					// Remove a ultima rota e a primeira dos ciclos
					rotas_encontradas[index_ciclo_join].apaga_rota_fim();
					rotas_encontradas[index_ciclo_removido].apaga_rota_comeco();

					// Adiciona a rota do saving ao ciclo que recebera o join
					rotas_encontradas[index_ciclo_join].adiciona_rota_fim_trajeto(id_origem, id_destino,
						cidades_entrada[id_origem].get_distancia(id_destino));

					// Adiciona as rotas que estavam no ciclo que sera removido da lista
					int size_ciclo_removido = rotas_encontradas[index_ciclo_removido].quantidade_rotas_trajeto();
					for (unsigned int i = 0; i < size_ciclo_removido; i++)
					{
						rotas_encontradas[index_ciclo_join].
										adiciona_rota_fim_trajeto(rotas_encontradas[index_ciclo_removido].get_rota_indice(i));
					}
				}


				if (dois_ciclos_comeco || dois_ciclos_fim)
				{
					// Adiciona as rotas que estavam no ciclo que sera removido da lista
					int size_ciclo_removido = rotas_encontradas[index_ciclo_removido].quantidade_rotas_trajeto();
					for (unsigned int i = 0; i < size_ciclo_removido; i++)
					{
						Rota rota_atual = rotas_encontradas[index_ciclo_removido].get_rota_indice(i);
						// Adiciona a rota do saving ao ciclo que recebera o join
						rotas_encontradas[index_ciclo_join].
							adiciona_rota_comeco_trajeto(rota_atual.get_id_destino(), rota_atual.get_id_origem(),rota_atual.get_distancia());
					}
				}
				
				// Apaga o ciclo de rota que foi incorporado
				rotas_encontradas.erase(rotas_encontradas.begin() + index_ciclo_removido);
				
			}
		}

		void inicializa_rotas_demandas(vector<Caminho> &rotas_demandas)
		{
			vector<Cidade> demandas = encontra_pontos_demandas(facilidade);
			
			int size_demandas = demandas.size();
			int id_facilidade = facilidade.get_id();
	
			rotas_demandas = vector<Caminho>(size_demandas);
			
			for (unsigned int i = 0; i < size_demandas; i++)
			{
				int id_demanda = demandas[i].get_id();
				rotas_demandas[i].adiciona_rota_fim_trajeto(id_facilidade, id_demanda, 
											cidades_entrada[id_facilidade].get_distancia(id_demanda));
				rotas_demandas[i].adiciona_rota_fim_trajeto(id_demanda,id_facilidade,
					cidades_entrada[id_demanda].get_distancia(id_facilidade));
			}
		}

		void encontra_rota_partindo_dos_savings(vector<Rota> &savings, vector<Caminho> & melhores_caminhos)
		{

			inicializa_rotas_demandas(melhores_caminhos);
			
			for (unsigned int i = 0;  i < savings.size(); i++)
			{
				if (saving_e_valido(savings[i]))
				{
					adiciona_saving_na_rota(savings[i], melhores_caminhos);
				}
			}
		}

		vector<Caminho> ClarkeWright::encontra_roteamentos(std::vector<Cidade> & cidades,Cidade facilidade_entrada)
		{
			cidades_entrada = cidades;
			facilidade = facilidade_entrada;
		
			vector<Caminho> melhores_caminhos_encontrados = vector<Caminho>();

			vector<Rota> savings = inicializa_savings(facilidade);
			
			ordena_maior_pro_menor(savings);

			encontra_rota_partindo_dos_savings(savings, melhores_caminhos_encontrados);

			return melhores_caminhos_encontrados;
		}
	}
}