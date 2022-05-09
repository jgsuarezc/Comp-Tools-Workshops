     #include <iostream>    
     #include <cstdlib>    
     #include <cmath>    
             
     // function declaration    
     int foo(int a, int b);    
     int bar(int a, int b);    
     double baz(double x);    
             
     // main    
     int main (int argc, char **argv)    
     {    
                 int ii, jj;    
                 ii =  0;    
                 jj = -1;    
             
                 foo(ii, jj);    
                 foo(jj, ii);    
                 baz(25.9);    
             
                 return EXIT_SUCCESS;    
     }    
             
     // foo    
     int foo(int a, int b)    
     {    
                 if (a*b!=0){     
                         return a/b + b/bar(a, b) + b/a;    
                 }else{     
                         return 0;    
                 }    
     }    
             
     // bar    
     int bar(int a, int b)    
     {    
                 unsigned int c = a;    
                     
                 return c + a - b;    
     }    
             
     // baz    
     double baz(double x)    
     {    
                 return std::sqrt(x);    
     } 
