#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <limits>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "State.h"

using namespace std;

char isExist(vector<State*> a,State *p)
{
    char found=false;
    for(unsigned int i=0;i<a.size();i++)
        if(a[i]==p)
        {
            found=true;
        }
    return (!found);
}

void showCase(State &p)
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            cout<<p.getBoardIndex(i,j)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

State *DFS(State *initial,State *goal,long long &examined,long long &mem)
{
    stack <State *> agenda;
    vector <State> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
        {
            mem=agenda.size()+closed.size();
        }
        State *s=agenda.top();
        agenda.pop();
        showCase(*s);
        if (find(closed.begin(),closed.end(),*s)==closed.end())
        {
            examined++;
            if (*s==*goal)
            {
                return s;
            }
            closed.push_back(*s);
            vector <State *> children=s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (find(closed.begin(),closed.end(),*children[i])==closed.end())
                {
                    agenda.push(children[i]);
                }
            }
        }
    }
    return nullptr;
}

State *BFS(State *initial,State *goal,long long &examined,long long &mem)
{
    queue <State *> agenda;
    vector <State> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
        {
            mem=agenda.size()+closed.size();
        }
        State *s=agenda.front();
        agenda.pop();
        showCase(*s);
        if (find(closed.begin(),closed.end(),*s)==closed.end())
        {
            examined++;
            if (*s==*goal)
            {
                return s;
            }
            closed.push_back(*s);
            vector <State *> children=s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (find(closed.begin(),closed.end(),*children[i])==closed.end())
                {
                    agenda.push(children[i]);
                }
            }
        }
    }
    return nullptr;
}

State *BestFS(State *initial,State *goal,long long &examined,long long &mem)
{
    priority_queue <State*,vector<State *>,myComparator>agenda;
    unordered_map <unsigned long,State*> closed;
    agenda.push(initial);
    mem=1;
    examined=0;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
        {
            mem=agenda.size()+closed.size();
        }
        State *s=agenda.top();
        agenda.pop();
        showCase(*s);
        if (!closed.count(s->getKey()))
        {
            examined++;
            if (*s==*goal)
            {
                return s;
            }
            pair <unsigned long,State*> k (s->getKey(),s);
            closed.insert(k);
            vector <State *> children=s->expand();
            for (unsigned int i=0;i<children.size();i++)
            {
                if (!closed.count(children[i]->getKey()))
                {
                    children.at(i)->setHvalue(children.at(i)->heuristic(goal));
                    agenda.push(children.at(i));
                }
            }
        }
    }
    return nullptr;
}

State *aStar(State *initial,State *goal,long long &examined,long long &mem)
{
    priority_queue <State*,vector<State*>,myComparator>agenda;
    vector <State*> closed;
    vector <double> cost_so_far;
    agenda.push(initial);
    closed.resize(20*20,nullptr);
    cost_so_far.resize(20*20,9999);
    cost_so_far[initial->getXZeroIndex(*initial)+20*initial->getYZeroIndex(*initial)]=0;
    examined=0;
    mem=1;
    while (agenda.size()>0)
    {
        if(agenda.size()+closed.size()>mem)
        {
            mem=agenda.size()+closed.size();
        }
        State *s=agenda.top();
        agenda.pop();
        showCase(*s);
        examined++;
        if (*s==*goal)
        {
            return s;
        }
        vector <State *> children=s->expand();
        for (unsigned int i=0;i<children.size();i++)
        {
            if(isExist(closed,children.at(i)))
            {
                double new_cost=cost_so_far[s->getXZeroIndex(*s)+20*s->getYZeroIndex(*s)]+children.at(i)->getDepth();
                if(new_cost<cost_so_far[children.at(i)->getXZeroIndex(*children.at(i))+20*children.at(i)->getYZeroIndex(*children.at(i))])
                {
                    cost_so_far[children.at(i)->getXZeroIndex(*children.at(i))+20*children.at(i)->getYZeroIndex(*children.at(i))]=new_cost;
                    closed[children.at(i)->getXZeroIndex(*children.at(i))+20*children.at(i)->getYZeroIndex(*children.at(i))]=s;
                    children.at(i)->setHvalue(children.at(i)->aStarHeuristic(goal)+new_cost);
                    agenda.push(children.at(i));

                }
            }
            children.at(i)->setHvalue(children.at(i)->aStarHeuristic(goal));
            agenda.push(children.at(i));
        }
    }
    return nullptr;
}

int main()
{
    int choise;
    long long examined,mem;
    int startBoard[3][3]={3,6,0,
                          1,4,2,
                          7,5,8};
    int finalBoard[3][3]={1,2,3,
                          4,5,6,
                          7,8,0};
    State *startPuzzle=new State(startBoard);
    State *finalPuzzle=new State(finalBoard);
    State *initial=startPuzzle;
    State *goal=finalPuzzle;
    cout<<"Which algorithm to you choose?"<<endl<<"1)Depth First Search"<<endl<<"2)Breadth First Search"<<endl<<"3)Best First Search"<<endl<<"4)A*."<<endl;
    cout<<"(Tip:Press 1,2,3 or 4 and then 'enter' to select an algorithm of the above.)"<<endl;
    cin>>choise;
    if(choise==1)
    {
        State *DFSsol=initial;
        DFSsol=DFS(initial,goal,examined,mem);
        if(DFSsol!=nullptr)
        {
            cout<<"DFS:depth="<<DFSsol->getDepth()<<",Mem:"<<mem<<",Examined:"<<examined;
        }
        else
        {
            cout<<"Problem unsolvable";
        }
    }
    if(choise==2)
    {
        State *BFSsol=initial;
        BFSsol=BFS(initial,goal,examined,mem);
        if(BFS!=nullptr)
        {
            cout<<"BFS:depth="<<BFSsol->getDepth()<<",Mem:"<<mem<<",Examined:"<<examined;
        }
        else
        {
            cout<<"Problem unsolvable";
        }
    }
    if(choise==3)
    {
        State *BestFSsol=initial;
        BestFSsol=BestFS(initial,goal,examined,mem);
        if(BestFSsol!=0)
        {
            cout<<"BestFS:depth="<<BestFSsol->getDepth()<<",Mem:"<<mem<<",Examined: "<<examined;
        }
        else
        {
            cout<<"Problem unsolvable";
        }
    }
    if(choise==4)
    {
        State *Astarsol=initial;
        Astarsol=aStar(initial,goal,examined,mem);
        if(Astarsol!=nullptr)
        {
            cout<<"A*:depth="<<Astarsol->getDepth()<<",Mem:"<<mem<<",Examined:"<<examined;
        }
        else
        {
            cout<<"Problem unsolvable";
        }
    }
    return 0;
}
