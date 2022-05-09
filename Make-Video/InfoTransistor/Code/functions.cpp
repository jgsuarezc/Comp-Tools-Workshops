#include <cmath>
#include <iostream>
#include "top.h"

double Shockley(double v){
    double I_s = 2.8e-3;
    double V_T = 0.2585;
    double n = 1.0;
    return I_s*(std::exp(v/(n*V_T))-1);
}
