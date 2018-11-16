#ifndef SRC_SWEEP_TSPGOLOSO_H
#define SRC_SWEEP_TSPGOLOSO_H

#include "lib/data.h"


using namespace std;

class Sweep {


public:

    PathList operator()(const Instance&) const;
	pair<vector<int>, int> tspGoloso(vector<Node>& cluster, const Instance& instance) const;
	PathList ruteo(vector<vector<Node> >& clusters, const Instance& instance) const;
	
};

#endif // SRC_SWEEP_TSPGOLOSO_H
