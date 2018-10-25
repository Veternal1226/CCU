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
