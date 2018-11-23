#pragma once

#include <cstdint>

/** Clase que engloba el comportamiento del esquema de enfriamiento del
 *  algoritmo
 */
class CoolingSchedule {

public:

    /** Inicializa el esquema de enfriamiento.
     *
     * @param `temp_init` Temperatura al inicial y al reinciar.
     * @param `beta` Factor para actualizar la temperatura. 0 < beta < 1
     * @param `max_resets` Cantidad de reinicios durante la ejecución del algorimo.
     */
    CoolingSchedule(float temp_init, float beta, uint32_t max_resets);

    /** Devuelve true si no se usaron todos los resets */
    bool  is_active() const;

    /** Calcula la temperatura del proximo paso y la devuelve. */
    float next();

    /** Reinicia la temperatura y decrementa la cantidad de reinicios. */
    float reset();

private:

    /** Temperatura actual */
    float _temp;

    /** Temperatura inicial */
    const float _temp_init;

    /** Proporción de decremento de la temperatura */
    const float _beta;

    /** Cantidad de reinicios restantes. */
    uint32_t _num_resets;

};
