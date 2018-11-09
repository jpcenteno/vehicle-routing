#ifndef SRC_SAVINGS_H
#define SRC_SAVINGS_H

#include "lib/data.h"
#include <deque>

using namespace std;

struct Ruta {
	deque<Saving> camino;	
	int capacidad; 
}; 


class Savings {


public:

    PathList operator()(const Instance&) const;


	
};

#endif // SRC_SAVINGS_H
