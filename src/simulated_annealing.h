#pragma once

#include <cstdint>

#include "lib/data.h"
#include "aux/sa_defs.h"

class SimulatedAnneling {
public:
    PathList operator()(const Instance&) const;
};
