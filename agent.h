/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   agent.h
 * Author: MSCS
 *
 * Created on 21 July 2020, 7:19 AM
 */

#ifndef AGENT_H
#define AGENT_H

#include "board.h"
#include "cell.h"
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>

#ifndef _SLP_CL_EG
   #define _SLP_CL_EG
   #define C(x) #x 
   #ifdef _WIN32
     	#define SLP(t) Sleep(t*1000)
     	#include <windows.h> 
     	#define CL C(cls)
   #endif
   #ifdef unix
      #define SLP(t) sleep(t)
      #include <unistd.h>
      #define CL C(clear)
   #endif
#endif

struct movement{
    string l;//location
    int n;//number of current player's marbles moving
    int fd;//direction from leading marbles to following marbles
    int md;//direction in which n marbles seek to move
    int d2e;//distance from leading marble to the edge of the board in move direction
    int mtype;//-1 broad-side 0-2 for in-line depending on how many opponent marbles are to be pushed
    bool scoreMove;//opponent marble to be pushed off the board?
    movement(const string&,const int&,const int&,const int&,const int&,const int&,const bool&);
    movement(const movement&);
};
double score(const movement&);
struct moveTNDPriority{//priority based on move types and distance to edge    
   inline bool operator()(const movement& a, const movement& b) {
       return score(a)<score(b);
   }     
}; 
class agent{
protected:
    char symbol;
    vector<vector<int> > pmd;//potential move details.
    vector<movement> findMoves(const board&) const;
public:
    agent(const char&);
    char getSymbol(){return symbol;}
    virtual movement move(movement const* const,board)=0;//pure virtual function
};

class randAgent: public agent{
public:
    randAgent(const char&);
    movement move(movement const* const,board);
};
class distAgent: public agent{
public:
    distAgent(const char&);
    movement move(movement const* const,board);
};


#endif /* AGENT_H */

