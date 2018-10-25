#include <iostream>
#include <cstdlib>
#define TESTER 0
#define LINUX 0
/*
    test 4 pattern:TESTER 1
    in linux system:LINUX 1
*/


using namespace std;

/*
    by 李維哲 404410039 資工二
*/
class worldtype
{
public:
    worldtype(int widthValue,int heightValue);
    worldtype();
    void input();
    void spaceDeclare();
    void initialize(int maptype);
    void display();
    void iniGlider();
    void iniSpaceship();
    void iniPulsar();
    void iniRandom(int possibility);
    void proceed(int generation);
    void proceed();
    bool judge(int y,int x);
    void copymap();
private:
    int width;
    int height;
    int midx;//the center of the map
    int midy;//the center of the map
    int totsize;//the map's total size
    char** worldmap;
    char** newworldmap;
};

int main()
{
    int gencount(100),maptype;
    int widthValue,heightValue;
    cout<<"please set map size(width height)";
    cin>>widthValue>>heightValue;
    if(!(widthValue>0&&widthValue<1000&&heightValue>0&&widthValue<1000))//size illegal
    {
        cout<<"error:format error.";
        return 0;
    }
    worldtype world(widthValue,heightValue);
    world.spaceDeclare();
    cout<<"\t1 for glider\n\t2 for Spaceship\n\t3 for pulsar\n";//mode information
    cout<<"\t4~100 for random\nmap type:";
    cin>>maptype;
    if(!(maptype>0&&maptype<=100))//map type illegal
    {
        cout<<"error:format error.";
        return 0;
    }
    cout<<"how many generation proceed?:";
    cin>>gencount;
    if(!(maptype>0&&maptype<=100))//generation illegal
    {
        cout<<"error:format error.";
        return 0;
    }
    world.initialize(maptype);
                //test of four pattern. want to test. change define TESTER to 1
                if(TESTER)
                {
                    world.initialize(1);//Glider
                    world.proceed(100);
                    system("pause");
                    world.initialize(2);//Spaceship
                    world.proceed(100);
                    system("pause");
                    world.initialize(3);//Pulsar
                    world.proceed(100);
                    system("pause");
                    world.initialize(50);//Random
                    world.proceed(100);
                    system("pause");
                    return 0;
                }
    if(gencount==0)//if no proceed: just show map
        world.display();
    world.proceed(gencount);
    system("pause");
    return 0;
}

worldtype::worldtype(int widthValue,int heightValue):width(widthValue+2),height(heightValue+2)
{   /*constructor*/
    midx=(widthValue+2)/2;
    midy=(heightValue+2)/2;
    totsize=widthValue*heightValue;
}
worldtype::worldtype():width(82),height(25)
{   /*default constructor*/
    midx=41;
    midy=13;
    totsize=533;//41*13
}

void worldtype::spaceDeclare()
{
    /*
        declare map's space with height*width
    */
    char* temp;
    int i;
    worldmap=(char**)malloc(sizeof(char*)*height);
    temp=(char*)malloc(sizeof(char)*height*width);
    for(i=0;i<height;i++,temp+=width)
    {
        worldmap[i]=temp;
    }
    //  declare new map's space with height*width
    char* newtemp;
    int j;
    newworldmap=(char**)malloc(sizeof(char*)*height);
    newtemp=(char*)malloc(sizeof(char)*height*width);
    for(j=0;j<height;j++,newtemp+=width)
    {
        newworldmap[j]=newtemp;
    }
    return;
}

void worldtype::initialize(int maptype)
{
    /*
        pre: the map type
        post:initialized map
    */
    //clear map&newmap
    int i,j;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            worldmap[i][j]='.';
            newworldmap[i][j]='.';
        }
    }

    switch(maptype)
    {
        case 1:
            iniGlider();
            break;
        case 2:
            iniSpaceship();
            break;
        case 3:
            iniPulsar();
            break;
        default:
            iniRandom(maptype);
            break;
    }
    //edge initialize
    for(i=0;i<width;i++)//up&down
    {
        worldmap[0][i]='.';
        worldmap[height-1][i]='.';
    }
    for(i=0;i<height;i++)//left&right
    {
        worldmap[i][0]='.';
        worldmap[i][width-1]='.';
    }

    return;
}

void worldtype::display()
{
    /*
        display the map
        "O" for live,"." for dead.
    */
    int i,j;
    if(LINUX)
        system("clear");
    else
        system("cls");//clean the window
    if(height==25&&width==82&&!LINUX)//if wid==82,it will auto change line->no \n
    {
        for(i=1;i<height-1;i++)
        {
            for(j=1;j<width-1;j++)
            {
                cout<<worldmap[i][j];
            }
        }
    }
    else
    {
        for(i=1;i<height-1;i++)
        {
            for(j=1;j<width-1;j++)
            {
                cout<<worldmap[i][j];
            }
            cout<<"\n";
        }
    }
    return;
}

void worldtype::iniGlider()
{
    /*initialize map type:Glider*/
    worldmap[midy-1][midx-1]='O';
    worldmap[midy-1][midx]='O';
    worldmap[midy-1][midx+1]='O';
    worldmap[midy][midx-1]='O';
    worldmap[midy+1][midx]='O';
    return;
}

void worldtype::iniSpaceship()
{
    /*initialize map type:Spaceship*/
    worldmap[midy-1][midx-1]='O';
    worldmap[midy-1][midx+2]='O';
    worldmap[midy][midx-2]='O';
    worldmap[midy+1][midx-2]='O';
    worldmap[midy+1][midx+2]='O';
    worldmap[midy+2][midx-2]='O';
    worldmap[midy+2][midx-1]='O';
    worldmap[midy+2][midx]='O';
    worldmap[midy+2][midx+1]='O';
    return;
}

void worldtype::iniPulsar()
{
    /*initialize map type:Pulsar*/
    int i,j;
    //4 quadrant
    for(i=-1;i<=1;i+=2)
    {
        for(j=-1;j<=1;j+=2)
        {
            worldmap[midy-6*j][midx+3*i]='O';
            worldmap[midy-6*j][midx+4*i]='O';
            worldmap[midy-5*j][midx+2*i]='O';
            worldmap[midy-5*j][midx+3*i]='O';
            worldmap[midy-4*j][midx+1*i]='O';
            worldmap[midy-4*j][midx+3*i]='O';
            worldmap[midy-4*j][midx+6*i]='O';
            worldmap[midy-3*j][midx+1*i]='O';
            worldmap[midy-3*j][midx+2*i]='O';
            worldmap[midy-3*j][midx+4*i]='O';
            worldmap[midy-3*j][midx+5*i]='O';
            worldmap[midy-3*j][midx+6*i]='O';
            worldmap[midy-2*j][midx+1*i]='O';
            worldmap[midy-2*j][midx+3*i]='O';
            worldmap[midy-2*j][midx+5*i]='O';
            worldmap[midy-1*j][midx+2*i]='O';
            worldmap[midy-1*j][midx+3*i]='O';
            worldmap[midy-1*j][midx+4*i]='O';
        }
    }
    return;
}

void worldtype::iniRandom(int possibility)
{
    /*initialize map type:Random*/
    int value,i,j;
    for(i=1;i<height-1;i++)
    {
        for(j=1;j<width-1;j++)
        {
            value=rand()%100;
            if(value<possibility)
                worldmap[i][j]='O';
            else
                worldmap[i][j]='.';
        }
    }
    return;
}

void worldtype::proceed()
{   /*  default:1 generation*/
    /*
        move to new generation
    */
    int y,x;
    for(y=1;y<height-1;y++)//every point
    {
        for(x=1;x<width;x++)
        {
            if(judge(y,x))//judge will live or dead
                newworldmap[y][x]='O';
            else
                newworldmap[y][x]='.';
        }
    }
    copymap();
    display();
    return;
}

void worldtype::proceed(int generation)
{
    /*
        move to new generation
        pre:how many generation will proceed
        post:show every step on screen
    */
    int y,x,gentemp;
    for(gentemp=0;gentemp<generation;gentemp++)
    {
        for(y=1;y<height-1;y++)
        {
            for(x=1;x<width;x++)
            {
                if(judge(y,x))
                    newworldmap[y][x]='O';
                else
                    newworldmap[y][x]='.';
            }
        }
        copymap();
        display();
    }
    return;
}

bool worldtype::judge(int y,int x)
{
    /*
        pre:the coordinate
        post:the cell will dead or live
    */
    int counter(0),judgement;
    //8 way
    if(worldmap[y-1][x-1]=='O') counter++;
    if(worldmap[y-1][x]=='O') counter++;
    if(worldmap[y-1][x+1]=='O') counter++;
    if(worldmap[y][x-1]=='O') counter++;
    if(worldmap[y][x+1]=='O') counter++;
    if(worldmap[y+1][x-1]=='O') counter++;
    if(worldmap[y+1][x]=='O') counter++;
    if(worldmap[y+1][x+1]=='O') counter++;
    //true for live,false for dead
    if(worldmap[y][x]=='O')//if alive
    {
        if(counter==0||counter==1)//die loneliness
            judgement=false;
        else if(counter>3)//die overcrowd
            judgement=false;
        else
            judgement=true;//nothing happened
    }
    else//if dead
    {
        if(counter==3)
            judgement=true;//birth
        else
            judgement=false;//nothing happened
    }
    return judgement;
}

void worldtype::copymap()
{
    /*
        update the map to next generation
    */
    int y,x;
    for(y=1;y<height-1;y++)
    {
        for(x=1;x<width-1;x++)
        {
            worldmap[y][x]=newworldmap[y][x];
        }
    }
}
