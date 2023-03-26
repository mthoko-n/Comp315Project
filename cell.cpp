/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "cell.h"
#include <iostream>
int getAdjacentIndex(const int& i){
    if(i<3)
        return i+3;
    else
        return i-3;
}
char cell::getMarble()const{
    return marble;
}
void cell::setMarble(const char& m){
    if(m=='O' || m=='@' || m=='+'){
        marble=m;
    }
}

cell* cell::getAdjacent(const int& i)const{
    return adjacent.at(i);
}
void cell::setAdjacent(cell* a,const int& i){
    if(adjacent.at(i)==nullptr){
        adjacent.at(i)=a;
        a->setAdjacent(this,getAdjacentIndex(i));
    }
}
string cell::getLocation() const{
    return location;
}
void cell::setLocation(const string& l){
    if(l.size()==2 && l[0]>='A' && l[0]<='I' && l[1]>='1' && l[1]<='9'){
        location = l;
    }
    else{
        throw "Invalid Location!";
    }
    
}

cell::cell(){
    for(int i=0;i<6;i++){
        adjacent.push_back(nullptr);
    }
}
