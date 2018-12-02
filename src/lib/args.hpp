#pragma once

#include <string>
#include "CLI11.hpp"

/**
 * No es la manera mas elegante de resolver el problema, pero creo que la más
 * sencilla de permitir a los algoritmos acceder a sus parámetros especificos
 * pasados en forma de argumentos sin modificar demaciado la estructura del
 * programa.
 */

namespace args {

    CLI::App app {"TP3 - Aed3"};

    // Nombre del algoritmo
    std::string algorithm_name;

    // Flag "experimentación"
    CLI::Option* exp_flag;

    // -- Simuleated Annealing ----------------------------------------------

    uint32_t max_iters = std::numeric_limits<uint32_t>::max();
    float    beta = 0.7f;

    void init_arg_parsing();

}

/** Configura el parser de argumentos */
void args::init_arg_parsing() {

    args::app.add_option("-a,--algo", args::algorithm_name,
            "Algoritmo. Puede ser `savings`, `goloso`, `sweep`, `2-opt`, `annealing`")
       ->required()
       ->expected(1);

    args::exp_flag = args::app.add_flag("--exp,-e", "Mostrar tiempo de ejecución");

    args::app.add_option("--max-iters,-k", args::max_iters,
            "Cantidad máxima de iteraciones en Simulated Annealing.");

    args::app.add_option("--beta,-b", args::beta,
            "Cantidad máxima de iteraciones en Simulated Annealing.");
}

#define PARSEARGS() \
    args::init_arg_parsing(); \
    CLI11_PARSE(args::app, argc, argv);
