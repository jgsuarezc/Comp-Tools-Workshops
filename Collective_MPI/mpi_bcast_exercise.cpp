#include "mpi.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <numeric>

void send_data_collective(int size, int pid, int np);
void send_data_point_to_point(int size, int pid, int np);
double average(std::vector<double> data_bw);

int main(int argc, char **argv)
{
  int np, pid;

  /* MPI setup */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);

  const int SIZE = std::atoi(argv[1]);
  //send_data_point_to_point(SIZE, pid, np);
  send_data_collective(SIZE, pid, np);

  MPI_Finalize();

  return 0;
}

void send_data_point_to_point(int size, int pid, int np)
{
  // create data buffer (all processes)
  double * data = new double [size];
  int root = 0;
  MPI_Status status;
  int tag = 0;
  if(pid == 0){
      std::vector<double> bandwidth; bandwidth.resize(np-1);
      std::iota(data, data+size, 0.0);
      for(int dst = 1; dst < np; dst++){
          double t1, t2, total_time;
          t1 = MPI_Wtime();
          MPI_Send(&data[0], size, MPI_DOUBLE, dst, tag, MPI_COMM_WORLD);
          t2 = MPI_Wtime();
          total_time = 2*(t2-t1);
          bandwidth[dst-1] = size*sizeof(double)/total_time/1.0e6;
      }
      std::cout << size <<'\t' << average(bandwidth) << std::endl;
  }
  else {
      MPI_Recv(&data[0], size, MPI_DOUBLE, root, tag, MPI_COMM_WORLD, &status);
  }
  delete [] data;
}

void send_data_collective(int size, int pid, int np)
{
  // create data buffer (all processes)
  double * data = new double [size];
  std::iota(data, data+size, 0.0);
  // send data to all processes
  int root = 0;
  double start = MPI_Wtime();
  MPI_Bcast(&data[0], size, MPI_DOUBLE, root, MPI_COMM_WORLD);
  double end = MPI_Wtime();
  // print size, time, bw in root
  if (0 == pid) {
    int datasize = sizeof(double)*size;
    std::cout //<< datasize << "\t" << (end-start) << "\t"
      << size << '\t' << datasize/(end-start)/1.0e6 << "\n";
  }
  delete [] data;
}
double average(std::vector<double> data_bw)
{
  double sum = std::accumulate(data_bw.begin(), data_bw.end(), 0.0);
  double mean = sum / data_bw.size();

  return mean;
}
