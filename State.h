#ifndef STATE_H
#define STATE_H
#include <sstream>
#include <string>
#include <vector>
#define HEIGHT 3
#define WIDTH 3

using namespace std;

class State
{
    public:
        State();
        State(int A[HEIGHT][WIDTH]);
        int getDepth();                            //Returns the depth of the final path
        bool operator==(const State&)const;        //Checks if 2 states are the same(if the current state is final or it exists in closed set)
        State operator=(State);
        int getBoardIndex(int,int);
        void setBoardIndex(int,int,int);
        double getHvalue();
        void setHvalue(double);
        bool goUp(State &,int,int);                //Checks if we can move a block up
        bool goDown(State &,int,int);              //Checks if we can move a block down
        bool goLeft(State &,int,int);              //Checks if we can move a block left
        bool goRight(State &,int,int);             //Checks if we can move a block right
        int getXZeroIndex(State &);
        int getYZeroIndex(State &);
        vector <State *> expand();                 //It returns all successors children for a state
        State *getPrevious()const{return prev;}
        void setPrevious(State *p){prev=p;}
        int heuristic(State *);                    //Heuristic method using Manhattan distance
        int aStarHeuristic(State *);               //Heuristic method for A* algorithm using Manhattan distance
        unsigned long getKey();
    private:
        int board[HEIGHT][WIDTH];
        double Hvalue;
        State *prev;
};

class myComparator                                 //Class using Heuristic method
{
    public:
        int operator()(State *p1,State *p2)const
        {
            return p1->getHvalue()>p2->getHvalue();
        }
};

#endif // STATE_H
