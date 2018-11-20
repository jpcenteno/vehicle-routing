#pragma once

#include "lib/data.h"

class SimulatedAnneling {
public:
    PathList operator()(const Instance&) const;
};
