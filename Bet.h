/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bet.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 3:29 PM
 */

#ifndef BET_H
#define BET_H
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
enum{anteType, insuranceType, evenMoneyType, splitType, doubleDownType};
class Bet {
private:
    float betAmount;
    int betType;;
    float amountWon;
    bool won;
    int indx;
    bool isTie;
public:
    Bet(){
        this->betAmount = 0;
        this->betType = 0;
        this->amountWon = 0;
        this->won = false;
        this->indx = -1;
        this->isTie = false;
    }
    Bet(float amount, int betType, int indx);
    float getWinnings(bool blackjack);
    void tie();
    float getBetAmount()const{return betAmount;}
    int getBetType()const{return betType;}
    int getIndx()const{return indx;}
    string getStringBet();
    string toStringBet(float betAmount);
    string toStringType(int type);
    bool getWon()const{return won;}
    bool getTie()const{return isTie;}

};

#endif /* BET_H */

