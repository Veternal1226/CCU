/** @file   Complex.h
  * @author team6 404420020 資工二 張庭瑋
  * @date   2017/6/12
*/

#ifndef CTW_COMPLEX
#define CTW_COMPLEX

#include<iostream>
#include<cstring>
#include<cstdlib>
#include"Rational.h"
#include"BigInt.h"
#include "Complex.h"

#define TRUE 1
#define FALSE 0
using namespace std ;
using namespace LWJ_bigint;
using namespace Rational_C ;

namespace CTW_Complex{
class Complex{
public:
    // constructor
    Complex(Rational r, Rational i) ;
    Complex(Rational r) ;
    Complex() ;

    // operator overloading
    friend const Complex operator +(const Complex& c1, const Complex& c2) ;
    friend const Complex operator -(const Complex& c1, const Complex& c2) ;
    friend const Complex operator *(const Complex& c1, const Complex& c2) ;
    friend const Complex operator /(const Complex& c1, const Complex& c2) ;

    friend ostream& operator <<(ostream& outpuStream, const Complex& c) ;
    friend istream& operator >>(istream& inputStream, Complex& c) ;

private:
    Rational real, imaginary ;

};
}
#endif
