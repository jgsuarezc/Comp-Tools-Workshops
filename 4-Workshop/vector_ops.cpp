#include "vector_ops.hpp"

double mean(const std::vector<double> & data)
{
    double vsum = 0.0;
    double vmean = 0.0;
    int length = data.size();
  
    for(auto n: data){
        vsum += n;
    }
    vmean = vsum/length;
    return vmean;
}
