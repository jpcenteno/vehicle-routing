#pragma once

#include <cstdint>

#include "lib/data.h"
#include "aux/sa_defs.h"

class SimulatedAnneling {

public:

    PathList operator()(Instance&,
                        uint32_t n_resets = 3,
                        float t           = 10,
                        float beta        = static_cast<float>(0.7));

private:

};
