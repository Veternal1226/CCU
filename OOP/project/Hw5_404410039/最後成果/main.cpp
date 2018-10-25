/** @file   main.cpp
  * @author team6 404420020 資工二 張庭瑋
  * @date   2017/6/12
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "BigInt.h"
#include "Rational.h"
#include "Complex.h"
#define TRUE 1
#define FALSE 0
using namespace std;
using namespace LWJ_bigint;
using namespace CTW_Complex ;
using namespace Rational_C ;
int main()
{

    Complex c1("1/3","-6/17"), c2("81!/320!","128!/520!") ;
    cout << c1/c2;


    return 0;
}
