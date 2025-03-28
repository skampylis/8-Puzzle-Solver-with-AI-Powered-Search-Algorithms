#include "State.h"
#include <cmath>
#include <cstring>
#include <sstream>
#include <vector>
#include <iostream>
#define HEIGHT 3
#define WIDTH 3

using namespace std;

State::State()
{
    for (int i=0;i<HEIGHT;i++)
    {
        for (int j=0;j<WIDTH;j++)
        {
            board[i][j]=0;
        }
    }
    setPrevious(NULL);
}

State::State(int A[HEIGHT][WIDTH])
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            board[i][j]=A[i][j];
        }
    }
    setPrevious(NULL);
}

int State::getDepth()
{
    int counter=0;
    State *p=this;
    while (p->prev!=NULL)
    {
        p=p->prev;
        counter++;
    }
    return counter;
}


bool State::operator==(const State& s)const
{
    char found=false;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(board[i][j]!=s.board[i][j])
            {
                found=true;
            }
        }
    }
    return (!found);
}

State State::operator=(State o)
{
    board[HEIGHT][WIDTH]=o.board[HEIGHT][WIDTH];
    prev=o.prev;
    return *this;
}

int State::getBoardIndex(int a,int b)
{
    return board[a][b];
}

void State::setBoardIndex(int a,int b,int value)
{
    board[a][b]=value;
}

void State::setHvalue(double h)
{
    Hvalue=h;
}

double State::getHvalue()
{
    return Hvalue;
}

bool State::goUp(State &n,int a,int b)
{
    if (a>0)
    {
        int temp=n.getBoardIndex(a-1,b);
        int x=n.getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a-1,b,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool State::goDown(State &n,int a,int b)
{
    if (a<2)
    {
        int temp=getBoardIndex(a+1,b);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a+1,b,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool State::goLeft(State &n,int a,int b)
{
    if (b>0)
    {
        int temp=getBoardIndex(a,b-1);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a,b-1,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    else
    {
        return false;
    }
}

bool State::goRight(State &n,int a,int b)
{
    if (b<2)
    {
        int temp=getBoardIndex(a,b+1);
        int x=getBoardIndex(a,b);
        n=*this;
        n.setBoardIndex(a,b+1,x);
        n.setBoardIndex(a,b,temp);
        n.setPrevious(this);
        return true;
    }
    else
    {
        return false;
    }
}

int State::getXZeroIndex(State &n)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(n.board[i][j]==0)
            {
                return i;
            }
        }
    }
}

int State::getYZeroIndex(State &n)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if(n.board[i][j]==0)
            {
                return j;
            }
        }
    }
}

vector <State *> State::expand()
{
    vector <State *> children;
    State *child;
    child=new State(*this);
    if (goUp(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
    {
        children.push_back(child);
    }
    else
    {
        delete child;
    }
    child=new State(*this);
    if (goRight(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
    {
        children.push_back(child);
    }
    else
    {
        delete child;
    }
    child=new State(*this);
    if (goDown(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
    {
        children.push_back(child);
    }
    else
    {
        delete child;
    }
    child=new State(*this);
    if (goLeft(*child,getXZeroIndex(*child),getYZeroIndex(*child)))
    {
        children.push_back(child);
    }
    else
    {
        delete child;
    }
    return children;
}

int State::heuristic(State *goal)
{
    int dist=0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            for(int q=0;q<HEIGHT;q++)
            {
                for(int p=0;p<WIDTH;p++)
                {
                    if(goal->board[q][p]==board[i][j])
                    {
                        dist+=abs(i-q)+abs(j-p);
                    }
                }
            }
        }
    }
    return dist;
}


int State::aStarHeuristic(State *goal)
{
    int dist=0;
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            for(int q=0;q<HEIGHT;q++)
            {
                for(int p=0;p<WIDTH;p++)
                {
                    if(goal->board[q][p]==board[i][j])
                    {
                        dist+=abs(i-q)+abs(j-p);
                    }
                }
            }
        }
    }
    return dist+this->getDepth();
}

unsigned long State::getKey()
{
    int finalBoard[3][3]={1,2,3,
                          4,5,6,
                          7,8,0};
    State *finalPuzzle=new State(finalBoard);
    unsigned long k=this->heuristic(finalPuzzle)*10+(getXZeroIndex(*this)+getYZeroIndex(*this));
    return k;
}
