#ifndef SRC_SAVINGS_H
#define SRC_SAVINGS_H

#include "lib/data.h"
#include <deque>

using namespace std;

struct Ruta {
	list<size_t> camino;
	unsigned int capacidad;

	Ruta(size_t i, unsigned int c) {
		camino = {i};
		capacidad = c;
	} 
}; 


class Savings {


public:

    PathList operator()(const Instance&) const;


	
};

#endif // SRC_SAVINGS_H
