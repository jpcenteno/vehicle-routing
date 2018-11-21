#ifndef SRC_2_OPT_H
#define SRC_2_OPT_H

#include "lib/data.h"
#include "savings.h"

using namespace std;

class TwoOpt {

private:
	float costo_ruta(const vector<size_t>& r,  const MatrizDist& dist) const;
	vector<size_t> swap_nodos(int i, int j, const vector<size_t>& r) const;
	float two_opt(vector<size_t>& r, const MatrizDist& dist) const;

public: 
	PathList operator()(const Instance&) const;

};

#endif // SRC_2_OPT_H