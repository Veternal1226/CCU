/** @file   Complex.cpp
  * @author team6 404420020 資工二 張庭瑋
  * @date   2017/6/12
*/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include"Rational.h"
#include"BigInt.h"
#include "Complex.h"

#define TRUE 1
#define FALSE 0
using namespace std ;
using namespace Rational_C ;
using namespace LWJ_bigint;

namespace CTW_Complex{
Complex::Complex(Rational r, Rational i):real(r), imaginary(i)
{  /* Intentionally empty */ }

Complex::Complex(Rational r):real(r), imaginary("0")
{  /* Intentionally empty */ }

Complex::Complex():real("0"), imaginary("0")
{  /* Intentionally empty */ }

const Complex operator +(const Complex& c1, const Complex& c2){
    Rational r, i ;
    r = c1.real + c2.real ;
    i = c1.imaginary + c2.imaginary ;
    return Complex(r,i) ;
}

const Complex operator -(const Complex& c1, const Complex& c2){
    Rational r, i ;
    r = c1.real - c2.real ;
    i = c1.imaginary - c2.imaginary ;
    return Complex(r,i) ;
}

const Complex operator *(const Complex& c1, const Complex& c2) {
    Rational r, i ;
    r = c1.real*c2.real - c1.imaginary*c2.imaginary ;
    i = c1.imaginary*c2.real + c1.real*c2.imaginary ;
    return Complex(r,i) ;
}

const Complex operator /(const Complex& c1, const Complex& c2){
    Rational r, i ;

    r = (c1.real*c2.real+c1.imaginary*c2.imaginary) / (c2.real*c2.real+c2.imaginary*c2.imaginary) ;
    i = (c1.imaginary*c2.real-c1.real*c2.imaginary) / (c2.real*c2.real+c2.imaginary*c2.imaginary) ;
    return Complex(r,i) ;
}

ostream& operator <<(ostream& outputStream, const Complex& c){

    outputStream << "real:\n" << c.real ;
    outputStream <<endl << endl << "imaginary:\n" << c.imaginary ;

    return outputStream ;
}

istream& operator >>(istream& inputStream, Complex& c){
    Rational r, i ;
    inputStream >> r >> i ;
    c.real = r ;
    c.imaginary = i ;

    return inputStream ;
}
}
