#ifndef SRC_SWEEP_TSPGOLOSO_H
#define SRC_SWEEP_TSPGOLOSO_H

#include "lib/data.h"


using namespace std;

class Sweep {


public:

    PathList operator()(const Instance&) const;
 	
};

#endif // SRC_SWEEP_TSPGOLOSO_H
