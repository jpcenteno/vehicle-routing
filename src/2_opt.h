#ifndef SRC_2_OPT_H
#define SRC_2_OPT_H

#include "lib/data.h"
#include "savings.h"

using namespace std;

class TwoOpt {

private:
	unsigned int costo_ruta(const vector<size_t>& r,  const MatrizDist& dist) const;
	vector<size_t> swap_nodos(size_t i, size_t j, const vector<size_t>& r) const;
	unsigned int two_opt(vector<size_t>& r, const MatrizDist& dist) const;

public: 
	PathList operator()(const Instance&) const;

};

#endif // SRC_2_OPT_H
