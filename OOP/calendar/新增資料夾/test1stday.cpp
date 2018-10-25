#include <iostream>
#include<string.h>

using namespace std;

/*
    by 404410039 李維哲 資工二
*/

void get1stDayOfMonth(int year,int month,int& weekday,int& ndaysOfMonth);
bool leapJudge(int year);
int getweek(int year,int month,bool leap);
void test(int year,int month,int weekday,int ndaysOfMonth);

int main()
{
    int year,month,weekday,ndaysOfMonth;
    year=2000,month=2;
    get1stDayOfMonth(year,month,weekday,ndaysOfMonth);
    return 0;
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
