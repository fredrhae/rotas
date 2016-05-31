#include "algoritmos/clarke_wright.h"
#include "algoritmos/gillet_johnson.h"
#include "domain/rota.h"
#include <vector>

using namespace std;
using namespace rotas::algoritmos;

namespace rotas {
	namespace algoritmos {

		static vector<Cidade> cidades_entrada;

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

		double ClarkeWright::get_distancia(Cidade a, Cidade b) {
			vector<Rota> rotas_a = a.get_rotas();
			for (unsigned int i = 0; i < rotas_a.size(); i++) {
				if (rotas_a[i].get_id_destino() == b.get_id()) {
					return rotas_a[i].get_distancia();
				}
			}
			return 0.0;
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
						double distancia_origem_facilidade = clarke.get_distancia(cidades_entrada[id_cidade_origem_atual],facilidade);
						double distancia_facilidade_destino = clarke.get_distancia(facilidade,cidades_entrada[id_cidade_destino]);
						double distancia_origem_destino = clarke.get_distancia(cidades_entrada[id_cidade_origem_atual], cidades_entrada[id_cidade_destino]);
						double distancia_saving_atual = distancia_origem_facilidade + distancia_facilidade_destino - distancia_origem_destino;

						savings.push_back(Rota(id_cidade_origem_atual,id_cidade_destino,distancia_saving_atual));
					}
				}
			}
			
			return savings;
		}

		vector<vector<Rota>> ClarkeWright::encontra_roteamentos(std::vector<Cidade> & cidades)
		{
			cidades_entrada = cidades;

			vector<Cidade> facilidades = encontra_facilidades();
			
			vector<vector<Rota>> todos_savings = vector<vector<Rota>>();

			for (unsigned int i = 0; i < facilidades.size(); i++)
			{
				todos_savings.push_back(inicializa_savings(facilidades[i]));
			}
			
			// TODO: Ordenar os savings do maior pro menor

			// TODO: Fazer a rota de acordo com os savings

			return todos_savings;
		}
	}
}