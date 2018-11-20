#include <iostream>

#include "lib/CLI11.hpp"
#include "lib/data.h"
#include "savings.h"
#include "goloso.h"


int main(int argc, char * argv[]) {

    // CLI
    CLI::App app {"TP3 - Aed3"};

    std::string algorithm;
    app.add_option("-a,--algo", algorithm,
            "algoritmo. Puede ser `savings`");

    CLI11_PARSE(app, argc, argv);

    // Lee STDIN
    const Instance instance;

    const Savings solve_savings;
    const PathList result = solve_savings(instance);

    cout << result.first.size() << endl;
    int route = 1;
    for (auto r :  result.first) {
        cout << "#" << (route++) << ": ";
        for (size_t i = 0; i < r.size(); ++i) {
            cout << r[i] << " ";
        }
        cout << "\n";
    }
    cout << result.second << "\n";

    return 0;

}
