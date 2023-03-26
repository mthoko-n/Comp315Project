/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "board.h"
#include <iomanip>
#include <iostream>
string traverse(const cell* start,const int& pd,const int& sd,const int& td){
    string ts;
    const cell* linep = start;
    while(linep->getAdjacent(pd)!=nullptr || linep->getAdjacent(sd)!=nullptr){
        const cell* cellp = linep;
        while(cellp!=nullptr){
            ts+=(cellp->getLocation()+'');
            cellp=cellp->getAdjacent(td);
        }
        if(linep->getAdjacent(pd)==nullptr)
            linep=linep->getAdjacent(sd);
        else
            linep=linep->getAdjacent(pd);
    }
    const cell* cellp = linep;
    while(cellp!=nullptr){
        ts+=(cellp->getLocation()+' ');
        cellp=cellp->getAdjacent(td);
    }
    return ts;
}
void setMarbles(cell* row,const int& z, const char& m){
    for(int i=0;i<z;i++){
        row[i].setMarble(m);
    }
    if(z==7){
        char pos[4]={0,1,5,6};
        for(int i=0;i<4;i++){
            row[pos[i]].setMarble('+');
        }
    }
}
void connectHorizontal(cell* row, const int& rz){
    for(int i=0;i<rz-1;i++){
        row[i].setAdjacent(row+i+1,1);
    }  
}

void connectDiagonal(cell* lrow,cell* srow,const int& f,const int& sz,const bool& top){
    for(int i=f;i<(f+sz);i++){
        if(top){
            if(f==0){//connecting from cell 0 in longer row
                lrow[i].setAdjacent(srow+i,0);
            }
            else if(f==1){//connecting from cell 1 in longer row
                lrow[i].setAdjacent(srow+i-1,5);
            }
            else return;
        }
        else{
            if(f==0){
                lrow[i].setAdjacent(srow+i,2);
            }
            else if(f==1){
                lrow[i].setAdjacent(srow+i-1,3);
            }
            else return;
            
        }
    }
}
void mapCells(cell* row,map<string,cell*>& cm,const char& r,const int& z){    
    int f=1;
    if(r>='A'&& r<='E'){
        f=1;
    }else if(r>'E'&& r<='I'){
        f=r-'E'+1;
    }else return;
    for(int i=0;i<z;i++){
        stringstream ss;
        ss<<r;
        ss<<(i+f);
        string lc = ss.str();
        row[i].setLocation(lc);
        cm[lc]=row+i;
    }
}
board::board(){
    char r = 'I';
    for(int i=0;i<9;i++){
        if(i<5){
            rows.push_back(new cell[5+i]);
            connectHorizontal(rows[i],5+i);
            mapCells(rows[i],cells,r--,5+i);
            if(i<3){
                setMarbles(rows[i],5+i,'O');
            }else
                setMarbles(rows[i],5+i,'+');
        }
        else{
            rows.push_back(new cell[5+8-i]);
            connectHorizontal(rows[i],5+8-i);
            mapCells(rows[i],cells,r--,5+8-i);
            if(i>=6){
                setMarbles(rows[i],5+8-i,'@');
            }else
                setMarbles(rows[i],5+8-i,'+');
        }
    }
    for(int i=1;i<9;i++){
        if(i<5){
            connectDiagonal(rows[i],rows[i-1],0,5+i-1,true);
            connectDiagonal(rows[i],rows[i-1],1,5+i-1,true);
        }
        else{
            connectDiagonal(rows[i-1],rows[i],0,5+8-i,false);
            connectDiagonal(rows[i-1],rows[i],1,5+8-i,false);
        }
    }
}
board::~board(){
    for(int i=0;i<9;i++){
        delete[] rows[i];
        rows[i]=nullptr;
    }
    cells.clear();
}

board::operator std::string() const{
    stringstream ss;
    char r ='I';
    int d=9;
    for(int i=0;i<9;i++){
        if(i<5){
            ss<<setw(5-i)<<r<<" ";
            for(int k=0;k<5+i;k++){
                ss<<rows[i][k].getMarble()<<" ";
            }
            ss<<endl;
            r--;
        }
        else{
            ss<<setw(i-3)<<r<<" ";
            for(int k=0;k<5+8-i;k++){
                ss<<rows[i][k].getMarble()<<" ";
            }
            ss<<d<<endl;
            r--;
            d--;
        }
    }
    d=1;
    ss<<setw(8)<<d++<<" ";
    for(;d<6;d++)
        ss<<d<<" ";
    ss<<endl;
    return ss.str();
}

string board::traverseDiagonal() const{
    //backward diagonal - nw to se
    /*
    map<string,cell*>::const_iterator it = cells.find(string("A1"));
    cell* start = it->second;
    return traverse(start,1,0,5); 
    */ 
    //forward diagonal - sw to ne
    /**/
    map<string,cell*>::const_iterator it = cells.find(string("E1"));
    cell* start = it->second;
    return traverse(start,0,1,2); 
    /**/
}
string board::traverseHorizontal() const{
    map<string,cell*>::const_iterator it = cells.find(string("A1"));
    cell* start = it->second;
    return traverse(start,5,0,1);
}