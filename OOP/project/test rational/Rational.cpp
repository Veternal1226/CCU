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

    return quotient;
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
}
istream& operator >>(istream& InputStream, Rational& rational)
{
    BigInt NumeratorValue, DenominatorValue;
    int i, count, n=0, d=0;
    char buffer[100], *tmp, *temp;

    cin.getline(buffer, 100);
    if(strlen(buffer)==0)
        rational=Rational();
    else
    {
        for(i=0; i<strlen(buffer); i=i+1)
            if(buffer[i]=='/')
                count=count+1;
        if(count==0)
        {
            if(buffer[strlen(buffer)-1]=='!')
            {
                tmp = strtok(buffer, "\0 NULL");
                BigInt NumeratorValue(tmp);
                NumeratorValue.factorial();
                rational = Rational(NumeratorValue);
            }
            else
            {
                tmp = strtok(buffer, "\0 NULL");
                BigInt NumeratorValue(tmp);
                rational = Rational(NumeratorValue);
            }
        }
        else
        {
            tmp = strtok(buffer, "/");
            temp = strtok(NULL, "\0 NULL");
            if(tmp[strlen(tmp)-1]=='!')
            {
                tmp = strtok(tmp, "!");
                n=1;
            }
            if(temp[strlen(temp)-1]=='!')
            {
                temp = strtok(temp, "!");
                d=1;
            }
            BigInt NumeratorValue(tmp);
            BigInt DenominatorValue(temp);
            if(n==1 && d==1)
            {
                NumeratorValue.factorial();
                DenominatorValue.factorial();
                rational = Rational(NumeratorValue, DenominatorValue);
            }
            else if(n==1 && d==0)
            {
                NumeratorValue.factorial();
                rational = Rational(NumeratorValue, DenominatorValue);
            }
            else if(n==0 && d==1)
                {
                    DenominatorValue.factorial();
                    rational = Rational(NumeratorValue, DenominatorValue);
                }
            else
                rational = Rational(NumeratorValue, DenominatorValue);
        }
    }
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
