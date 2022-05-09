#include "vector_ops.hpp"
#include <iostream>

//main function that calculates x mean
int main(int argc, char **argv) {
  
    const int N = std::atoi(argv[1]);
    std::vector<double> x;
    x.resize(N);
    std::iota(x.begin(), x.end(), 0.0);
    std::cout << mean(x) << "\n";
    
}
