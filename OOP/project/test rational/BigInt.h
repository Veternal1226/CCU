#ifndef LWJ_BIGINT
#define LWJ_BIGINT

#include <iostream>
using std::istream;
using std::ostream;

namespace LWJ_bigint
{
class BigInt
{
public:
    //constructor
    BigInt(void);
    BigInt(const char* data);
    BigInt(const long long int data);
    BigInt(const BigInt& iniObj);
    BigInt(int data,int arySize);
    //destructor
    ~BigInt();
    //accessor&mutator
    const int* getPos(void)const;
    const int getArraysize(void)const;
    const int getData(int input)const;
    const int getSign(void)const;
    const void setPos(int* newpos);
    const void setArraysize(int input);
    const void setData(int input,int value);
    const void setSign(int inputSign);
    //size check
    const void sizecheck(void);
    //factorial
    const void factorial(void);
    //operator
    friend const BigInt operator +(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator -(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator -(const BigInt& value);
    friend const BigInt operator *(const BigInt& value1,const int& value2);
    friend const BigInt operator *(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator /(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator %(const BigInt& value1,const BigInt& value2);
    friend const BigInt ADD(const BigInt& value1,const BigInt& value2);
    friend const BigInt SUB(const BigInt& value1,const BigInt& value2);
    friend const BigInt DIV(const BigInt& value1,const BigInt& value2,bool returntype);//returntype:0=/ 1=%
    friend const int findQ(const BigInt& value1,const BigInt& value2);
    //shift
    const void shiftright(void);
    const void shiftleft(void);
    //compare
    friend const int abscmp(const BigInt& value1,const BigInt& value2);
    friend const bool operator >(const BigInt& value1,const BigInt& value2);
    friend const bool operator >=(const BigInt& value1,const BigInt& value2);
    friend const bool operator <(const BigInt& value1,const BigInt& value2);
    friend const bool operator <=(const BigInt& value1,const BigInt& value2);
    friend const bool operator !=(const BigInt& value1,const BigInt& value2);
    friend const bool operator ==(const BigInt& value1,const BigInt& value2);
    //input
    friend ostream& operator <<(ostream& outputstream,const BigInt& value);
    //assignment
    BigInt& operator=(const BigInt& rtSide);
private:
    int* pos;//start position
    int arraysize;//array size
    int sign;//0=+ 1=-
};
}//LWJ_bigint
#endif //LWJ_BIGINT
