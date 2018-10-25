#include<iostream>
#include <cstring>
#include <cstdlib>
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
#include "BigInt.h"

//using namespace std;


namespace LWJ_bigint
{
/*constructor*/
BigInt::BigInt(void):arraysize(1),sign(0)
{
    /*default:size=1,sign=0*/
    pos=new int[arraysize];
    pos[0]=0;
}
BigInt::BigInt(const char* data)
{
    /*for string data*/

    int i,len,flag,inputpos;
    sign=0;
    flag=0;
    inputpos=1;//+- assign pos is different by i->direct find now input position
    len=strlen(data);
    for(i=0;i<len;i++)
    {
        if(data[i]=='-')
        {
            sign=1;
            //pos[i]=0;
        }
        else if (data[i]!='-'&&data[i]!=0&&flag==0)
        {
            flag=1;
            arraysize=strlen(data)-i;
            pos=new int[arraysize];
            pos[arraysize-inputpos]=data[i]-'0';
            inputpos++;
        }
        else
        {
            pos[arraysize-inputpos]=data[i]-'0';
            inputpos++;
        }
    }

    if(data[len-1]=='!')
    {
        shiftright();
        factorial();
    }
    sizecheck();
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
    for(i=0;i<counter;i++)//copy array
    {
        pos[i]=temppos[i];
    }
    arraysize=counter;
}
BigInt::BigInt(int data,int arySize):arraysize(arySize),sign(data)
{
    /*constructor with size but no data*/
    int i;
    pos=new int[arraysize];
    for(i=0;i<arraysize;i++)
    {
        pos[i]=0;
    }
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

//size check
const void BigInt::sizecheck(void)
{
    int i,maxpos=1;
    for(i=arraysize;i>=1;i--)
    {
        if(pos[i-1]!=0)
        {
            maxpos=i;
            break;
        }
    }
    arraysize=maxpos;
}

/*io function*/
ostream& operator <<(ostream& outputstream,const BigInt& value)
{
    int i;
    int flag=0;
    BigInt temp;
    if(abscmp(value,temp)==0)//if bigint(0) print '0'
    {
        outputstream<<0;
        return outputstream;
    }
    if(value.sign==1)
        outputstream<<'-';
    for(i=value.arraysize-1;i>=0;i--)
    {
        if(value.pos[i]!=0)
            flag=1;
        if(flag)
        {
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
        sign=rtSide.sign;
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
        post:add result*/
        //cout<<value1<<"+"<<value2<<endl;
    int maxdig;
    if(value1.arraysize>value2.arraysize)
        maxdig=value1.arraysize+1;
    else
        maxdig=value2.arraysize+1;
    BigInt result(0,maxdig);
    if(value1.sign==value2.sign)//1+2=1+2 -1+-2=-1+-2
    {
        result=ADD(value1,value2);
    }
    else
    {
        if(value1.sign==0&&value2.sign==1)//1+-2=1-2
        {
            result=SUB(value1,-value2);
        }
        else//-1+2=-1--2
        {
            result=SUB(value1,-value2);
        }
    }
    result.sizecheck();
    return result;
}

//sub:subtraction
const BigInt operator -(const BigInt& value1,const BigInt& value2)
{
    /*  pre:two bigint
        post:sub result*/
        //cout<<value1<<"-"<<value2<<endl;
    int maxdig;
    if(value1.arraysize>value2.arraysize)
        maxdig=value1.arraysize+1;
    else
        maxdig=value2.arraysize+1;
    BigInt result(0,maxdig);
    if(value1.sign==value2.sign)//1-2=1-2 -1--2=-1--2
    {
        result=SUB(value1,value2);
    }
    else
    {
        if(value1.sign==0&&value2.sign==1)//1--2=1+2
        {
            result=ADD(value1,-value2);
        }
        else//-1-2=-1+-2
        {
            result=ADD(value1,-value2);
        }
    }
    result.sizecheck();
    return result;
}

//add:addition
const BigInt ADD(const BigInt& value1,const BigInt& value2)
{
    /*  pre:two bigint
        post:add result*/
        //cout<<value1<<"+"<<value2<<endl;
    int maxdig;//max digit
    int i,carry,temp;
    if(value1.arraysize>value2.arraysize)
        maxdig=value1.arraysize+1;
    else
        maxdig=value2.arraysize+1;
    BigInt result(value1.sign,maxdig);
    for(i=0;i<maxdig;i++)
    {
        result.pos[i]=0;
    }
    carry=0;
    for(i=0;i<maxdig-1;i++)
    {
        if(i>value2.arraysize-1)
        {
            temp=value1.pos[i]+carry;
        }
        else if(i>value1.arraysize-1)
        {
            temp=value2.pos[i]+carry;
        }
        else
        {
            temp=value1.pos[i]+value2.pos[i]+carry;
        }
        if(carry)
            carry=0;
        if(temp>=10)
        {
            carry=temp/10;
            temp=temp%10;
        }
        result.pos[i]=temp;
    }
    if(carry)
        result.pos[i]=carry;
    return result;
}
//sub:subtraction
const BigInt SUB(const BigInt& value1,const BigInt& value2)
{
    /*  pre:two bigint
        post:sub result*/
        //cout<<value1<<"-"<<value2<<endl;
    int maxdig;//max digit
    int i,bought,temp,tempsign;
    if(value1.arraysize>value2.arraysize)
        maxdig=value1.arraysize+1;
    else
        maxdig=value2.arraysize+1;
    if(value1.sign==0)//+ - +
    {
        if(abscmp(value1,value2)==-1)//+small-+big
        {
            return -(SUB(value2,value1));
        }
        else//+big-+small
        {
            tempsign=0;
        }
    }
    else//- - -
    {
        if(abscmp(value1,value2)==-1)//-small--big
        {
            return -(SUB(value2,value1));
        }
        else//-big--small
        {
            tempsign=1;
        }
    }
    BigInt result(tempsign,maxdig);
    for(i=0;i<maxdig;i++)
    {
        result.pos[i]=0;
    }
    bought=0;
    for(i=0;i<maxdig-1;i++)
    {
        if(i>value2.arraysize-1)
        {
            temp=value1.pos[i]-bought;
        }
        else if(i>value1.arraysize-1)
        {
            temp=value2.pos[i]-bought;
        }
        else
        {
            temp=value1.pos[i]-value2.pos[i]-bought;
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
        result.pos[i]=temp;
    }
    return result;
}
//neg:negation
const BigInt operator -(const BigInt& value)
{
    /*  pre:one bigint
        post:neg result*/
        //cout<<"-"<<value<<endl;
    BigInt result(value);
    if(value.getSign())//originate sign is -
        result.setSign(0);
    else
        result.setSign(1);
    return result;
}

//conpare
const int abscmp(const BigInt& value1,const BigInt& value2)
{
    int i,maxdig;
    BigInt temp1(value1);
    BigInt temp2(value2);
    temp1.sizecheck();
    temp2.sizecheck();
    if(temp1.arraysize>temp2.arraysize)
        return 1;
    else if(temp1.arraysize<temp2.arraysize)
        return -1;
    else
    {
        maxdig=temp1.arraysize;
        for(i=maxdig-1;i>=0;i--)
        {
            if(temp1.pos[i]>temp2.pos[i])
                return 1;
            else if(temp1.pos[i]<temp2.pos[i])
                return -1;
        }
        return 0;
    }
}

const bool operator >(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return true;
    else if(value1.sign==1&&value2.sign==0)
        return false;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return false;
        else
            return false;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return true;
        else
            return false;
    }
}
const bool operator >=(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return true;
    else if(value1.sign==1&&value2.sign==0)
        return false;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return false;
        else
            return true;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return true;
        else
            return true;
    }
}
const bool operator <(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return false;
    else if(value1.sign==1&&value2.sign==0)
        return true;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return true;
        else
            return false;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return false;
        else
            return false;
    }
}
const bool operator <=(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return false;
    else if(value1.sign==1&&value2.sign==0)
        return true;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return true;
        else
            return true;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return false;
        else
            return true;
    }
}
const bool operator !=(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return true;
    else if(value1.sign==1&&value2.sign==0)
        return true;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return true;
        else
            return false;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return true;
        else if(abscmpResult==-1)
            return true;
        else
            return false;
    }
}
const bool operator ==(const BigInt& value1,const BigInt& value2)
{
    int abscmpResult;
    if(value1.sign==0&&value2.sign==1)
        return false;
    else if(value1.sign==1&&value2.sign==0)
        return false;
    else if(value1.sign==0&&value2.sign==0)
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return false;
        else
            return true;
    }
    else
    {
        abscmpResult=abscmp(value1,value2);
        if(abscmpResult==1)
            return false;
        else if(abscmpResult==-1)
            return false;
        else
            return true;
    }
}

const BigInt operator *(const BigInt& value1,const int& value2)
{
    int i,maxdig,temp,carry;
    maxdig=value1.arraysize+1;
    BigInt result(0,maxdig);
    carry=0;
    for(i=0;i<maxdig;i++)
    {
        if(i==value1.arraysize)
            temp=carry;
        else
            temp=value1.pos[i]*value2+carry;
        if(carry)
            carry=0;
        if(temp>=10)
        {
            carry=temp/10;
            temp=temp%10;
        }
            //cout<<i<<" "<<temp<<endl;
        result.pos[i]=temp;
    }
    result.sizecheck();
    return result;
}

const BigInt operator *(const BigInt& value1,const BigInt& value2)
{
    int i,j,maxdig,carry,resultsign;
    maxdig=value1.arraysize+value2.arraysize;
    if(value1.sign==value2.sign)
        resultsign=0;//+
    else
        resultsign=1;//-
    BigInt result(resultsign,maxdig);
    for(i=0;i<maxdig;i++)
    {
        result.pos[i]=0;
    }
    for(i=0;i<value1.arraysize;i++)
    {
        for(j=0;j<value2.arraysize;j++)
        {
            result.pos[i+j]+=value1.pos[i]*value2.pos[j];
        }
    }
    carry=0;
    for(i=0;i<maxdig;i++)
    {
        result.pos[i]=result.pos[i]+carry;
        if(carry)
            carry=0;
        if(result.pos[i]>=10)
        {
            carry=result.pos[i]/10;
            result.pos[i]=result.pos[i]%10;
        }
            //cout<<i<<" "<<result.pos[i]<<endl;
    }
    result.sizecheck();
    return result;
}

const BigInt operator /(const BigInt& value1,const BigInt& value2)
{
    int maxdig,resultsign;
    if(value1.sign==value2.sign)
        resultsign=0;//+
    else
        resultsign=1;//-
    if(value1.arraysize<value2.arraysize)
    {
        BigInt result(resultsign,1);//return 0
        return result;
    }
    else
    {
        maxdig=value1.arraysize-value2.arraysize+1;
    }
    BigInt result(resultsign,maxdig);
    result=DIV(value1,value2,0);
    result.sizecheck();
    return result;
}
const BigInt operator %(const BigInt& value1,const BigInt& value2)
{
    int maxdig,resultsign;
    if(value1.sign==value2.sign)
        resultsign=0;//+
    else
        resultsign=1;//-
    if(value1.arraysize<value2.arraysize)
    {
        return value1;
    }
    else
    {
        maxdig=value1.arraysize-value2.arraysize+1;
    }
    BigInt result(resultsign,maxdig);
    result=DIV(value1,value2,1);
    result.sizecheck();
    return result;
}
const BigInt DIV(const BigInt& value1,const BigInt& value2,bool returntype)
{
    //returntype:0=/ 1=%
    int maxdig,delta,i,Q,resultsign;
    maxdig=value1.arraysize-value2.arraysize+1;
    if(value1.sign==value2.sign)
        resultsign=0;//+
    else
        resultsign=1;//-
    BigInt result(resultsign,maxdig);
    delta=value1.arraysize-value2.arraysize;
    BigInt t_value1(value1),t_value2(value2);
    if(t_value1.sign==1)//always +
        t_value1.setSign(0);
    if(t_value2.sign==1)
        t_value2.setSign(0);
    for(i=0;i<delta;i++)
    {
        t_value2.shiftleft();
    }
        //cout<<t_value1<<endl<<t_value2<<endl<<endl;
    for(i=delta;i>=0;i--)
    {
        Q=findQ(t_value1,t_value2);
            //cout<<Q<<endl;
            //cout<<t_value1<<endl<<t_value2<<endl;
        result.pos[i]=Q;
        t_value1=t_value1-(t_value2*Q);
        t_value2.shiftright();
            //cout<<t_value1<<endl;
    }
    result.sizecheck();
    t_value1.sizecheck();
    if(returntype)
        return t_value1;
    else
        return result;
}

const int findQ(const BigInt& value1,const BigInt& value2)
{
    int i;
    for(i=1;i<=10;i++)
    {
        if(abscmp(value2*i,value1)==1)
        {
            return i-1;
        }
        if(abscmp(value2*i,value1)==0)
        {
            return i;
        }
    }
    //if(i==11)
        //cout<<"error"<<endl;
    return i-1;
}

const void BigInt::shiftright(void)
{
    int i;
    for(i=1;i<arraysize;i++)
    {
        pos[i-1]=pos[i];
    }
    pos[arraysize-1]=0;
    arraysize=arraysize-1;
    return;
}

const void BigInt::shiftleft(void)
{
    int i;
    int* temp;
    temp=new int[arraysize+1];//deu to pos[arraytsize] is not declare by pos ->new
    temp[0]=0;
    for(i=arraysize-1;i>=0;i--)
    {
        temp[i+1]=pos[i];
    }
    pos=temp;
    arraysize=arraysize+1;
    return;
}

const void BigInt::factorial(void)
{
    BigInt level(*this);
    level.setSign(0);
    BigInt temp(this->sign,100000);
    temp.setData(0,1);
    BigInt i(0,100);
    i.setData(0,1);//i=1;
    BigInt adder(0,1);
    adder.setData(0,1);//adder=1 use for i=i+1
    while(abscmp(level,i)!=-1)//level>=i
    {
        temp=temp*i;
        //cout<<i<<'\t'<<temp<<endl;
        i=i+adder;
    }
    *this=temp;
        //cout<<*this;
}
}//LWJ_bigint
