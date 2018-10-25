#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class queen
{
public:
    //constructor
    queen(void);
    queen(int boardSize);
    queen(int* knownArray);
    queen(const queen& copyFrom);
    //accessor
    void setRow(int row,int col);
    void setBoard(int* newBoard);
    int getCol(int row);
    int* getBoard(void);
    int getAttack(void);
    //assignment(shallow copy)
    queen& operator =(const queen& rtSide);

    void printBoard(void);
    void printBoard_map(void);
    int attack();
    int evolution_HC(void);
private:
    int* board;
    int boardSize;
    int attackNum;
};

int seed=time(NULL);

queen::queen(void):boardSize(8)
{
    srand(seed++);
    board=new int[boardSize];
    for(int i=0;i<boardSize;i++)
    {
        board[i]=rand()%8;
    }
    attackNum=attack();
}
queen::queen(int boardSize):boardSize(boardSize)
{
    srand(seed++);
    //cout<<"//"<<endl;
    board=new int[boardSize];
    for(int i=0;i<boardSize;i++)
    {
        board[i]=rand()%boardSize;
        //cout<<board[i]<<" ";
    }
    //cout<<"//"<<endl;
    attackNum=attack();
}
queen::queen(int* knownArray):boardSize(sizeof(knownArray)/sizeof(int))
{
    board=new int[boardSize];
    for(int i=0;i<boardSize;i++)
    {
        board[i]=knownArray[i];
    }
    attackNum=attack();
}
queen::queen(const queen& copyFrom):boardSize(copyFrom.boardSize)
{
    board=new int[boardSize];
    for(int i=0;i<boardSize;i++)
    {
        board[i]=copyFrom.board[i];
    }
    attackNum=attack();
}

void queen::setRow(int row,int col)
{
    board[row]=col;
    attackNum=attack();
    return;
}

void queen::setBoard(int* newBoard)
{
    for(int i=0;i<boardSize;i++)
    {
        board[i]=newBoard[i];
    }
    attackNum=attack();
    return;
}

int queen::getCol(int row)
{
    return board[row];
}

int* queen::getBoard(void)
{
    return board;
}

int queen::getAttack(void)
{
    return attackNum;
}

void queen::printBoard(void)
{
    for(int i=0;i<boardSize;i++)
    {
        cout<<board[i]<<" ";
    }
    cout<<endl;
}

void queen::printBoard_map(void)
{
    for(int i=0;i<boardSize;i++)
    {
        for(int j=0;j<boardSize;j++)
        {
            if(j==board[i])
                cout<<"O ";
            else
                cout<<". ";
        }
        cout<<endl;
    }
}

int queen::attack(void)
{
    int attacks=0;
    int nowRow,testRow;
    for(nowRow=0;nowRow<boardSize;nowRow++)
    {
        for(testRow=nowRow+1;testRow<boardSize;testRow++)
        {
            if(board[nowRow]==board[testRow]//same col
               ||(testRow-nowRow)==abs(board[testRow]-board[nowRow]))//same cross X
                attacks++;
        }
    }
    attackNum=attacks;
    return attacks;
}

queen& queen::operator =(const queen& rtSide)
{
    if(this==&rtSide)
        return *this;
    else
    {
        boardSize=rtSide.boardSize;
        delete [] board;
        board=new int[boardSize];
        for(int i=0;i<boardSize;i++)
            board[i]=rtSide.board[i];
        attackNum=attack();
    }
    return *this;
}

int queen::evolution_HC(void)
{
    int row,col;
    int minAttack,minRow,minCol;
    queen nowBoard(*this);
    queen testBoard(nowBoard);
    minAttack=nowBoard.attack();
    minRow=minCol=999999;
    //nowBoard.printBoard_map();
    //cout<<nowBoard.attack()<<endl;
    for(row=0;row<boardSize;row++)
    {
        for(col=0;col<boardSize;col++)
        {
            if(nowBoard.board[row]!=col)
            {
                testBoard=nowBoard;
                testBoard.setRow(row,col);
                //testBoard.printBoard();
                if(testBoard.attack()<minAttack)
                {
                    minRow=row;
                    minCol=col;
                    minAttack=testBoard.attack();
                }
            }
        }
    }
    //cout<<minRow<<" "<<minCol<<endl;
    if(minAttack==nowBoard.attack())//local min attack
        return 0;
    else
    {
        this->setRow(minRow,minCol);
        //this->printBoard_map();
        //cout<<this->attack()<<endl;
        return 1;
    }

}

int attackArray(int* board,int boardSize)
{
    int attacks=0;
    int nowRow,testRow;
    for(nowRow=0;nowRow<boardSize;nowRow++)
    {
        for(testRow=nowRow+1;testRow<boardSize;testRow++)
        {
            if(board[nowRow]==board[testRow]//same col
               ||(testRow-nowRow)==abs(board[testRow]-board[nowRow]))//same cross X
                attacks++;
        }
    }
    return attacks;
}

int selectionWheel(queen* input,int population)
{
    int nSample,samplePos;
    int bestAttack,bestPos;
    nSample=rand()%population+1;
    bestAttack=999999;
    bestPos=999;
    for(int i=0;i<nSample;i++)
    {
        samplePos=rand()%population;
        //cout<<input[samplePos].attack()<<" ";
        if(input[samplePos].attack()<bestAttack)
        {
            bestAttack=input[samplePos].attack();
            bestPos=samplePos;
        }
    }
    //cout<<"bestPos="<<bestPos<<endl;
    return bestPos;
}

queen crossover(queen pick1,queen pick2,int nqueen,int population)
{
    int crossPoint;
    queen child(nqueen);
    crossPoint=rand()%(nqueen-1);//8q:0~6
    for(int row=0;row<nqueen;row++)
    {
        if(row<=crossPoint)
        {
            child.setRow(row,pick1.getCol(row));
        }
        else
        {
            child.setRow(row,pick2.getCol(row));
        }
    }
    //cout<<"m="<<crossPoint<<endl;
    //child.printBoard();
    return child;
}

queen* mutation(queen* origin,int nqueen,int population,float mutationRate)
{
    srand(seed++);
    int mutationTest;
    int mutationNum;
    for(int i=0;i<population;i++)
    {
        for(int row=0;row<nqueen;row++)
        {
            mutationTest=rand()%10000;
            if((float)mutationTest<mutationRate*10000)
            {
                do{mutationNum=rand()%8;}
                while(mutationNum==origin[i].getCol(row));//prevent same col
                origin[i].setRow(row,mutationNum);
                //cout<<"(i,m)="<<i<<","<<row<<"="<<mutationNum<<endl;
            }
        }
    }
    return origin;
}

queen* evolution_GA(queen* origin,int nqueen,int population,float mutationRate,int generation)
{
    queen* child;
    queen temp;
    int flag=0;
    int pick1,pick2;
    //int crossPoint;
    child=(queen*)malloc(sizeof(queen)*population);
    for(int i=0;i<population;i++)
        child[i]=queen(nqueen);

    while(generation--)
    {
        //crossover
        for(int i=0;i<population;i++)
        {
            pick1=selectionWheel(origin,population);
            do{
            pick2=selectionWheel(origin,population);
            }while(pick2==pick1);
            //cout<<pick1<<" "<<pick2<<endl;
            temp=crossover(origin[pick1],origin[pick2],nqueen,population);
            child[i]=temp;
        }
        //mutation
        child=mutation(child,nqueen,population,mutationRate);
        //fitness

        for(int i=0;i<population;i++)
        {
            //child[i].printBoard();
            origin[i]=child[i];
        }
        for(int i=0;i<population;i++)
        {
            if(origin[i].attack()==0)
                flag=1;
        }
        if(flag)
            break;
    }
    return origin;
}




int main()
{
    int nqueen;
    int testTimes;
    int population,generation;
    float mutationRate;
    int total,success;
    float average,successRate;
    int bestPos,bestAttack;
    int startTime,endTime;
    //using HillClimbing 8queen
    //
    startTime=clock();
    nqueen=8;
    testTimes=30;
    total=success=0;
    cout<<nqueen<<"-queen test in HC for "<<testTimes<<" times:"<<endl;
    cout<<"list of all result:"<<endl;
    for(int i=0;i<testTimes;i++)
    {
        queen test(nqueen);
        while(test.evolution_HC());
        cout<<test.attack()<<" ";
        if((i+1)%10==0)
            cout<<endl;//only for alignment for 10 element 1 row
        total+=test.attack();
        if(test.attack()==0)
            success++;
    }
    average=(float)total/(float)testTimes;
    successRate=((float)success/(float)testTimes)*100;
    cout<<"ave="<<average<<endl;
    cout<<"rate="<<successRate<<"%"<<endl;
    endTime=clock();
    cout<<"use "<<(float)(endTime-startTime)/(float)CLOCKS_PER_SEC<<" sec"<<endl;
    //

    //using Genatic Algorithm 8queen
    nqueen=8;
    testTimes=30;
    population=20;
    generation=500;
    mutationRate=0.005;
    startTime=clock();
    queen best_8(nqueen);

    total=success=0;
    cout<<nqueen<<"-queen test in GA for "<<testTimes<<" times:"<<endl;
    cout<<"population="<<population<<endl;
    cout<<"generation="<<generation<<endl;
    cout<<"mutationRate="<<mutationRate<<endl;
    cout<<"list of all result:"<<endl;
    for(int i=0;i<testTimes;i++)
    {
        queen* test=(queen*)malloc(sizeof(queen)*population);;

        for(int j=0;j<population;j++)
        {
            test[j]=queen(nqueen);
            //test[j].printBoard();
            //cout<<"A:"<<test[j].attack()<<endl;
        }
        test[0].setRow(0,rand()%nqueen);
        test[0].setRow(1,rand()%nqueen);
        test=evolution_GA(test,nqueen,population,mutationRate,generation);
        bestAttack=bestPos=999999;
        for(int j=0;j<population;j++)
        {
            if(test[j].attack()<bestAttack)
            {
                bestAttack=test[j].attack();
                bestPos=j;
            }
            //test[i].printBoard();
            //cout<<"A:"<<test[i].attack()<<endl;
        }
        best_8=test[bestPos];

        cout<<best_8.attack()<<" ";
        if((i+1)%10==0)
            cout<<endl;//only for alignment for 10 element 1 row
        total+=best_8.attack();
        if(best_8.attack()==0)
            success++;
    }
    average=(float)total/(float)testTimes;
    successRate=((float)success/(float)testTimes)*100;
    endTime=clock();
    cout<<"ave="<<average<<endl;
    cout<<"rate="<<successRate<<"%"<<endl;
    cout<<"use "<<(float)(endTime-startTime)/(float)CLOCKS_PER_SEC<<" sec"<<endl;
    //

    //using HillClimbing 50queen
    //
    startTime=clock();
    nqueen=50;
    testTimes=30;
    total=success=0;
    cout<<nqueen<<"-queen test in HC for "<<testTimes<<" times:"<<endl;
    cout<<"list of all result:"<<endl;
    for(int i=0;i<testTimes;i++)
    {
        queen test(nqueen);
        while(test.evolution_HC());
        cout<<test.attack()<<" ";
        if((i+1)%10==0)
            cout<<endl;//only for alignment for 10 element 1 row
        total+=test.attack();
        if(test.attack()==0)
            success++;
    }
    average=(float)total/(float)testTimes;
    successRate=((float)success/(float)testTimes)*100;
    cout<<"ave="<<average<<endl;
    cout<<"rate="<<successRate<<"%"<<endl;
    endTime=clock();
    cout<<"use "<<(float)(endTime-startTime)/(float)CLOCKS_PER_SEC<<" sec"<<endl;
    //

    //using Genatic Algorithm 50queen
    nqueen=50;
    testTimes=30;
    population=20;
    generation=500;
    mutationRate=0.005;
    startTime=clock();
    queen best_50(nqueen);
    total=success=0;
    cout<<nqueen<<"-queen test in GA for "<<testTimes<<" times:"<<endl;
    cout<<"population="<<population<<endl;
    cout<<"generation="<<generation<<endl;
    cout<<"mutationRate="<<mutationRate<<endl;
    cout<<"list of all result:"<<endl;
    for(int i=0;i<testTimes;i++)
    {
        queen* test=(queen*)malloc(sizeof(queen)*population);;

        for(int j=0;j<population;j++)
        {
            test[j]=queen(nqueen);
            //test[j].printBoard();
            //cout<<"A:"<<test[j].attack()<<endl;
        }
        test[0].setRow(0,rand()%nqueen);
        test[0].setRow(1,rand()%nqueen);
        test=evolution_GA(test,nqueen,population,mutationRate,generation);
        bestAttack=bestPos=999999;
        for(int j=0;j<population;j++)
        {
            if(test[j].attack()<bestAttack)
            {
                bestAttack=test[j].attack();
                bestPos=j;
            }
            //test[i].printBoard();
            //cout<<"A:"<<test[i].attack()<<endl;
        }
        best_50=test[bestPos];

        cout<<best_50.attack()<<" ";
        if((i+1)%10==0)
            cout<<endl;//only for alignment for 10 element 1 row
        total+=best_50.attack();
        if(best_50.attack()==0)
            success++;
    }
    average=(float)total/(float)testTimes;
    successRate=((float)success/(float)testTimes)*100;
    endTime=clock();
    cout<<"ave="<<average<<endl;
    cout<<"rate="<<successRate<<"%"<<endl;
    cout<<"use "<<(float)(endTime-startTime)/(float)CLOCKS_PER_SEC<<" sec"<<endl;
    //

    return 0;
}
