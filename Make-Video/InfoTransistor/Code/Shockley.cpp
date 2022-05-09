#include <iostream>
#include <cmath>
#include "top.h"

int main(int argc, char **argv){
    for (double vv = 0.1; vv <= 1.0; vv+=0.01){
        std::cout << vv << "\t"<< Shockley(vv) << "\n";
    }
    return 0;
}
