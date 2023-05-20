/*

Kupiwa Nangati
Sithembiso Ntanzi
Munazzah Hassan
Ntandokayise Cele
Mthokozisi Nxumalo



 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "board.h"
#include <iomanip>
#include <iostream>
#define ESC "\033["
#define RED_TXT "31"
#define GREEN_TXT "32"
#define RESET "\033[m"
string traverse(const board& abalone, const cell* start,const int& pd,const int& sd,const int& td){
    string ts;
    const cell* linep = start;
    while(linep!=nullptr){
        const cell* cellp = linep;
        while(cellp!=nullptr){
            string location = cellp->getLocation();
            ts+=(location+' '); 
            cellp = abalone.getCell(cellp, location, td);
        }
        if(linep->getAdjacent(pd)==nullptr)
            linep=abalone.getCell(linep, linep->getLocation(), sd);
        else
            linep=abalone.getCell(linep, linep->getLocation(), pd);
    }
    return ts;
}

//Jump over obstacle
const cell* board::getCell(const cell* cell, const string& location, const int& direction) const{
    
    if (location == "D4" && direction == 0)
            return cells.at("F6");
    if (location == "E4" && direction == 1)
            return cells.at("E6"); 
    if (location == "F5" && direction == 2)
            return cells.at("D5"); 
    if (location == "F6" && direction == 3)
            return cells.at("D4"); 
    if (location == "E6" && direction == 4)
            return cells.at("E4");
    if (location == "D5" && direction == 5)
            return cells.at("F5");
    
    return cell->getAdjacent(direction);
}

void setMarbles(cell* row,const int& z, const char& m, const bool& topSection){
    
    if(topSection){  //Top half of the board
        for(int i=0;i<z;i++){
            if(i > 1 && i < z-2){
                row[i].setMarble(m);
            }
            else{
                     row[i].setMarble('-'); //Sets disable cells to"-"
                }
        }

         if (z==9){ //Obstacle addition
                char pos[1]={4};
                row[pos[0]].setMarble('*');
              
            }
    }

    else if(!topSection){ //Bottom-Half of the board
        for(int i=0;i<z;i++){

            if(z==8){
                 if(i > 0 && i < z-1){
                    row[i].setMarble(m);
                }
                else{
                     row[i].setMarble('-'); //Sets disable cells to"-"
                }
            }

           

            else if(z==7){
                 row[i].setMarble('+');
            }
            else if(z ==6){
                 row[i].setMarble(m);
            }

            
    
            else{
                row[i].setMarble('-');  //Sets disable cells to"-"
            }
            
            
        }


    }


}
void connectHorizontal(cell* row, const int& rz, const bool& topSection){
   
    if (topSection){
        if (rz == 9){  //Row E
           for(int i=2;i<rz-3;i++){
                if (i != 4 && i != 3)   //Disconnecting obstacle's horizontal cell neighbours in row E
                    row[i].setAdjacent(row+i+1,1);   //Sets non-obstacle horizontal cell neighbours in row E
            }
        } else {
             for(int i=2;i<rz-3;i++){
                row[i].setAdjacent(row+i+1,1); //Sets horizontal cell neighbours in the top half  of the board
            }
        }
    }
    else { //Bottom-half of the board
        if (rz == 8){
            for(int i=1;i<rz-2;i++){
                row[i].setAdjacent(row+i+1,1);
            }
        }
        else if (rz != 5){ //Sets horizonal cell neighbours besides row A
            for(int i=0;i<rz-1;i++){
                row[i].setAdjacent(row+i+1,1);
            }
        }
    }
}

void connectDiagonal(cell* lrow,cell* srow,const int& f,const int& sz,const bool& top){
    
    if(top){
        for(int i=f+2;i<(f+sz-2);i++){
            if(f==0){//connecting from cell 0 in longer row 
                if(sz == 8) {
                    if (i != 4) //Avoids creating a diagonal connection with our obstacle
                       lrow[i].setAdjacent(srow+i,0);
                    // lrow[4].setAdjacent(srow+4,0);
                } 
                else
                    lrow[i].setAdjacent(srow+i,0);
            }
            else if(f==1){//connecting from cell 1 in longer row
                if(sz == 8) {
                    if (i != 4) { //Avoids creating a diagonal connection with our obstacle
                        lrow[i].setAdjacent(srow+i-1,5);
                    }
                }
                else
                    lrow[i].setAdjacent(srow+i-1,5);
            }
            else return;
        }
    }

    else { //Bottom-half of the board
        if (sz == 7){
            for (int i=f;i<(f+sz-1);i++){
                if(f==0){
                    srow[i].setAdjacent(lrow+i+1,0);
                }
                else if(f==1){
                    srow[i].setAdjacent(lrow+i,5);
                }
                else return;            
            }
        } else if (sz == 8){
            for (int i=f+1;i<(f+sz-2);i++){
                if(f==0){
                    if (i != 3) //Avoids creating a diagonal connection with our obstacle
                        srow[i].setAdjacent(lrow+i+1,0);
                }
                else if(f==1){
                    if (i != 4) //Avoids creating a diagonal connection with our obstacle
                    srow[i].setAdjacent(lrow+i,5);
                }
                else return;            
            }
        }
        else if (sz == 6){
            for (int i=f;i<(f+sz);i++){
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
}
void board::mapCells(cell* row,const char& r,const int& z){    
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
        cells[lc]=row+i;
    }
}
board::board():woc(0),boc(0){
    char r = 'I';
    for(int i=0;i<9;i++){
        if(i<5){
            rows.push_back(new cell[5+i]);
            connectHorizontal(rows[i],5+i, true);
            mapCells(rows[i],r--,5+i);
            if(i<3){
                setMarbles(rows[i],5+i,'O',true);
            }else
                setMarbles(rows[i],5+i,'+',true);
        }
        else{
            rows.push_back(new cell[5+8-i]);
            connectHorizontal(rows[i],5+8-i, false);
            mapCells(rows[i],r--,5+8-i);
            if(i>=6){
                setMarbles(rows[i],5+8-i,'@',false);
            }else
                setMarbles(rows[i],5+8-i,'+',false);
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
    cell* linep = rows[0]+2;//start at I7cell* linep = rows[0];//start at I5
    while(linep!=nullptr){
        cell* cellp = linep;
        while(cellp!=nullptr){
            for(int i=0;i<6;i++){
                cellp->setDistanceToEdge(i);
            }
            cellp=cellp->getAdjacent(1);
        }
        if(linep->getAdjacent(3)==nullptr)
            linep=linep->getAdjacent(2);
        else
            linep=linep->getAdjacent(3);
    }
}

board::board(const board& copy): board(){//constructor delegation - C++11
    woc=copy.woc;
    boc=copy.boc;
    map<string,cell*>::const_iterator it = copy.cells.begin();
    while(it!=copy.cells.end()){
        (cells[it->first])->setMarble((*(it->second)).getMarble());
        it++;
    }

    
}
map<string,cell*> board::getCells() const{
    return cells;
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
                  if (rows[i][k].getMarble()=='-' || rows[i][k].getMarble()=='*'){
                    ss<<ESC<< ";" << RED_TXT <<"m"<<rows[i][k].getMarble()<<" "<<RESET; //Colour coded marbles to act as a barrier
                }
                else{
                    ss<<rows[i][k].getMarble()<<" ";
                }
            }
            ss<<endl;
            r--;
        }
        else{
            ss<<setw(i-3)<<r<<" ";
            for(int k=0;k<5+8-i;k++){
                  if (rows[i][k].getMarble()=='-' || rows[i][k].getMarble()=='*'){
                    ss<<ESC<< ";" << RED_TXT <<"m"<<rows[i][k].getMarble()<<" "<<RESET; //Colour coded marbles to act as a barrier
                }
                else{
                    ss<<rows[i][k].getMarble()<<" ";
                }
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
    
    int b = 0;
    for(int i=0;i<woc;i++) { 
        // ss<<'O'<<" ";
        b += 1; //Black marble Score counter
    }
    int w = 0;
    for(int i=0;i<boc;i++) {
        
        w += 1; //White marble Score counter
    }   
        
        string s = "  ";
        int i = 0;
        for(; i < b; i++) {
            s[i] = 'O';  //Appending the white marbles of the board
        }
        // s[i] = ')';
        
        string m = "  ";
        int x = 0;
        for(; x < w; x++) {
            m[x] = '@';  //Appending the black marbles of the board
        }
        // m[x] = ')';

        

        //Score board display
        ss<<endl;
        ss << "-------------------------------------------------------\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n||||                                               ||||\n||||    SCOREBOARD:                                ||||\n||||                                               ||||\n||||    Black:  " << b << " " << ESC<< ";" << RED_TXT <<"m"<< s << RESET <<"                               ||||" << "\n||||                                               ||||\n||||    White:  " << w << " " << ESC<< ";" << RED_TXT <<"m"<<m << RESET <<"                               ||||" << "\n||||                                               ||||\n||||_______________________________________________||||\n|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n-------------------------------------------------------" << endl;
        ss<<endl;
        ss<<endl;
        ss<<endl;
    return ss.str();
}

string board::traverseDiagonal() const{
    map<string,cell*>::const_iterator it = cells.find(string("I7"));
    cell* start = it->second;
    return traverse(*this,start,3,2,2); 
}
string board::traverseHorizontal() const{
    map<string,cell*>::const_iterator it = cells.find(string("I7"));
    cell* start = it->second;
    return traverse(*this,start,2,3,3);
}

bool board::validateMove(const char& m,const string& l,const int& n, const int& fd, const int& md, int& mtype, bool& scoreMove) const{
    if(!cell::validateLocation(l))//confirm existence of location
        return false;
    else{        
        cell* cp = cells.at(l);//initialize to leading cell
        const char marble = cp->getMarble();
        if(marble!=m)//trying to move a space or a marble that is not yours
            return false;
        for(int i=1;i<n;i++){
            cp=cp->getAdjacent(fd);
            if(cp==nullptr || marble!=cp->getMarble())//confirm availability and type of claimed resources
                return false;
        }
        if(fd==getAdjacentIndex(md)){//in-line move
            cp = cells.at(l);//initialize to leading cell
            mtype=0;//how many opponent marbles are in front of the leading marble i.e in the move direction
            for(int i=0;i<n;i++){
                cp=cp->getAdjacent(md);
                if(cp!=nullptr){//confirm availability of required resources
                    if(marble==cp->getMarble())//met own marble instead of space
                        return false;
                    if('+'!=cp->getMarble())//if it belongs to opponent
                        mtype++;//count opponent marbles
                    else
                        break;
                }
                else{
                    if(mtype>0)//opponent's marble will be pushed off the board
                        scoreMove=true;
                    else//if trying to push your own marble off the board
                        return false;
                    break;
                }
            }
            if(mtype>=n)//should only push fewer than n of the opponent's marbles
                return false;
        }
        else{//broad-side move
            mtype=-1;
            if(n<=1)//broad-side move must use at least 2 marbles
                return false;
            cp = cells.at(l);
            for(int i=0;i<n;i++){
                cell* dp=cp->getAdjacent(md);//destination pointer
                if(dp!=nullptr && '+' == dp->getMarble())//is there an empty space to move to?
                    cp=cp->getAdjacent(fd);
                else
                    return false;
            }
        }
        return true;
    }
}

bool board::executeMove(const char& m,const string& l,const int& n, const int& fd, const int& md){
    int moveType = 0;//default to in-line with no following marbles
    bool scoreMove = false;
    bool valid = validateMove(m,l,n,fd,md,moveType,scoreMove);
    if(valid){
        if(moveType==-1){//broad-side
            if(cells.find(l)==cells.end()) return false;
            cell* cp = cells.at(l);
            for(int i=0;i<n;i++){
                if(cp==nullptr) return false;
                cell* dp=cp->getAdjacent(md);//destination pointer
                if(dp==nullptr) return false;
                dp->setMarble(cp->getMarble());
                cp->setMarble('+');
                cp=cp->getAdjacent(fd); 
            }
        }
        else{//in-line
            cell* cp = cells.at(l), *rearp=cp;
            const char marble = cp->getMarble();
            cell* frontp=cp->getAdjacent(md);
            for(int i=1;i<n;i++){
                rearp=rearp->getAdjacent(fd);
            }
            if(scoreMove){                
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+'); 
                if(marble=='O')
                    boc++;
                if(marble=='@')
                    woc++;
            }
            else{
                cell* tipp = frontp;
                for(int i=0;i<moveType;i++){
                    tipp=tipp->getAdjacent(md);//looking for empty space
                }
                if(moveType!=0)//tipp is already equal to frontp
                    tipp->setMarble(frontp->getMarble());
                frontp->setMarble(rearp->getMarble());
                rearp->setMarble('+');
            }
        }
    }
    return valid;
}
bool board::inPlay() const{
    if((woc<2) && (boc<2))
        return true;

    //Message to display if either marbles win the game
    if(woc >= 2) {
        cout << "-----------------------------\n||||" <<ESC<< ";" << GREEN_TXT <<"m"<<"    Black Wins!!!    "<<RESET<<"||||\n-----------------------------\n" << endl;
    }
    else if(boc >=2) {
        cout << "-----------------------------\n||||" <<ESC<< ";" << GREEN_TXT <<"m"<<"    White Wins!!!    "<<RESET<<"||||\n-----------------------------\n" << endl;

    }
    return false;
}
void board::refreshOffboardCounts(){
    int wOnBoard = 0;
    int bOnBoard = 0;
    
    map<string,cell*>::const_iterator it = cells.begin();
    while(it!= cells.end()){
        if((cells[it->first])->getMarble() == 'O'){
            wOnBoard++;
        }
        if((cells[it->first])->getMarble() == '@'){
            bOnBoard++;
        }
        it++;
    }
    
    woc = 6 - wOnBoard;
    boc = 6 - bOnBoard;
}
