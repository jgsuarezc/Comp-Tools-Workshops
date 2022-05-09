#include <Eigen/Dense>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

double multiply(int size);
void statistics(double &meanT, double &stdevT, int R, int L);

int main(int argc, char **argv) {

  int R = 10;            // Repetitions

  double meanT = 0.0;
  double stdevT = 0.0;
  for(int LL = 2; LL < 8192; LL*=2){
    statistics(meanT, stdevT, R, LL);
    // Impresion en pantalla
    std::cout << LL << '\t' << meanT << '\t' << stdevT << std::endl;
  }
  return 0;
}

double multiply(int size) {
  // create matrices
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(size, size);
  Eigen::MatrixXd B = Eigen::MatrixXd::Random(size, size);

  auto start = std::chrono::steady_clock::now();
  auto C{A * B};        // MULTIPLY
  double tmp = C(0, 0); // use the matrix to make eigen compute it
  auto end = std::chrono::steady_clock::now();

  // std::clog << tmp << std::endl; // use the matrix to make eigen compute it

  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

void statistics(double &meanT, double &stdevT, int R, int L) {
  std::vector<double> wall_time;

  for (int rr = 0; rr < R; ++rr) {
    srand(rr + 1);
    wall_time.push_back(multiply(L));
  }
  double sum = std::accumulate(wall_time.begin(), wall_time.end(), 0.0);
  double mean = sum / wall_time.size();
  std::vector<double> diff(wall_time.size()); // To avoid overflow,underflow:
  std::transform(wall_time.begin(), wall_time.end(), diff.begin(),
                 std::bind2nd(std::minus<double>(), mean));
  double sq_sum =
      std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / wall_time.size());

  meanT = mean;
  stdevT = stdev;
}
