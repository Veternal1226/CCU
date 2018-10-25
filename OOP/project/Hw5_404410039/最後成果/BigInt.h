
/*
    by 404410039 李維哲
*/

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
    BigInt(const char* data);           //constructor for string. ex:a("321")
    BigInt(const long long int data);   //constructor for int ex:a(321)
    BigInt(const BigInt& iniObj);       //copy constructor
    BigInt(int data,int arySize);       //declare size but no data

    //destructor
    ~BigInt();

    //accessor&mutator
    const int* getPos(void)const;       //return pos
    const int getArraysize(void)const;  //return arraysize
    const int getData(int input)const;  //return pos[input]
    const int getSign(void)const;       //return sign
    const void setPos(int* newpos);     //set pos=newpos
    const void setArraysize(int input); //set arraysize=input
    const void setData(int input,int value);    //set pos[input]=value
    const void setSign(int inputSign);  //set sign=inputSign

    //size check
    const void sizecheck(void);         //check check ex: 000123(size=6)->123(size=3)

    //factorial
    const void factorial(void);         //factorialize the bigint
        //can be call normally or insert in constructor's string
        //ex: a(500);a.factorial();  AND a("500!") are both acceptable

    //operator
    friend const BigInt operator +(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator -(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator -(const BigInt& value);
    friend const BigInt operator *(const BigInt& value1,const int& value2);
    friend const BigInt operator *(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator /(const BigInt& value1,const BigInt& value2);
    friend const BigInt operator %(const BigInt& value1,const BigInt& value2);
        /*
            pre:    just use the operator as normal operator with BigInt
            post    return result(BigInt)
                p.s.if use negitive%negitive the % always  do positive%postive's result
        */

    //calculate function
    friend const BigInt ADD(const BigInt& value1,const BigInt& value2);
    friend const BigInt SUB(const BigInt& value1,const BigInt& value2);
    friend const BigInt DIV(const BigInt& value1,const BigInt& value2,bool returntype);//returntype:0=/ 1=%
    friend const int findQ(const BigInt& value1,const BigInt& value2);
        //ues to implement operator. user should not call these function(result may be wrong)

    //shift
    const void shiftright(void);
    const void shiftleft(void);
        /*use to shift BigInt.
            ex:a(123456);
            r=a.shiftright();   //r=12345
            l=a.shiftleft();    //l=1234560
        */

    //compare
    friend const int abscmp(const BigInt& value1,const BigInt& value2);
    friend const bool operator >(const BigInt& value1,const BigInt& value2);
    friend const bool operator >=(const BigInt& value1,const BigInt& value2);
    friend const bool operator <(const BigInt& value1,const BigInt& value2);
    friend const bool operator <=(const BigInt& value1,const BigInt& value2);
    friend const bool operator !=(const BigInt& value1,const BigInt& value2);
    friend const bool operator ==(const BigInt& value1,const BigInt& value2);
        /*
            pre:    just use the operator as normal operator with BigInt
            post:   return compare result(bool)
                p.s.abscmp just compare the value not consider the sign
                    a>b:return 1    a==b:return 0 a<b:return -1
                    e.x.    r=abscmp(-123456,123456)    //r=0
        */
    //input
    friend ostream& operator <<(ostream& outputstream,const BigInt& value);
        //just use the operator as normal operator with BigInt
    //assignment
    BigInt& operator=(const BigInt& rtSide);
        //just use the operator as normal operator with BigInt
private:
    int* pos;       //start position
    int arraysize;  //array size
    int sign;       //0=+ 1=-
};
}//LWJ_bigint
#endif //LWJ_BIGINT
