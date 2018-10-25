#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

/*
    by 李維哲 404410039 資工二
*/

class Rational
{
public:
    //constructor
    Rational(void);
    Rational(int wholeNumber);
    Rational(int numeValue,int denoValue);
    //accessor&mutator
    const int getNumerator(void)const;
    const int getDenominator(void)const;
    const void setNumerator(int input);
    const void setDenominator(int input);
    //normalize
    const void normalize(void);

    //friend
    friend const Rational operator *(const Rational& value1,const Rational& value2);
    friend const Rational operator /(const Rational& value1,const Rational& value2);
    friend bool operator ==(const Rational& value1,const Rational& value2);

    //member
    bool operator <(const Rational& value2)const;
    bool operator <=(const Rational& value2)const;
    bool operator >(const Rational& value2)const;
    bool operator >=(const Rational& value2)const;
    int& operator[](int index);

    //io:friend
    friend ostream& operator <<(ostream& outputstream,const Rational& value);
    friend istream& operator >>(istream& inputstream,Rational& value);

private:
    int nume;//numerator
    int deno;//denominator
};

//non-member
const void normalize(int& numeValue,int& denoValue);
const Rational operator +(const Rational& value1,const Rational& value2);
const Rational operator -(const Rational& value1,const Rational& value2);
const Rational operator -(const Rational& value);

int main()
{
    Rational x,y,add,sub,neg,mul,div;
    int numeVal,denoVal;//numeratorValue&denominatorValue
            /*test Mutator&Accessor
            int a,b,c,d;
            x.setNumerator(4);
            x.setDenominator(2);
            y.setNumerator(5);
            y.setDenominator(4);
            a=x.getNumerator();
            b=x.getDenominator();
            c=y.getNumerator();
            d=y.getDenominator();
            cout<<a<<"/"<<b<<" "<<c<<"/"<<d<<endl;
            */
    //input test data
    cout<<"please input two rational number:[format:(nume)/(deno)]"<<endl;
    cin>>x>>y;
    //calculate result
    add=x+y;
    sub=x-y;
    neg=-x;
    mul=x*y;
    div=x/y;
    /*test cout*/
    cout<<"normalized:"<<endl<<x<<" "<<y<<endl;
    cout<<x<<"+"<<y<<"="<<add<<endl;
    cout<<x<<"-"<<y<<"="<<sub<<endl;
    cout<<"-"<<x<<"="<<neg<<endl;
    cout<<x<<"*"<<y<<"="<<mul<<endl;
    cout<<x<<"/"<<y<<"="<<div<<endl;
    x.normalize();
    y.normalize();
    //equ
    cout<<x<<"equal to "<<y<<endl;
    if(x==y)
        cout<<"\t...true"<<endl;
    else
        cout<<"\t...false"<<endl;
    //LT
    cout<<x<<"less than "<<y<<endl;
    if(x<y)
        cout<<"\t...true"<<endl;
    else
        cout<<"\t...false"<<endl;
    //LE
    cout<<x<<"less or equal to "<<y<<endl;
    if(x<=y)
        cout<<"\t...true"<<endl;
    else
        cout<<"\t...false"<<endl;
    //GT
    cout<<x<<"greater than "<<y<<endl;
    if(x>y)
        cout<<"\t...true"<<endl;
    else
        cout<<"\t...false"<<endl;
    //GE
    cout<<x<<"greater or equal to "<<y<<endl;
    if(x>=y)
        cout<<"\t...true"<<endl;
    else
        cout<<"\t...false"<<endl;

    numeVal=x[0];
    denoVal=x[1];
    cout<<"x[0]="<<numeVal<<" x[1]="<<denoVal<<endl;
    numeVal=y[0];
    denoVal=y[1];
    cout<<"y[0]="<<numeVal<<" y[1]="<<denoVal<<endl;
    return 0;
}

/*constructor*/
Rational::Rational(void):nume(0),deno(1)
{/*default:0/1*/}
Rational::Rational(int wholeNumber):nume(wholeNumber),deno(1)
{/*only one argument:wholeNumber/1*/}
Rational::Rational(int numeValue,int denoValue):nume(numeValue),deno(denoValue)
{/*normal:numeValue/denoValue*/}
//

/*mutator*/
const void Rational::setNumerator(int input)
{
    /*change nume value*/
    nume=input;
    return;
}
const void Rational::setDenominator(int input)
{
    /*change deno value*/
    deno=input;
    return;
}
//

/*accessor*/
const int Rational::getNumerator(void)const
{
    /*return nume value*/
    return nume;
}
const int Rational::getDenominator(void)const
{
    /*return deno value*/
    return deno;
}
//

/*io function*/
ostream& operator <<(ostream& outputstream,const Rational& value)
{
    /*if denominator is 1 just output nume*/
    if(value.deno==1||value.deno==0)
        outputstream<<"("<<value.nume<<")";
    else
        outputstream<<"("<<value.nume<<"/"<<value.deno<<")";
    return outputstream;
}
istream& operator >>(istream& inputstream,Rational& value)
{
    const int MAXBUFFER=1000;
    char buffer[MAXBUFFER];
    char valueBuffer[MAXBUFFER];
    int i,j,len,divpos;
    int numeValue,denoValue;
    //read from stream
    inputstream>>buffer;
    //find '/' pos
    len=strlen(buffer);
    divpos=-1;
    for(i=0;i<len;i++)
    {
        if(buffer[i]=='/')
        {
            divpos=i;
            break;
        }
        else if(!((buffer[i]>='0'&&buffer[i]<='9')||buffer[i]=='/'||buffer[i]=='\0'||buffer[i]=='-'))
        {

            cout<<"error:input format error"<<endl;
            cout<<"error char: "<<buffer[i]<<" "<<endl;
            exit(1);
        }
    }
    if(divpos==-1)//no '/'
    {
        cout<<"no slash sign:auto type convert to (wholeNumber)/1"<<endl;
        value.setNumerator(atoi(buffer));
    }
    else if(divpos==0)//start with '/'
    {
        cout<<"start with slash sign:auto type convert to 0/1"<<endl;
        value.setNumerator(0);
    }
    else if(divpos==len-1)//end with '/'
    {
        cout<<"end with slash sign:auto type convert to (wholeNumber)/1"<<endl;
        buffer[len-1]='\0';
        value.setNumerator(atoi(buffer));
    }
    else
    {
        j=0;
        valueBuffer[j]='\0';
        for(i=0;i<divpos;i++)
        {
            valueBuffer[j++]=buffer[i];
            valueBuffer[j]='\0';
        }
        numeValue=atoi(valueBuffer);
        j=0;
        valueBuffer[j]='\0';
        for(i=divpos+1;i<len;i++)
        {
            valueBuffer[j++]=buffer[i];
            valueBuffer[j]='\0';
        }
        denoValue=atoi(valueBuffer);
        normalize(numeValue,denoValue);
        if(numeValue==0&&denoValue==0)
        {
            cout<<"error:detect 0/0"<<endl;
            exit(1);
        }
        value.setNumerator(numeValue);
        value.setDenominator(denoValue);
    }
    return inputstream;
}
/* */

/*normalize*/
const void Rational::normalize(void)
{
    /*normalize the Rational class:
    check point:
        1.factor that can be both divide
        2.the sign should be +/+ -/+.
            no -/- +/-.
    */
    int i;
    const int MAXFACTOR=abs(deno);
    for(i=MAXFACTOR;i>=2;i--)//check every factor
    {
        if((nume%i==0)&&(deno%i==0))
        {
            nume=nume/i;
            deno=deno/i;
        }
    }
    if(deno<0)
    {
        nume*=-1;
        deno*=-1;
    }
    return;
}
const void normalize(int& numeValue,int& denoValue)
{
    /*normalize the nume(int)&deno(int):
    check point:
        1.factor that can be both divide
        2.the sign should be +/+ -/+.
            no -/- +/-.
    */
    int i;
    const int MAXFACTOR=abs(denoValue);
    for(i=MAXFACTOR;i>=2;i--)//check every factor
    {
        if((numeValue%i==0)&&(denoValue%i==0))
        {
            numeValue=numeValue/i;
            denoValue=denoValue/i;
        }
    }
    if(denoValue<0)
    {
        numeValue*=-1;
        denoValue*=-1;
    }
    return;
}
//


//add:addition
const Rational operator +(const Rational& value1,const Rational& value2)
{
    /*  pre:two rational number
        post:return result rational number*/
    int newnume=value1.getNumerator()*value2.getDenominator()+value2.getNumerator()*value1.getDenominator();
    int newdeno=value1.getDenominator()*value2.getDenominator();
    normalize(newnume,newdeno);
    return Rational(newnume,newdeno);
}
//sub:subtraction
const Rational operator -(const Rational& value1,const Rational& value2)
{
    /*  pre:two rational number
        post:return result rational number*/
    int newnume=value1.getNumerator()*value2.getDenominator()-value2.getNumerator()*value1.getDenominator();
    int newdeno=value1.getDenominator()*value2.getDenominator();
    normalize(newnume,newdeno);
    return Rational(newnume,newdeno);
}
//neg:negation
const Rational operator -(const Rational& value)
{
    /*  pre:one rational number
        post:return result rational number*/
    int newnume=value.getNumerator()*-1;
    int newdeno=value.getDenominator();
    normalize(newnume,newdeno);
    return Rational(newnume,newdeno);
}
//mul:multipilication
const Rational operator *(const Rational& value1,const Rational& value2)
{
    /*  pre:two rational number
        post:return result rational number*/
    int newnume=value1.nume*value2.nume;
    int newdeno=value1.deno*value2.deno;
    Rational newRat(newnume,newdeno);
    newRat.normalize();
    return newRat;
}
//div:division
const Rational operator /(const Rational& value1,const Rational& value2)
{
    /*  pre:two rational number
        post:return result rational number*/
    int newnume=value1.nume*value2.deno;
    int newdeno=value1.deno*value2.nume;
    Rational newRat(newnume,newdeno);
    newRat.normalize();
    return newRat;
}
//equ:equal
bool operator ==(const Rational& value1,const Rational& value2)
{
    /*  pre:two rational number
        post:return compare result bool*/
    bool judge;
    judge=(value1.nume*value2.deno==value2.nume*value1.deno);
    return judge;
}
//LT:less than
bool Rational::operator <(const Rational& value2)const
{
    /*  pre:first function call argument is normolized rational number
        second argument is normolized rational number
        post:return compare result bool*/
    bool judge;
    judge=(nume*value2.deno<value2.nume*deno);
    return judge;
}
//LE:less than or equal to
bool Rational::operator <=(const Rational& value2)const
{
    /*  pre:first function call argument is normolized rational number
        second argument is normolized rational number
        post:return compare result bool*/
    bool judge;
    judge=(nume*value2.deno<=value2.nume*deno);
    return judge;
}
//GT:greater than
bool Rational::operator >(const Rational& value2)const
{
    /*  pre:first function call argument is normolized rational number
        second argument is normolized rational number
        post:return compare result bool*/
    bool judge;
    judge=(nume*value2.deno>value2.nume*deno);
    return judge;
}
//GE:greater than or equal to
bool Rational::operator >=(const Rational& value2)const
{
    /*  pre:first function call argument is normolized rational number
        second argument is normolized rational number
        post:return compare result bool*/
    bool judge;
    judge=(nume*value2.deno>=value2.nume*deno);
    return judge;
}

int& Rational::operator[](int index)
{
    /*  pre:index should be 0 or 1
        post:   index=0 return numerator
                index=1 return denominator
                else error:exit program     */
    if(index==0)
        return nume;
    else if(index==1)
        return deno;
    else
    {
        cout<<"error:index format error"<<endl;
        exit(1);
    }
}

