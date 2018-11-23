#include "coolingschedule.h"


CoolingSchedule::CoolingSchedule(float temp_init, float beta, uint32_t max_resets)
    : _temp_init(temp_init), _beta(beta) {

        _temp       = temp_init;
        _num_resets = max_resets;

}


float CoolingSchedule::reset() {

    _temp = _temp_init;
    _num_resets--;

    // (Devuelve _temp_init y actualiza _temp para el proximo llamado)
    return next();

}


float CoolingSchedule::next() {

    float t = _temp;
    _temp = _beta * _temp;

    return t;

}


bool CoolingSchedule::is_active() const {

    return _num_resets > 0;

}
