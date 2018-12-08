#include <iostream>
#include <random>

using namespace std;

/*
	Genera una instancia de n nodos distribuidos uniformemente en el plano, entre las coordenadas [0, ..., 1000]
	y capacidades [0, ..., 30]
*/
int main() {
	int n; cin >> n;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> demand(1, 30);
	uniform_int_distribution<int> coord(0, 1000);

	cout << "NAME : Uniform\n";
	cout << "COMMENT : Instancia de experimentacion\n";
	cout << "TYPE : CVRP\n";
	cout << "DIMENSION : " << n << "\n";
	cout << "EDGE_WEIGHT_TYPE : EUC_2D\n";
	cout << "CAPACITY : 100\n";
	cout << "NODE_COORD_SECTION\n";
	for (int i = 1; i <= n; ++i) {
		cout << i << " " << coord(gen) << " " << coord(gen) << "\n"; 
	}
	cout << "DEMAND_SECTION : \n";
	cout << 1 << " " << 0 << "\n";
	for (int i = 2; i <= n; ++i) {
		cout << i << " " << 52 << "\n"; 		//aca seteo en 52 todas las demandas
	}
	cout << "DEPOT_SECTION\n"; 
 	cout << " 1\n";  
	cout << " -1\n"; 
	cout << " EOF\n";
	return 0;
}
