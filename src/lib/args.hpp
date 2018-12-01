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

}

/** Configura el parser de argumentos */
void init_arg_parsing() {

    std::string algorithm_name;
    args::app.add_option("-a,--algo", algorithm_name,
            "Algoritmo. Puede ser `savings`, `goloso`, `sweep`, `2-opt`, `annealing`")
       ->required()
       ->expected(1);

    args::exp_flag = args::app.add_flag("--exp,-e", "Mostrar tiempo de ejecución");

}

#define PARSEARGS() \
    init_arg_parsing(); \
    CLI11_PARSE(args::app, argc, argv);

