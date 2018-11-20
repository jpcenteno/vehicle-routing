#include "lib/data.h"
#include "savings.h"

PathList Savings::operator()(const Instance& instance) const {

	// Datos de la instancia
	int n = instance.size();
    MatrizDist dist = instance.getDistances();
	vector<Node> nodos = instance.getNodes();
	unsigned int C = instance.getCapacity();

	// Max-heap de savings
	priority_queue<Saving> savings_pq; // O(n)

	// Savings O(n^2*log(n))
	for (int i = 1; i < n; i++) {
		for(int j = i + 1; j < n; j++) {
			savings_pq.push({i, j, dist[i][0] + dist[0][j] - dist[i][j]}); // i, j, saving
		}	
	}

	// Lista de rutas. Cada una tiene un camino y una capacidad.
	list<Ruta> rutas; // O(1)
	vector<list<Ruta>::iterator> it_ruta(n, rutas.end()); // it_ruta[i] = iterador a la ruta de la ciudad i O(n)

	// Control de ciudades visitadas
	int ciudades_visitadas = 1;
	vector<bool> visitada(n, false); // O(n)
	visitada[0] = true;

	while (!savings_pq.empty() && ciudades_visitadas < n) { // O(n^2)
		Saving sav = savings_pq.top(); // O(1)
		savings_pq.pop(); // (log n)

		int i = sav.i;
		int j = sav.j;

		// Saving descartado
		if (nodos[i].demand + nodos[j].demand > C) continue;

		// Las ciudades no están en ninguna ruta
		if (it_ruta[i] == rutas.end() && it_ruta[j] == rutas.end()) {
			rutas.push_back({i, j, nodos[i].demand + nodos[j].demand}); // i, j, demanda O(1)
			it_ruta[i] = it_ruta[j] = prev(rutas.end()); // O(1)
		// La ciudad i está en una ruta y la ciudad j no
		} else if (it_ruta[i] != rutas.end() && it_ruta[j] == rutas.end()) {
			auto r = it_ruta[i];

			if (nodos[j].demand + r->capacidad > C) continue;

			if (r->camino.front() == i) {
				r->camino.push_front(j); // O(1)
				r->capacidad += nodos[j].demand;
				it_ruta[j] = it_ruta[i];
			} else if (r->camino.back() == i) {
				r->camino.push_back(j); // O(1)
				r->capacidad += nodos[j].demand;
				it_ruta[j] = it_ruta[i];
			}
		// La ciudad j está en una ruta y la ciudad i no
		} else if (it_ruta[i] == rutas.end() && it_ruta[j] != rutas.end()) {
			auto r = it_ruta[j];

			if (nodos[i].demand + r->capacidad > C) continue;	

			if (r->camino.front() == j) {
				r->camino.push_front(i); // O(1)
				r->capacidad += nodos[i].demand;
				it_ruta[i] = it_ruta[j];
			} else if (r->camino.back() == j) {
				r->camino.push_back(i); // O(1)
				r->capacidad += nodos[i].demand;
				it_ruta[i] = it_ruta[j];
			}
		// Ambas ciudades están el alguna ruta
		} else {
			auto ruta_i = it_ruta[i];
			auto ruta_j = it_ruta[j];

			// Están en la misma ruta
			if (ruta_i == ruta_j) continue;

			// La unión de rutas supera la capacidad de un camión
			if (ruta_i->capacidad + ruta_j->capacidad > C) continue;

			int front_i = ruta_i->camino.front();
			int back_i = ruta_i->camino.back();

			int front_j = ruta_j->camino.front();
			int back_j = ruta_j->camino.back();

			if (front_i == i && front_j == j) {
				ruta_i->camino.insert(ruta_i->camino.begin(), ruta_j->camino.rbegin(), ruta_j->camino.rend()); // O(n)
				ruta_i->capacidad += ruta_j->capacidad;
				for (auto c : it_ruta[j]->camino) // O(n)
					it_ruta[c] = it_ruta[i]; // O(1)
				rutas.erase(ruta_j); // O(1)
			} else if (back_i == i && back_j == j) {
				ruta_i->camino.insert(ruta_i->camino.end(), ruta_j->camino.rbegin(), ruta_j->camino.rend());
				ruta_i->capacidad += ruta_j->capacidad;
				for (auto c : it_ruta[j]->camino)
					it_ruta[c] = it_ruta[i];
				rutas.erase(ruta_j);
			} else if (front_i == i && back_j == j) {
				ruta_j->camino.insert(ruta_j->camino.end(), ruta_i->camino.begin(), ruta_i->camino.end());
				ruta_j->capacidad += ruta_i->capacidad;
				for (auto c : it_ruta[i]->camino)
					it_ruta[c] = it_ruta[j];
				rutas.erase(ruta_i);
			} else { // back_i == i && front_j == j
				ruta_i->camino.insert(ruta_i->camino.end(), ruta_j->camino.begin(), ruta_j->camino.end());
				ruta_i->capacidad += ruta_j->capacidad;
				for (auto c : it_ruta[j]->camino)
					it_ruta[c] = it_ruta[i];
				rutas.erase(ruta_j);
			}
		}

		if (!visitada[i] && it_ruta[i] != rutas.end()) {
			visitada[i] = true;
			ciudades_visitadas++; 
		}

		if (!visitada[j] && it_ruta[j] != rutas.end()) {
			visitada[j] = true;
			ciudades_visitadas++; 
		}
	}

	PathList result;
	result.second = 0;
	
	int last;
	for (auto r : rutas) { // O(n)
		last = 0;
		vector<int> ruta;
		for (auto nodo : r.camino) { 
			ruta.push_back(nodo); // O(1)
			result.second += dist[last][nodo];
			last = nodo;
		}
		result.first.push_back(ruta); // O(1)
		result.second += dist[last][0];
	}

	return result;
}


