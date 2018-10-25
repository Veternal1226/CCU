#include <iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

/*
    by 404410039 李維哲 資工二
*/

bool inputYrMn(int& year,int& month);
void get1stDayOfMonth(int year,int month,int& weekday,int& ndaysOfMonth);
bool leapJudge(int year);
int getweek(int year,int month,bool leap);
void test(int year,int month,int weekday,int ndaysOfMonth);
void showCalendar(int year,int month,int weekday,int ndaysOfMonth);

int main()
{
    bool judge;
    int year(0),month(0);//target year&month
    int weekday(0),ndaysOfMonth(0);//what day is it&how many day it has
    judge=inputYrMn(year,month);
    if(judge!=1)    cout<<"error\n";//if input is illegal->error
        //else    cout<<year<<"/"<<month;//test
    else
    {
        get1stDayOfMonth(year,month,weekday,ndaysOfMonth);
        showCalendar(year,month,weekday,ndaysOfMonth);
    }
    return 0;
}

bool inputYrMn(int& year,int& month)
{
    /*
        pre:1901<=year<=2099,1<=month<=12
        ,all of they are positive integer
        otherwise return error
        post:the year&month will be inputed
        if legal return true
        if illegal return false
    */
    bool judge;
    int length,i;
    char buffer[10];
    //key in year
    cout<<"Year:";
    cin>>buffer;
    length=strlen(buffer);
    for(i=0;i<length;i++)//check input is int
    {
        if(buffer[i]<='9'&&buffer[i]>='0')
            judge=true;
        else
        {
            judge=false;
            break;
        }
    }
    if(judge)
        year=atoi(buffer);
    else
        return judge;
    //judge year is valid
    if(year>2099||year<1901)
    {
        judge=false;
        return judge;
    }
    //key in month
    cout<<"Month:";
    cin>>buffer;
    length=strlen(buffer);
    for(i=0;i<length;i++)//check input is int
    {
        if(buffer[i]<='9'&&buffer[i]>='0')
            judge=true;
        else
        {
            judge=false;
            break;
        }
    }
    if(judge)
        month=atoi(buffer);
    else
        return judge;
    //judge month is valid
    if(month<1||month>12)
    {
        judge=false;
        return judge;
    }
    return judge;
}

void get1stDayOfMonth(int year,int month,int& weekday,int& ndaysOfMonth)
{
    /*
        pre: the year&month should be illegal
        post:this function will get the weekday
        &how many days of this month
    */
    bool leap(false);//leap year or not.yes=true
    const int daysOfMonth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    const int daysOfLeap[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
        //array start at 0->13month to align real month
    leap=leapJudge(year);
    //get the days of this month
    if(leap)    ndaysOfMonth=daysOfLeap[month];
    else    ndaysOfMonth=daysOfMonth[month];
    weekday=getweek(year,month,leap);
    test(year,month,weekday,ndaysOfMonth);
    return;
}

bool leapJudge(int year)
{
    /*
        pre:input year
        post:judge leap year or not.
        if yes return true
    */
    bool judge(0);
    if(year%4==0)
        judge=true;
    if(year%100==0)
        judge=false;
    if(year%400==0)
        judge=true;
    return judge;
}

int getweek(int year,int month,bool leap)
{
    /*
        pre: input valid year&month and leap or not
        post: output the first day's weekday of the month
    */
    const int normalAdd[13]={0,0,3,3,6,1,4,6,2,5,0,3,5};
    const int leapAdd[13]={0,6,2,3,6,1,4,6,2,5,0,3,5};
    int weekday(-1),add(-1);
    if(leap)    add=leapAdd[month];
    else    add=normalAdd[month];
    weekday=((year)+(year/4)+(year/400)-(year/100)+add)%7;
    return weekday;
}

void test(int year,int month,int weekday,int ndaysOfMonth)
{
    /*
        post:print out the data
        check the data is properly
    */
    char monthName[4];
    char weekName[4];
    switch(month)
    {
        case 1:
            strcpy(monthName,"Jan.");
            break;
        case 2:
            strcpy(monthName,"Feb.");
            break;
        case 3:
            strcpy(monthName,"Mar.");
            break;
        case 4:
            strcpy(monthName,"Apr.");
            break;
        case 5:
            strcpy(monthName,"May.");
            break;
        case 6:
            strcpy(monthName,"Jun.");
            break;
        case 7:
            strcpy(monthName,"Jul.");
            break;
        case 8:
            strcpy(monthName,"Aug.");
            break;
        case 9:
            strcpy(monthName,"Sem.");
            break;
        case 10:
            strcpy(monthName,"Oct.");
            break;
        case 11:
            strcpy(monthName,"Nov.");
            break;
        case 12:
            strcpy(monthName,"Dec.");
            break;
    }
    cout<<year<<"/"<<month<<" "
    <<monthName<<" "<<ndaysOfMonth<<"days ";
    switch(weekday)
    {
        case 0:
            strcpy(weekName,"Sun.");
            break;
        case 1:
            strcpy(weekName,"Mon.");
            break;
        case 2:
            strcpy(weekName,"Tue.");
            break;
        case 3:
            strcpy(weekName,"Wed.");
            break;
        case 4:
            strcpy(weekName,"Thr.");
            break;
        case 5:
            strcpy(weekName,"Fri.");
            break;
        case 6:
            strcpy(weekName,"Sat.");
            break;
    }
    cout<<"start at:"<<weekName<<endl;
    return;
}

void showCalendar(int year,int month,int weekday,int ndaysOfMonth)
{
    /*
        pre: valid year,month,weekday,ndaysOfMonth
        post: print out target calendar
    */
    char monthName[4];
    int i,counter;
    //show title
    switch(month)
    {
        case 1:
            strcpy(monthName,"Jan.");
            break;
        case 2:
            strcpy(monthName,"Feb.");
            break;
        case 3:
            strcpy(monthName,"Mar.");
            break;
        case 4:
            strcpy(monthName,"Apr.");
            break;
        case 5:
            strcpy(monthName,"May.");
            break;
        case 6:
            strcpy(monthName,"Jun.");
            break;
        case 7:
            strcpy(monthName,"Jul.");
            break;
        case 8:
            strcpy(monthName,"Aug.");
            break;
        case 9:
            strcpy(monthName,"Sem.");
            break;
        case 10:
            strcpy(monthName,"Oct.");
            break;
        case 11:
            strcpy(monthName,"Nov.");
            break;
        case 12:
            strcpy(monthName,"Dec.");
            break;
    }
    cout<<"--------------------------------------------------------\n"
    <<"\t\t"<<year<<"\t\t"<<monthName<<"\t\t\t\n"
    <<"--------------------------------------------------------\n"
    <<"SUN\tMON\tTUE\tWED\tTHU\tFRI\tSAT\t\n";
    //skip space
    for(i=0;i<weekday;i++)
    {
        cout<<"\t";
    }
    //output everyday on calendar
    counter=weekday;
    for(i=1;i<=ndaysOfMonth;i++)
    {
        if(counter==7)
        {
            cout<<"\n"<<i<<"\t";
            counter=1;
        }
        else
        {
            cout<<i<<"\t";
            counter++;
        }
    }
    cout<<"\n--------------------------------------------------------\n";
    return;
}



