#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <cmath>
#include <iostream>
using K = CGAL::Exact_predicates_inexact_constructions_kernel; using P2 = K::Point_2;
double orient_d(double ax,double ay,double bx,double by,double cx,double cy){ return (bx-ax)*(cy-ay)-(by-ay)*(cx-ax); }
int main(){ const double u = std::ldexp(1.0,-53); int wrong=0, total=0;
 for(int i=0;i<256;i++) for(int j=0;j<256;j++){ double px=0.5+i*u, py=0.5+j*u; double d=orient_d(px,py,12,12,24,24);
   int sd=(d>0)-(d<0); int se=(int)CGAL::orientation(P2(px,py),P2(12,12),P2(24,24)); total++; if(sd!=se) wrong++; }
 std::cout<<wrong<<" of "<<total<<" naive double orientations have the wrong sign\n"; }
