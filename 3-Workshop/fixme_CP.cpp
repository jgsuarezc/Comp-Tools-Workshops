
#include <iostream>
#include <cmath>

int foo(int a, int b);
int bar(int a, int b);
double baz(double x);

int main(int argc, char **argv) {
  
  int ii, jj;
  ii = 0;
  jj = -1;
  std::cout << foo(ii, jj) << std::endl;
  std::cout << foo(jj, ii) << std::endl;
  std::cout << baz(25.9) << std::endl;

  return 0;
}

int foo(int a, int b) {
  int z = -a*a + b/bar(a,b) -b*b;
  return z;
}

int bar(int a, int b) {
  unsigned int c = a;
  return c + a - b;
}

double baz(double x) {
  if (x < 0){
    double nx = std::fabs(x);
    return std::sqrt(nx);
  }
  //  double v = 1 - (x + 1);
  return std::sqrt(x);
}
