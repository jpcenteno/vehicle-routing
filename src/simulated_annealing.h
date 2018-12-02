#pragma once

#include <cstdint>

#include "lib/data.h"
#include "lib/args.hpp"
#include "aux/sa_defs.h"

class SimulatedAnneling {
public:
    PathList operator()(const Instance&) const;
};
