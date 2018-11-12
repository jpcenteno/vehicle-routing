#ifndef SRC_SAVINGS_H
#define SRC_SAVINGS_H

#include "lib/data.h"
#include <deque>

using namespace std;

struct Ruta {
	list<int> camino;	
	unsigned int capacidad;

	Ruta(int i, int j, unsigned int c) {
		camino = {i, j};
		capacidad = c;
	} 
}; 


class Savings {


public:

    PathList operator()(const Instance&) const;


	
};

#endif // SRC_SAVINGS_H
