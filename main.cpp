/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MSCS
 *
 * Created on 12 March 2020, 8:38 AM
 */

#include <cstdlib>
#include <iostream>
#include "board.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    board abalone;
    string da(abalone);
    cout<<"Display Abalone Board:"<<endl;
    cout<<da;    
    cout<<"Traverse NW-SE Diagonally From E1:"<<endl;
    cout<<abalone.traverseDiagonal()<<endl;
    cout<<"Traverse W-E Horizontally From A1:"<<endl;
    cout<<abalone.traverseHorizontal()<<endl;
    return 0;
}

