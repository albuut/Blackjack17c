/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Login.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 12:00 PM
 */

#ifndef LOGIN_H
#define LOGIN_H
#include "Player.h"
#include <fstream>
#include <map>
#include <iterator>
#include <iomanip>
#include <functional>
class Login {
private:
    map<string,Player> playerList;
    Player player = Player("Guest","Password",25000,0,0);
    bool online;
    hash<string> str_hash;
protected:
    string fileNamePlayer = "playerData.txt";
public:
    Login();
    bool logon();
    bool checkLogin(string username, string password);
    void createUser(string username, string password);
    bool validateUsername(string username);
    void getPlayers();
    Player getPlayer();
    void updatePlayers();
    void updatePlayer(const Player &current);
    bool getOnline();
    void loginHeader();
    bool loginChoice();
    void clear();
    bool caseless_match(string, string);
    
    

};

#endif /* LOGIN_H */

