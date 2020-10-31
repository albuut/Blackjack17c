/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 11:44 AM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;
class Player {
private:
    string username;
    string password;
    float money;
    int handsPlayed;
    int handsWon;
    string fileNamePlayer = "playerData.txt";
    map<string,Player> playerList;
    
public:
    Player(string username, string password, float money, int handsPlayed, int handsWon);
    Player(const Player &player);
    void modBal(float money);
    string getUsername()const{return this->username;}
    string getPassword()const{return this->password;}
    float getMoney()const{return this->money;}
    int getHandsPlayed()const{return this->handsPlayed;}
    int getHandsWon()const{return this->handsWon;}
    void handPlayed(int i){handsPlayed += i;}
    void handWon(){handsWon++;}
    void getPlayerList();
    void update(const Player &current);
    void updateList();
};

#endif /* PLAYER_H */

