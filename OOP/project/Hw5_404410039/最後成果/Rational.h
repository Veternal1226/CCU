//¸ê¤u¤G 404410025 ±iºû®¦
#ifndef RATIONAL_H_
#define RATIONAL_H_
#include<iostream>
#include"BigInt.h"

using namespace std;
using namespace LWJ_bigint;
#define TRUE 1
#define FALSE 0
namespace Rational_C{
class Rational
{
public:
    Rational(BigInt numerator, BigInt denominator);
    Rational(BigInt wholeNumber);
    Rational(char* s) ;
    Rational();
    BigInt getNumerator() const;
    BigInt getDenominator() const;
    friend istream& operator >>(istream& InputStream, Rational& rational);
    friend ostream& operator <<(ostream& OutputStream,const Rational& Rational);
    friend const Rational operator *(const Rational& rational1,const Rational& rational2);
    friend const Rational operator /(const Rational& rational1,const Rational& rational2);
    friend bool operator ==(const Rational& rational1,const Rational& rational2);
    bool operator <(const Rational& rational2) const;
    bool operator <=(const Rational& rational2) const;
    bool operator >(const Rational& rational2) const;
    bool operator >=(const Rational& rational2) const;
    BigInt& operator [](int index);
    //friend const Rational normalization(Rational& rational);
    Rational normalization() ;
    friend const Rational operator +(const Rational& rational1,const Rational& rational2);
    friend const Rational operator -(const Rational& rational1,const Rational& rational2);
    friend const Rational operator -(const Rational& rational);

private:
    BigInt numerator;
    BigInt denominator;
};
}
#endif
