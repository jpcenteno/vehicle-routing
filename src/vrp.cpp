#include <iostream>

#include "lib/CLI11.hpp"
#include "lib/data.h"
#include "savings.h"
#include "goloso.h"



int getAlgorithm(const string& name, Algorithm& a) {
    if (name == "savings") {
        a = Savings();
    } else if (name == "goloso") {
        a = Goloso();
    } else {
        return 0;
    }
    return 1;
}

void printPathList(const PathList& pl) {

    cout << pl.first.size() << endl;

    int route = 1;
    for (auto r :  pl.first) {
        cout << "#" << (route++) << ": ";
        for (size_t i = 0; i < r.size(); ++i) {
            cout << r[i] << " ";
        }
        cout << "\n";
    }

    cout << pl.second << "\n";
}

int main(int argc, char * argv[]) {

    // CLI
    CLI::App app {"TP3 - Aed3"};

    std::string algorithm_name;
    app.add_option("-a,--algo", algorithm_name,
            "algoritmo. Puede ser `savings`")
       ->required()
       ->expected(1);

    CLI11_PARSE(app, argc, argv);

    Algorithm algo;
    getAlgorithm(algorithm_name, algo);

    // Lee STDIN
    const Instance instance;

    // Ejecuta el algoritmo
    const PathList result = algo(instance);

    printPathList(result);

    return 0;

}
