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
#include <csignal>
#ifdef _WIN32
    #include <windows.h>
#endif

using namespace std;

board abalone;
agent* w=nullptr;
agent* b=nullptr;
movement* pom=nullptr;//previous opponent's move
movement* mym=nullptr;


//Deallocates memory
void cleanUp(){ 
    if (w)
        delete w;
    if (b)
        delete b;
    if (pom)
        delete pom;
    if (mym)
        delete mym;
}

#ifdef _WIN32 //Checks if the terminal was paused in Windows
    BOOL WINAPI signalHandler(DWORD signal) { 
        if (signal == CTRL_C_EVENT) {
            std::cout << "\nPaused" << std::endl;
            cleanUp();
        }
        return false;
    }
#endif
#ifdef __unix__ //Checks if the terminsl was paused iin Unix
    void signalHandler(int signal) {
        if (signal == SIGINT) {
            std::cout << "\n\nPaused\n" << std::endl;
            cleanUp();
        }
        std::exit(0);
    }
#endif

int main(int argc, char** argv) {

    #ifdef __unix__
        std::signal(SIGINT, signalHandler);
    #endif

    #ifdef _WIN32
        SetConsoleCtrlHandler(signalHandler, TRUE);
    #endif

   // Welcome Board
    std::cout << "-----------------------------------------------" << endl;
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    std::cout << "||||                                       ||||" << endl;
    std::cout << "||||                            O          ||||" << endl;
    std::cout << "||||      WELCOME              O O         ||||" << endl;
    std::cout << "||||           TO             O O O        ||||" << endl;
    std::cout << "||||               ABALONE   O O O O       ||||" << endl;
    std::cout << "||||                                       ||||" << endl;
    std::cout << "||||_______________________________________||||" << endl;
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||" << endl;
    std::cout << "-----------------------------------------------" << endl;
    //Options for the game
    std::cout << "Enter a number between(1-3): "<<endl;
    std::cout << "1 - New Game"<<endl;
    std::cout << "2 - Replay"<<endl;
    std::cout << "3 - Resume"<<endl;
    
    int num = 0; // Variable for Option chosen
    //ofstream storeSeed("storeSeed.txt");

    //ofstream lastMove("moves.txt");


    cin >> num; //  Option chosen
    int diff =0; // Variable for Difficulty chosen
    if (num == 1){
        std::cout << "Enter difficulty level (1: easy/2: hard): ";  
        cin >> diff ; // Difficulty chosen

        ofstream storeSeed("storeSeed.txt");
        storeSeed << diff << endl;
        if (diff == 1){

            time_t now = time(NULL); // store the now object into a file.
            srand(now); // replay several games

            // store the now object into a file and then 
            
            storeSeed<<now;
            storeSeed.close();
            


            std::cout<<"Seed: "<<now<<endl;
            string state(abalone);
            std::cout<<"Initial State:"<<endl<<state;

         //  cout << abalone.traverseDiagonal()<<endl;
          
          
          // cout << abalone.traverseHorizontal() <<endl;

            w = new easyAgent('O');
            b = new distAgent('@');
            char c='O';
            int i = 0;
            while(abalone.inPlay()){//for(int i=0;i<200;i++){
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
                    cleanUp();
                    std::cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                std::cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    std::cout<<"Next State:"<<endl<<state; 
                }
                else{
                    std::cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(0.2);
                //system(CL);

                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
                i++;
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

            storeSeed<<now;
            storeSeed.close();

            std::cout<<"Seed: "<<now<<endl;
            string state(abalone);
            std::cout<<"Initial State:"<<endl<<state;
            w = new distAgent('O');
            b = new distAgent('@');
            char c='O';
            int i = 0;
            while(abalone.inPlay()) {
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
                    cleanUp();
                    std::cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                std::cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    std::cout<<"Next State:"<<endl<<state; 
                }
                else{
                    std::cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
               // SLP(1);
                //system(CL);
                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
                i++;
            }
            if(pom)
                delete pom;
            delete w;
            delete b;
            
            return 0;           
        }

    

    }
    else if (num == 2 ){
          

            ifstream storeSeed("storeSeed.txt");
            
            int now;
            int diff;
            
            string line;
            getline(storeSeed, line);
            stringstream ss(line);
            ss>>diff;

            getline(storeSeed, line);
            stringstream zz(line);
            zz>>now;
            
            
            srand(now); // replay several games

     

            string state(abalone);
            std::cout<<"Initial State:"<<endl<<state;
           
            if(diff == 1)
                w = new easyAgent('O'); // white should always win
            
            else
                w = new distAgent('O');
               
               

            b = new distAgent('@'); 


            char c='O';
            int n = 5;
            int i = 0;
            while(abalone.inPlay()){
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
                    cleanUp();
                    std::cout<<s;
                    return 1;
                }        
                bool valid=abalone.executeMove(c,mym->l,mym->n,mym->fd,mym->md);
                std::cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                if(valid){
                    string state(abalone);         
                    std::cout<<"Next State:"<<endl<<state; 
                }
                else{
                    std::cout<<"Invalid move!!"<<endl;
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                SLP(0.1);
                //system(CL);
                ofstream lastMove("moves.txt");
                lastMove<<i;
                lastMove.close();
                i++;
            }
            if(pom)
                delete pom;
            delete w;
            delete b;

            storeSeed.close();
            
            return 0;      
         
    }
    

    else if (num == 3){
            cout<<"Game Resumed" <<endl;
            ifstream storeSeed("storeSeed.txt");
            
            int now;
            int diff;
            
            string line;
            getline(storeSeed, line);
            stringstream ss(line);
            ss>>diff;

            getline(storeSeed, line);
            stringstream zz(line);
            zz>>now;
            
            
            srand(now); // replay several games

           
        
            if(diff == 1)
                w = new easyAgent('O'); // white should always win
            
            else
                w = new distAgent('O');

            b = new distAgent('@');
            char c='O';
            int n = 5;
            int i = 0;
            while(abalone.inPlay()){
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
                    cleanUp();
                    std::cout<<s;
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
                    std::cout<<"Move "<<i+1<<": "<<c<<","<<mym->l<<","<<mym->n<<","<<mym->fd<<","<<mym->md<<endl;
                    if(valid){
                        string state(abalone);         
                        std::cout<<"Next State:"<<endl<<state; 
                    }
                    else{
                        std::cout<<"Invalid move!!"<<endl;
                    }
                    SLP(1);
                    ofstream lastMove("moves.txt");
                    lastMove<<i;
                    lastMove.close();
                }
                if(c=='O') 
                    c='@';
                else
                    c='O'; 
                delete mym;
                //system(CL);
                i++;
            }
            if(pom)
                delete pom;
            delete w;
            delete b;

            storeSeed.close();
            
            return 0;      
    }

    else{
        std::cout << "Enter a number between 1 and 3" << endl;
    }
}
