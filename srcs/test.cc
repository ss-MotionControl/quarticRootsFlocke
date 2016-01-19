#include "PolynomialRoots.hh"
#include <iostream>
#include <iomanip>

using namespace std ;
using namespace PolynomialRoots ;

double p1[4] = { 1, -6, 11, -6 } ; // 1, 2, 3
double p2[4] = { 1, -1000003, 3000002,-2000000 } ; // 1, 2, 1000000
double p3[4] = { 1, -1.000002e6, 2.000001e6, -2.0 } ; // 1/1000000, 2, 1000000
double p4[4] = { 1, -3, 1.00000003e8, -1.00000001e8 } ; // 1, 1+-10000*I
double p5[4] = { 1, -1.000002e6, 1.02000001e8, -1.000000010e14 } ; // 1000000, 1+-10000*I
double p6[4] = { 1, -2.000001000, 1.00000001e8,-100.000001 } ; // 1/1000000, 1+-10000*I
double p7[4] = { 1, -20000000001.0/1000000.0, 100000000019999/1000000.0, -99999999999999/1000000000000.0 } ; // 10000+-1/1000,-1/1000000

double q1[6] = { 1, -4, 1000000, -5999990, 10999999,-6000006 } ; // 1, 2, 3, -1+-I*1000
double q2[8] = { 1, -2, 1999993, -7999994, 1000000000019,
                 -5999979999998, 10999997999987, -6000012000006 } ; // 1, 2, 3, -1+-I*1000
double q3[8] = { 1, -9, 1000026, -11000014, 46999949, -96999941, 96000024,-36000036 } ;
double q4[10] = { 1, -7, 2000009, -17999971, 1000051999947,-11000028000057,
                  46999898000091,-96999881999929,96000047999952,-36000072000036 } ;
double q5[15] = { 1, 99, -2387, 59943, -1055726, 13296390, -156124010,
                  1314881010, -9434306855, 52871002635, -192808037939,
                  422986088679, -532888067052, 352235930508, -94133665296 } ;
static
void
do_test( double const p[4] ) {
  int    nr, nc ;
  double r1, r2, r3 ;
  solveCubic( p[0], p[1], p[2], p[3], r1, r2, r3, nr, nc ) ;
  cout.precision(8) ;
  valueType res1 = evalPoly( p, 3, r1, true ) ;
  cout << "\n\n"
       << p[0] << " * x^3 + "
       << p[1] << " * x^2 + "
       << p[2] << " * x + "
       << p[3] << " --> zeros" ;
  if ( nr == 3 ) {
    valueType res2 = evalPoly( p, 3, r2, true ) ;
    valueType res3 = evalPoly( p, 3, r3, true ) ;
    cout << "\nr1 = " << setw(8) << r1 << "\tp(r1) = " << res1
         << "\nr2 = " << setw(8) << r2 << "\tp(r2) = " << res2
         << "\nr3 = " << setw(8) << r3 << "\tp(r3) = " << res3
         << "\n" ;
  } else {
    std::complex<valueType> res2 = evalPolyC( p, 3, std::complex<valueType>(r2,r3), true ) ;
    std::complex<valueType> res3 = evalPolyC( p, 3, std::complex<valueType>(r2,-r3), true ) ;
    cout << "\nr1 = " << setw(20) << r1 << "\tp(r1)=" << res1
         << "\nr2 = " << setw(8) << r2 << " + " << setw(8) << r3 << "I\t|p(r2)|=" << std::norm(res2)
         << "\nr3 = " << setw(8) << r2 << " - " << setw(8) << r3 << "I\t|p(r3)|=" << std::norm(res3)
         << "\n" ;
  }
}

static
void
do_test1( double p[], int degree ) {
  double r[100], i[100] ;

  roots( p, degree, r, i ) ;

  cout.precision(8) ;
  cout << "\n\n" ;
  for ( int k = 0 ; k < degree ; ++k ) {
    std::complex<valueType> x   = std::complex<valueType>(r[k],i[k]) ;
    std::complex<valueType> res = evalPolyC( p, degree, std::complex<valueType>(r[k],i[k]), true ) ;
    cout << k << " x = " << setw(15) << x << " |p(x)|=" << std::norm(res) << "\n" ;
  }
  cout << "\n\n" ;
}

int
main() {
  do_test( p1 ) ;
  do_test( p2 ) ;
  do_test( p3 ) ;
  do_test( p4 ) ;
  do_test( p5 ) ;

  do_test( p6 ) ;
  do_test1( p6, 3 ) ;

  do_test( p7 ) ;
  do_test1( p7, 3 ) ;

  do_test1( q1, 5 ) ;
  do_test1( q2, 7 ) ;
  do_test1( q3, 7 ) ;
  do_test1( q4, 9 ) ;
  do_test1( q5, 14 ) ;
  return 0 ;
}

