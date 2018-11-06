#include <iostream>

#include "lib/CLI11.hpp"
#include "lib/data.h"


int main(int argc, char * argv[]) {

    // CLI
    CLI::App app {"TP3 - Aed3"};

    std::string algorithm;
    app.add_option("-a,--algo", algorithm,
            "algoritmo. Puede ser `savings`");

    CLI11_PARSE(app, argc, argv);

    // Lee STDIN
    const Instance instance;

    return 0;

}
