//¸ê¤u¤G 404410025 ±iºû®¦

#include<iostream>
#include<cstring>
#include<cstdlib>
#include"Rational.h"
#include"BigInt.h"
#define TRUE 1
#define FALSE 0

using namespace LWJ_bigint;

namespace Rational_C
{
BigInt Rational::getNumerator() const
{
    return numerator;
}
BigInt Rational::getDenominator() const
{
    return denominator;
}
Rational::Rational(BigInt NumeratorValue, BigInt DenominatorValue):numerator(NumeratorValue),denominator(DenominatorValue)
{

}
Rational::Rational(BigInt WholeNumberValue):numerator(WholeNumberValue),denominator(1)
{

}
Rational::Rational(char *s)
{
    Rational temp ;
    char s2[1000] ;
    strcpy(s2,s) ;
    char *pch = strtok(s2,"/") ;
    temp.numerator = pch ;
    pch = strtok(NULL,"/") ;
    if(pch != NULL)
        temp.denominator = pch ;
    else temp.denominator = 1 ;
    temp.normalization() ;
    numerator = temp.numerator ;
    denominator = temp.denominator ;
}

Rational::Rational()
{
    BigInt n("0"),d("1");
    numerator=n;
    denominator=d;
}
const Rational operator +(const Rational& rational1,const Rational& rational2)
{
    BigInt numeratorValue1(rational1.getNumerator()),denominatorValue1(rational1.getDenominator());
    BigInt numeratorValue2(rational2.getNumerator()),denominatorValue2(rational2.getDenominator());
    BigInt SumNumerator, SumDenominator;

    SumNumerator = numeratorValue1*denominatorValue2 + numeratorValue2*denominatorValue1;
    SumDenominator = denominatorValue1*denominatorValue2;

    Rational sum(SumNumerator, SumDenominator);

    return sum;
}
const Rational operator -(const Rational& rational1,const Rational& rational2)
{
    BigInt numeratorValue1(rational1.getNumerator()),denominatorValue1(rational1.getDenominator());
    BigInt numeratorValue2(rational2.getNumerator()),denominatorValue2(rational2.getDenominator());
    BigInt SubNumerator, SubDenominator;

    SubNumerator = numeratorValue1*denominatorValue2 - numeratorValue2*denominatorValue1;
    SubDenominator = denominatorValue1*denominatorValue2;

    Rational sub(SubNumerator, SubDenominator);

    return sub;
}
const Rational operator -(const Rational& rational)
{
    Rational negative(-rational.getNumerator(), rational.getDenominator());

    return negative;
}
const Rational operator *(const Rational& rational1,const Rational& rational2)
{
    Rational product;

    product.numerator=rational1.numerator * rational2.numerator;
    product.denominator=rational1.denominator * rational2.denominator;

    return product;
}
const Rational operator /(const Rational& rational1,const Rational& rational2)
{
    Rational quotient;

    quotient.numerator=rational1.numerator * rational2.denominator;
    quotient.denominator=rational1.denominator * rational2.numerator;

    return quotient.normalization();
}
bool operator ==(const Rational& rational1,const Rational& rational2)
{
    if((rational1.numerator*rational2.denominator) == (rational1.denominator*rational2.numerator))
        return TRUE;
    else
        return FALSE;
}
bool Rational:: operator <(const Rational& rational2) const
{
    if((numerator*rational2.denominator) < (denominator*rational2.numerator))
        return TRUE;
    else
        return FALSE;
}
bool Rational:: operator <=(const Rational& rational2) const
{
    if(((numerator*rational2.denominator) < (denominator*rational2.numerator)) || ((numerator*rational2.denominator) == (denominator*rational2.numerator)))
        return TRUE;
    else
        return FALSE;
}
bool Rational:: operator >(const Rational& rational2) const
{
    if((numerator*rational2.denominator) > (denominator*rational2.numerator))
        return TRUE;
    else
        return FALSE;
}
bool Rational:: operator >=(const Rational& rational2) const
{
    if(((numerator*rational2.denominator) > (denominator*rational2.numerator)) || ((numerator*rational2.denominator) == (denominator*rational2.numerator)))
        return TRUE;
    else
        return FALSE;
}
BigInt& Rational:: operator [](int index)
{
    if(index==0)
        return numerator;
    else if(index==1)
        return denominator;
    else
    {
        cout <<"Illegal index\n";
        exit(1);
    }
}
/*
const Rational normalization(Rational& rational)
{
    long long int O(0);
    BigInt absnumerator, absdenominator, zero(O);
    BigInt i, j, k;

    absnumerator=(rational.getNumerator()>zero)? rational.getNumerator(): -rational.getNumerator();
    absdenominator=(rational.getDenominator()>zero)? rational.getDenominator(): -rational.getDenominator();
    j=absnumerator;
    k=absdenominator;
    if(rational.numerator==zero)
    {
        rational = Rational(zero);
        return rational;
    }
    else
    {
        j=(j>k)? j: k;
        k=(j<k)? j: k;
        while(k!=zero)
        {
            j=j%k;
            i=k;
            k=j;
            j=i;
        }
        rational.numerator=rational.numerator/j;
        rational.denominator=rational.denominator/j;
        if(rational.getDenominator()<zero)
        {
            rational.numerator=-rational.numerator;
            rational.denominator=-rational.denominator;
        }
        return rational;
    }
}*/
Rational Rational::normalization() {
    bool n_sign, d_sign ;
    BigInt a, b, temp ;
    a = numerator ; b = denominator ;
    if(a < b){
        temp = a ;
        a = b ;
        b= temp ;
    }

    while(a != "0"){
        a = a%b ;
        temp = a ;
        a = b ;
        b = temp ;
    }

    numerator = numerator/b ;
    denominator = denominator/b ;
    return Rational(numerator,denominator) ;
}
istream& operator >>(istream& InputStream, Rational& rational)
{
    BigInt NumeratorValue, DenominatorValue;
    char s[1000] ;
    char *pch ;

    InputStream >> s ;
    pch = strtok(s, "/") ;
    rational.numerator = pch ;
    pch = strtok(NULL,"/") ;
    if(pch != NULL)
        rational.denominator = pch ;
    else rational.denominator = 1 ;

    return InputStream ;

}

ostream& operator <<(ostream& OutputStream,const Rational& rational)
{
    OutputStream << rational.numerator;

    if(rational.denominator!=1)
    {
        OutputStream <<"/";
        OutputStream <<rational.denominator;
    }
    return OutputStream;
}
}
