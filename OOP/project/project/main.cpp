
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
    BigInt xl("100!"),yl("520!");
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
    cout<<"100!="<<endl<<xl<<endl;
    cout<<"520!="<<endl<<yl<<endl;
    /*
    BigInt x("314159265358979323846264338327950288419716939937510"), ad(a);
    BigInt *y = new BigInt(9586958);
    BigInt *su = new BigInt(30);
    BigInt z("314159265358979323846264338327950288419716949524468");
    ad=x+(*y);
    cout<<x<<"+"<<*y<<"="<<endl<<ad<<endl;
    *su=ad-z;
    cout<<ad<<"-"<<z<<"="<<endl<<*su<<endl;
    */
    return 0;
}


