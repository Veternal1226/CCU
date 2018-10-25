#include <iostream>
#include <cstring>
#include <cstdlib>
#define XXX -999
//for represent non-exist digit ->can't use const
using namespace std;

/*
    by 李維哲 404410039 資工二
*/

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
    //input
    friend ostream& operator <<(ostream& outputstream,const BigInt& value);
    //assignment
    BigInt& operator=(const BigInt& rtSide);
private:
    int* pos;//start position
    int arraysize;//array size
    int sign;//0=+ 1=-
};

//non-member
const BigInt operator +(const BigInt& value1,const BigInt& value2);
const BigInt operator -(const BigInt& value1,const BigInt& value2);

int main()
{
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    BigInt *b = new BigInt(1618033988);
    //BigInt a("54321"),c(a);
    //BigInt *b=new BigInt(12345);
            /*test
            cout<<a<<endl;
            cout<<"size="<<a.getArraysize()<<endl;
            cout<<*b<<endl;
            cout<<"size="<<b->getArraysize()<<endl;
            cout<<c<<endl;
            cout<<"size="<<c.getArraysize()<<endl;
            */
    c = a + *b;
    cout << a <<"+"<< *b <<"="<< c << endl;
    c = a - *b;
    cout << a <<"-"<< *b <<"="<< c << endl;
    return 0;
}

/*constructor*/
BigInt::BigInt(void):arraysize(1),sign(0)
{
    /*default:size=1,sign=0*/
    pos=new int[arraysize];
    pos[0]=0;
}
BigInt::BigInt(const char* data):arraysize(strlen(data))
{
    /*for string data*/
    pos=new int[arraysize];
    int i;
    sign=0;
    for(i=0;i<arraysize;i++)
    {
        if(data[i]=='-')
        {
            sign=1;
            pos[i]=XXX;
        }
        else
        {
            pos[i]=data[i]-'0';
        }
    }
}
BigInt::BigInt(const long long int data)
{
    /*for int data*/
    int counter,i;
    int* temppos;
    long long int temp;
    sign=0;
    if(data<0)//if data<0
    {
        sign=1;
        temp=-data;
    }
    else
        temp=data;
    temppos=new int[20];//2^64=20bits
    counter=0;
    while(temp!=0)
    {
        temppos[counter]=temp%10;//cout<<temppos[counter]<<' '<<endl;
        temp=temp/10;//cout<<temp<<' ';
        counter++;
    }
    pos=new int[counter];
    for(i=0;i<counter;i++)//reverse array
    {
        pos[i]=temppos[counter-i-1];
    }
    arraysize=counter;
}
BigInt::BigInt(int data,int arySize):arraysize(arySize),sign(0)
{
    /*constructor with size but no data*/
    pos=new int[arraysize];
}

/*copy constructor*/
BigInt::BigInt(const BigInt& iniObj):arraysize(iniObj.getArraysize()),sign(iniObj.getSign())
{
    pos=new int[arraysize];
    for(int i=0;i<arraysize;i++)
        pos[i]=iniObj.pos[i];
}

/*destructor*/
BigInt::~BigInt()
{
    delete [] pos;
}

/*mutator*/
const void BigInt::setPos(int* newpos)
{
    /*change Pos value*/
    pos=newpos;
    return;
}
const void BigInt::setArraysize(int input)
{
    /*change Arraysize value*/
    arraysize=input;
    return;
}
const void BigInt::setData(int input,int value)
{
    /*change the data which is in array*/
    pos[input]=value;
    return;
}
const void BigInt::setSign(int inputSign)
{
    /*change sign*/
    sign=inputSign;
    return;
}
//

/*accessor*/
const int* BigInt::getPos(void)const
{
    /*return pos value(address)*/
    return pos;
}
const int BigInt::getArraysize(void)const
{
    /*return arraySize value*/
    return arraysize;
}
const int BigInt::getData(int input)const
{
    /*return data in array at target pos*/
    return pos[input];
}
const int BigInt::getSign(void)const
{
    /*return the sign*/
    return sign;
}
//

/*io function*/
ostream& operator <<(ostream& outputstream,const BigInt& value)
{
    int i;
    if(value.sign)
        outputstream<<'-';
    for(i=0;i<value.arraysize;i++)
    {
        if(value.pos[i]!=XXX)
        {
            //if(value.pos[i]<0)
                //outputstream<<-value.pos[i];
            //else
                outputstream<<value.pos[i];
        }
    }
    return outputstream;
}

//assignment
BigInt& BigInt::operator=(const BigInt& rtSide)
{
    if(this==&rtSide)
        return *this;
    else
    {
        arraysize=rtSide.arraysize;
        delete [] pos;
        pos=new int[arraysize];
        for(int i=0;i<arraysize;i++)
            pos[i]=rtSide.pos[i];
    }
    return *this;
}

//add:addition
const BigInt operator +(const BigInt& value1,const BigInt& value2)
{
    /*  pre:two bigint
        post:result*/
    int maxdig;//max digit
    int i,carry,temp;
    int size1=value1.getArraysize();
    int size2=value2.getArraysize();
    //int sign1=value1.getSign();
    //int sign2=value2.getSign();
    if(size1>size2)
        maxdig=size1+1;
    else
        maxdig=size2+1;
    //cout<<size1<<" "<<size2<<" "<<maxdig<<endl;
    BigInt result(0,maxdig);
    for(i=0;i<maxdig;i++)
    {
        result.setData(i,XXX);
    }
    carry=0;
    for(i=0;i<maxdig-1;i++)
    {
        if(i>size2-1)
        {
            temp=value1.getData(size1-i-1)+carry;
        }
        else if(i>size1-1)
        {
            temp=value2.getData(size2-i-1)+carry;
        }
        else
        {
            temp=value1.getData(size1-i-1)+value2.getData(size2-i-1)+carry;
        }
        if(carry)
            carry=0;
        if(temp>=10)
        {
            carry=temp/10;
            temp=temp%10;
        }
        //cout<<i<<" "<<temp<<endl;
        result.setData(maxdig-i-1,temp);
        //cout<<temp<<" ";
    }
    return result;
}

//sub:subtraction
const BigInt operator -(const BigInt& value1,const BigInt& value2)
{
    /*  pre:two bigint
        post:result*/
    int maxdig;//max digit
    int i,bought,temp;
    int size1=value1.getArraysize();
    int size2=value2.getArraysize();
    //int sign1=value1.getSign();
    //int sign2=value2.getSign();
    if(size1>size2)
        maxdig=size1+1;
    else
        maxdig=size2+1;
    //cout<<size1<<" "<<size2<<" "<<maxdig<<endl;
    BigInt result(0,maxdig);
    for(i=0;i<maxdig;i++)
    {
        result.setData(i,XXX);
    }
    bought=0;
    for(i=0;i<maxdig-1;i++)
    {
        if(i>size2-1)
        {
            temp=value1.getData(size1-i-1)-bought;
        }
        else if(i>size1-1)
        {
            temp=value2.getData(size2-i-1)-bought;
        }
        else
        {
            temp=value1.getData(size1-i-1)-value2.getData(size2-i-1)-bought;
        }
        if(bought)
            bought=0;
        if(temp<0)
        {
            while(temp<0)
            {
                temp=temp+10;
                bought++;
            }
        }
        //cout<<i<<" "<<temp<<endl;
        result.setData(maxdig-i-1,temp);
        //cout<<temp<<" ";
    }
    return result;
}
