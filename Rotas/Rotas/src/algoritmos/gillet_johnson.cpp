#include "gillet_johnson.h"
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// --------- TODO: não está contando com a capacidade de cada ponto de atendimento --------
namespace rotas
{
	namespace algoritmos
	{	
		double GilletJohnson::get_distancia(Cidade a, Cidade b) {
			vector<Rota> rotas_a = a.get_rotas();
			for (unsigned int i = 0; i < rotas_a.size(); i++) {
				if (rotas_a[i].get_id_destino() == b.get_id()) {
					return rotas_a[i].get_distancia();
				}
			}
			return 0.0;
		}

		bool compara_diferencas(Cidade a, Cidade b) {
			return a.diferenca < b.diferenca;
		}
		
		Cidade GilletJohnson::encontra_mais_proxima(Cidade origem, vector<Cidade> destinos) {
			Cidade mais_proxima = destinos[0];
			double menor_distancia = get_distancia(origem, mais_proxima);
			
			for (unsigned int i = 0; i < destinos.size(); i++) {
				double distancia = get_distancia(origem, destinos[i]);
				if (distancia < menor_distancia) {
					menor_distancia = distancia;
					mais_proxima = destinos[i];
				}
			}

			return mais_proxima;
		}

		//TODO testar esse método
		vector<Cidade> GilletJohnson::ordena_por_distancia(Cidade origem, vector<Cidade> destinos) {
			vector<Cidade> cidades_em_ordem = vector<Cidade>();

			cidades_em_ordem.push_back(destinos[0]);

			struct _compara_distancia {
				Cidade _origem;				
				GilletJohnson gilletJohnson;
				bool operator() (Cidade a, Cidade b) { return gilletJohnson.get_distancia(_origem, a) < gilletJohnson.get_distancia(_origem, b); }
			} compara_distancia;
			compara_distancia._origem = origem;

			for (unsigned int i = 1; i < destinos.size(); i++) {
				auto it = upper_bound(cidades_em_ordem.begin(), cidades_em_ordem.end(), destinos[i], compara_distancia);
				cidades_em_ordem.insert(it, destinos[i]);
				
			}			

			return cidades_em_ordem;
		}

		void GilletJohnson::encontra_medianas(vector<Cidade> & cidades) {

			vector<Cidade> pontos_atendimento = vector<Cidade>();
			vector<Cidade> pontos_demanda = vector<Cidade>();
			for (unsigned int i = 0; i < cidades.size(); i++) {
				if (cidades[i].is_mediana()) {
					pontos_atendimento.push_back(cidades[i]);
				}
				else {
					pontos_demanda.push_back(cidades[i]);
				}
			}

			switch (pontos_atendimento.size()) {
			case 0:
				//Se não encontrou nenhum ponto de atendimento, o algoritmo não faz sentido
				//TODO disparar exceção
				return;
			case 1:
				//Se encontrou um ponto de atendimento, ele atende a todos os pontos de demanda
				for (unsigned int i = 0; i < cidades.size(); i++) {
					cidades[i].set_id_mediana(pontos_atendimento.front().get_id());
				}
				return;				
			default:
				//TODO: fazer primeiro pra uma cidade
				vector<Cidade> lista_designacao = vector<Cidade>();

				for (unsigned int i = 0; i < pontos_demanda.size(); i++) {
					Cidade ponto_demanda = pontos_demanda[i];
					//Passo 1: Encontrar L1 e L2, as duas medianas mais próximas
					vector<Cidade> pontos_atendimento_ordenados = ordena_por_distancia(ponto_demanda, pontos_atendimento);
					//L1 -> cidades_ordenadas[0]
					//L2 -> cidades_ordenadas[1]

					//Passo 2: calcular a razão r = |L2| - |L1|
					double d1 = get_distancia(ponto_demanda, pontos_atendimento_ordenados[0]);
					double d2 = get_distancia(ponto_demanda, pontos_atendimento_ordenados[1]);
					double d = d2 - d1;
					ponto_demanda.diferenca = d;

					//Passo 3: preencher a lista de designação
					lista_designacao.push_back(ponto_demanda);
				}

				//Passo 4: organizar a lista por ordem crescente de d
				sort(lista_designacao.begin(), lista_designacao.end(), compara_diferencas);
				
				//Passo 5: Designar os pontos de demanda ao ponto de atendimento mais próximo
				for (unsigned i = 0; i < lista_designacao.size(); i++) {
					Cidade ponto_atendimento_mais_prox = encontra_mais_proxima(lista_designacao[i], pontos_atendimento);
					lista_designacao[i].set_id_mediana(ponto_atendimento_mais_prox.get_id());
				}				

				for (unsigned i = 0; i < lista_designacao.size(); i++) {
					Cidade cidade = lista_designacao[i];					
					cidades[cidade.get_id()].set_id_mediana(cidade.get_id_mediana());
				}
			
				break;
			}			
			
		}
	} // algoritmos
} // rotas
