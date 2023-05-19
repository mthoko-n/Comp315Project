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
#include <fstream>
#include <time.h>
#include "board.h"
#include "agent.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {


   // Welcome Board
    cout << "-----------------------------------------------" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "||||                                       ||||" << endl;
    cout << "||||                            O          ||||" << endl;
    cout << "||||      WELCOME              O O         ||||" << endl;
    cout << "||||           TO             O O O        ||||" << endl;
    cout << "||||               ABALONE   O O O O       ||||" << endl;
    cout << "||||                                       ||||" << endl;
    cout << "||||_______________________________________||||" << endl;
    cout << "|||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    cout << "-----------------------------------------------" << endl;
    //Options for the game
    cout << "Enter a number between(1-3): "<<endl;
    cout << "1 - New Game"<<endl;
    cout << "2 - Replay"<<endl;
    cout << "3 - Resume"<<endl;
    
    int num = 0; // Variable for Option chosen
    //ofstream storeSeed("storeSeed.txt");

    //ofstream lastMove("moves.txt");


    cin >> num; //  Option chosen
    int diff =0; // Variable for Difficulty chosen
    if (num == 1){
        cout << "Enter difficulty level (1: easy/2: hard): ";  
        cin >> diff ; // Difficulty chosen

        if (diff == 1){

            time_t now = time(NULL); // store the now object into a file.
            srand(now); // replay several games

            // store the now object into a file and then 
            ofstream storeSeed("storeSeed.txt");
            storeSeed<<now<<endl;
            storeSeed.close();


            cout<<"Seed: "<<now<<endl;
            board abalone;
            string state(abalone);
            cout<<"Initial State:"<<endl<<state;
            agent* w = new randAgent('O');
            agent* b = new distAgent('@');
            movement* pom=nullptr;//previous opponent's move
            movement* mym=nullptr;//player's chosen move
            char c='O';
            for(int i=0;i<200;i++){
                try{
                    if(c=='O'){
                        movement mm = w->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                    else{
                        movement mm = b->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                }
                catch(const string& s){
                    cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    cout<<"Next State:"<<endl<<state; 
                }
                else{
                    cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(1);
                //system(CL);

                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
            }
            if(pom)
                delete pom;
            delete w;
            delete b;
            
            return 0;           
        }

        else if (diff == 2){
            time_t now = time(NULL);
            srand(now);
            cout<<"Seed: "<<now<<endl;
            board abalone;
            string state(abalone);
            cout<<"Initial State:"<<endl<<state;
            agent* w = new distAgent('O');
            agent* b = new distAgent('@');
            movement* pom=nullptr;//previous opponent's move
            movement* mym=nullptr;//player's chosen move
            char c='O';
            for(int i=0;i<200;i++){
                try{
                    if(c=='O'){
                        movement mm = w->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                    else{
                        movement mm = b->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                }
                catch(const string& s){
                    cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    cout<<"Next State:"<<endl<<state; 
                }
                else{
                    cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(1);
                //system(CL);
                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
            }
            if(pom)
                delete pom;
            delete w;
            delete b;
            
            return 0;           
        }

    

    }
    else if (num == 2 ){
            //Munazzah & Kupiwa & Ntando
            //time_t now = time(NULL); // store the now object into a file.

            ifstream storeSeed("storeSeed.txt");
            int now;
            string line;
            getline(storeSeed, line);
            //now = stoul(line);
            stringstream ss(line);
            ss>>now;
            srand(now); // replay several games

            //ofstream lastMove("moves.txt");

            board abalone;
            string state(abalone);
            cout<<"Initial State:"<<endl<<state;
            agent* w = new randAgent('O');
            agent* b = new distAgent('@');
            movement* pom=nullptr;//previous opponent's move
            movement* mym=nullptr;//player's chosen move
            char c='O';
            int n = 5;
            for(int i=0;i<200;i++){
                try{
                    if(c=='O'){
                        movement mm = w->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                    else{
                        movement mm = b->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                }
                catch(const string& s){
                    cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    cout<<"Next State:"<<endl<<state; 
                }
                else{
                    cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(1);
                //system(CL);
                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
            }
            if(pom)
                delete pom;
            delete w;
            delete b;

            storeSeed.close();
            
            return 0;      
         
    }
    

    else if (num == 3){
        //Ntando & Kupiwa & Munazzah
            ifstream storeSeed("storeSeed.txt");
            int now;
            string line;
            getline(storeSeed, line);
            stringstream ss(line);
            ss>>now;
            srand(now); // replay several games

            board abalone;
            string state(abalone);
            
            agent* w = new randAgent('O');
            agent* b = new distAgent('@');
            movement* pom=nullptr;//previous opponent's move
            movement* mym=nullptr;//player's chosen move
            char c='O';
            int n = 5;
            for(int i=0;i<200;i++){
                try{
                    if(c=='O'){
                        movement mm = w->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                    else{
                        movement mm = b->move(pom,abalone);
                        mym = new movement(mm);
                        if(pom)
                            delete pom;
                        pom = new movement(mm);
                    }
                }
                catch(const string& s){
                    cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);

                ifstream lastM("moves.txt");
                int lastMoveReadFromFile;
                string line;
                while(getline(lastM, line)) {
                    stringstream ss(line);
                    ss>>lastMoveReadFromFile;
                }
             
                if(i > lastMoveReadFromFile) {
                    cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                    if(valid){
                        string state(abalone);         
                        cout<<"Next State:"<<endl<<state; 
                    }
                    else{
                        cout<<"Invalid move!!"<<endl;
                    }
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(1);
                //system(CL);
            }
            if(pom)
                delete pom;
            delete w;
            delete b;

            storeSeed.close();
            
            return 0;      
    }

    else{
        cout << "Enter a number between 1 and 3" << endl;
    }


    /*
    
    Ntando and Kupiwa will be adding an obstacle on their own specified location (E)
    
    
    */

    /*
    
    Mthoko , Munazzah , Sthembiso will modify the shape of board
    
    
    */



}




  





