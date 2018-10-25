#include <iostream>
#include"BigInt.h"
#include"Rational.h"

using namespace LWJ_bigint;
using namespace Rational_C;

int main()
{
    Rational sum, difference, negative,  product, quotient, rational1, rational2;
    bool result;

    cout << "Enter first rational with the form a/b" << endl;
    cin >> rational1;
    cout << "Enter second rational with the form a/b" << endl;
    cin >> rational2;
    sum = rational1 + rational2;
    sum = normalization(sum);
    cout <<"First rational + second rational = " << sum << endl;
    difference = rational1 - rational2;
    difference = normalization(difference);
    cout <<"First rational - second rational = " << difference << endl;
    negative = -rational1;
    negative = normalization(negative);
    cout <<"-First rational = " << negative << endl;
    negative = -rational2;
    negative = normalization(negative);
    cout <<"-Second rational = " << negative << endl;
    product = rational1 * rational2;
    product = normalization(product);
    cout <<"First rational * second rational = " << product << endl;
    quotient = rational1 / rational2;
    quotient = normalization(quotient);
        cout <<"First rational / second rational = " << quotient << endl;
    result = rational1 < rational2;
    cout <<"First rational < second rational = " << result << endl;
    result = rational1 <= rational2;
    cout <<"First rational <= second rational = " << result << endl;
    result = rational1 > rational2;
    cout <<"First rational > second rational = " << result << endl;
    result = rational1 >= rational2;
    cout <<"First rational >= second rational = " << result << endl;

    cout << "rational1[0] = " << rational1[0] << " rational2[0] = " << rational2[0] << endl;
    cout << "rational1[1] = " << rational1[1] << " rational2[1] = " << rational2[1] << endl;

    return 0;
}
