/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 1:44 PM
 */

#ifndef TABLE_H
#define TABLE_H
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
#include "Bet.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <bits/stdc++.h>

class Table {
private:
    map <int,Hand> playerHand;
    list<Card> dealerHand;
    queue<Bet> playerBet;
    Deck deck;
    Player player = Player("Guest","Password",25000,0,0);
    bool dealerTurn = false;
    int bet;
    int numHands;
    set<int> handOrder;
public:
    Table(const Player &player);
    void play();
    void dealCards(float amount);
    bool hit(int i);
    bool doubleDown(int i);
    void insurance(int i);
    void evenMoney(int i);
    void split(int i);
    bool choice();
    void win();
    int dealerValue();
    Player getPlayer();
    void header();
    void cls();
    void printHand();
    void cycle(int i);
    bool isNumber(string s);
    int getNumHands(int bet);
    int getBetValue();
    void dealerPlay();
    void displayWinning();
    Player getCurrentPlayer();
    void reset();
};

#endif /* TABLE_H */

