#include <iostream>

int main(int argc, char *argv[]) {

    // Command line arguments
    std::cout << "Number of command line arguments = " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "Argument " << i << " = " << argv[i] << std::endl;
    }
    
    return 0;
}