#include <iostream>
#include <cmath>
#include <iomanip>

//Function declaration
double det (double a, double b, double c);
double x1(double a, double b, double c, double d);
double x2(double a, double b, double c, double d);
double x1p(double a, double b, double c, double d);
double x2p(double a, double b, double c, double d);


int main(int agrc, char **argv){
    std::cout.precision(15); std::cout.setf(std::ios::scientific);
    const double A = 1.0;
    const double B = 1.0;
    std::cout << std::setw (12) << "c"<< std::setw (24) << "x1" << std::setw(24)<< "x2"
              << std::setw (24)<< "x1'"<< std::setw (24)<< "x2'"<< '\n';
    for(int nn = 1; nn <= 10; nn++){
        double c = std::pow(10.0,-nn);
        double dd = det(A,B,c);
        std::cout << c << '\t'<< x1(A,B,c,dd)- x1p(A,B,c,dd)
                  << '\t' << x2(A,B,c,dd)- x2p(A,B,c,dd)<< '\n';
    }
    return 0;
}

//Roots could be written as: x1'= c/ax2 and x2'=c/ax1, so I will not use all functions below in order  to reduce subtractivecancellation.  
//Implementation
double det(double a, double b, double c){
    return std::sqrt(b*b - 4.0*a*c);
}
//Subtractive cancellation
double x1(double a, double b, double c,double d){
    double x = (-b + d)/(2.0*a);
    return x;
}

double x2(double a, double b, double c,double d){
    double x = (-b - d)/(2.0*a);
    return x;
}
double x1p(double a, double b, double c,double d){
    double x = (2.0*c)/(-b - d);
    return x;
}
//Subtractive cancellation
double x2p(double a, double b, double c, double d){
    double x = (2.0*c)/(-b + d);
    return x;
}
