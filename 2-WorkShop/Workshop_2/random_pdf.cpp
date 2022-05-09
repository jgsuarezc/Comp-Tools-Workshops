/* Instructions: 
 * Authors: Sebastian Ordoñez & Cindy Padilla
 * Date: April 3rd, 2022.
*/

#include <random>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>


void compute_pdf(int seed, int nsamples, double mu, double sigma, double xmin, double xmax, int nbins);

int main(int argc, char **argv)
{
  const int SEED = std::atoi(argv[1]);
  const int NSAMPLES = std::atoi(argv[2]);
  const double MU = std::atof(argv[3]);
  const double SIGMA = std::atof(argv[4]);
  const double XMIN = std::atof(argv[5]);
  const double XMAX = std::atof(argv[6]);
  const int NBINS = std::atoi(argv[7]);

  compute_pdf(SEED, NSAMPLES, MU, SIGMA, XMIN, XMAX, NBINS);
}

void compute_pdf(int seed, int nsamples, double mu, double sigma, double xmin, double xmax, int nbins)
{
  // random stuff and histogram
  std::mt19937 gen(seed);
  std::normal_distribution<double> dis{mu, sigma};

  const double bin_width = (double) (xmax - xmin)/ (double) nbins;
  int histogram[nbins] = { 0 };
  int pdf[nbins] = { 0 };

  for(int n = 0; n < nsamples; ++n) {
    double r = dis(gen);
    if (r < xmin || r > xmax) continue;
    
    int count = 0;
    for(double xmin_aux = xmin; xmin_aux <= xmax-bin_width; xmin_aux += bin_width){	      double xmax_aux = xmin_aux + bin_width;
	if (r > xmin_aux && r < xmax_aux){
		histogram[count]++;		
	}
	count += 1;
    }
  }


  //pdf calculation and print
  for(int ii=0; ii< nbins; ii++){
      std::cout << xmin + ii*bin_width << "\t" << histogram[ii]/double(nsamples*bin_width) << "\n";
  }

}

