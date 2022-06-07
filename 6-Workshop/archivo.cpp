#include <iostream>
#include <cstdlib>
#include <cmath>
#include <numeric>
#include <vector>
#include <algorithm>
#include "mpi.h"

typedef std::vector<double> data_t; // alias

void fill_matrix(data_t & data, int nrows, int ncols, int pid, int np);
void print_matrix(const data_t & data, int nrows, int ncols, int pid, int np);
void print_local(const data_t & data, int nrows, int ncols);
double average(data_t data_bw);

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv); /* Mandatory */

  int pid;                 /* rank of process */
  int np;                 /* number of processes */

  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  int N = std::atoi(argv[1]);
  int Nlocal = N/np;
  
  data_t data; data.resize(Nlocal*N); /*Sub-matrix for each process*/
  std::fill(data.begin(), data.end(), 0.0);


  fill_matrix(data, Nlocal, N, pid, np);
  print_matrix(data, Nlocal,N, pid, np);


  MPI_Finalize(); /* Mandatory */

  return 0;
}

void fill_matrix(data_t & data, int nrows, int ncols, int pid, int np)
{
  /* Adjust problem size for sub-process */
  int idxs = data.size();
  int lower_idx = pid*idxs;
  for(int ii = 0; ii < idxs; ++ii){
      if((lower_idx+ii)%ncols == (lower_idx+ii)/ncols){
          data[ii] = 1;
      }
  }
}
void print_matrix(const data_t & data, int nrows, int ncols, int pid, int np)
{
  /* Collect info and print results */
  data_t bandwidth; bandwidth.resize(np-1);
  MPI_Status status;
  int tag = 0;
  if (0 == pid) { /* Master*/ 
      print_local(data, nrows, ncols);
      data_t matrix(nrows*ncols); /* To receive */
      for (int src = 1; src < np; ++src) {
          double t1 = MPI_Wtime();
          MPI_Recv(&matrix[0], data.size(), MPI_DOUBLE, src, tag, MPI_COMM_WORLD, &status);
          double t2 = MPI_Wtime();
          double total_time = t2-t1;
          bandwidth[src-1] = data.size()*sizeof(double)/total_time/1.0e6;
          print_local(matrix, nrows, ncols);
    }
      std::cout << "Avg. Bandwith: " << average(bandwidth) << " MB/s" << std::endl;  
  }
  else { /* slaves only send */
    int dest = 0;
    MPI_Send(&data[0], data.size(), MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
  }
}
void print_local(const data_t & data, int nrows, int ncols)
{
  for(int ll = 0; ll < nrows; ++ll) {
    for(int kk = 0; kk < ncols; ++kk) {
      std::cout << data[ll*ncols + kk] << " ";
    }
    std::cout << "\n";
  }
}
double average(data_t data_bw)
{
  double sum = std::accumulate(data_bw.begin(), data_bw.end(), 0.0);
  double mean = sum / data_bw.size();

  return mean;
}

