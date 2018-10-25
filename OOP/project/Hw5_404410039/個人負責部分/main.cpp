
/*
    by 404410039 李維哲
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "BigInt.h"

using namespace std;

int main()
{
    using LWJ_bigint::BigInt;
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    BigInt *b = new BigInt(1618033988);
    BigInt x("100!"),y("520!");
    c=a+(*b);
    cout<<a<<"+"<<*b<<"="<<endl<<c<<endl;
    c=a-(*b);
    cout<<a<<"-"<<*b<<"="<<endl<<c<<endl;
    c=a*(*b);
    cout<<a<<"*"<<*b<<"="<<endl<<c<<endl;
    c=a/(*b);
    cout<<a<<"/"<<*b<<"="<<endl<<c<<endl;
    c=a%(*b);
    cout<<a<<"%"<<*b<<"="<<endl<<c<<endl;
    cout<<"100!="<<endl<<x<<endl;
    cout<<"520!="<<endl<<y<<endl;
    return 0;
}


