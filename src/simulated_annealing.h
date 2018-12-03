#pragma once

#include <cstdint>

#include "lib/data.h"
#include "lib/args.h"
#include "aux/sa_defs.h"

class SimulatedAnneling {
public:
    SimulatedAnneling(const Args&);
    PathList operator()(const Instance&) const;
private:
    const Args& _args;
};
