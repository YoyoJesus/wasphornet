#include "utilities.hpp"

int main (int argc, char *argv[]) {
    if (argc < 2)
        std::cerr << "No file input provided, please run again!" << std::endl;

    std::ifstream in(argv[1]);

    if (!in) {
        std::cerr << "Specified input file could not be opened" << std::endl;
        return 1; // Return an error code
    }

    std::ofstream out(argv[2]);

    if (!out)
        Prefix(in, std::cout);

    Prefix(in, out);

    in.close();
    out.close();
    return 0;
}