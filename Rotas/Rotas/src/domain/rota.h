#ifndef ROTAS_DOMAIN_ROTA_H_
#define ROTAS_DOMAIN_ROTA_H_

namespace rotas
{
	namespace domain
	{
		class Rota
		{
			int id_origem;
			int id_destino;
			double distancia;
		public:
			Rota() {};
			Rota(int id_origem, int id_destino, double distancia) :
				id_origem(id_origem), id_destino(id_destino), distancia(distancia) {};
			int get_id_origem();
			int get_id_destino();
			double get_distancia();
			bool rota_contem_cidade(int id_cidade);
		};
	} // domain
} // rotas

#endif // ROTAS_DOMAIN_ROTA_H_
