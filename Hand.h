/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hand.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 2:20 PM
 */

#ifndef HAND_H
#define HAND_H
#include "Card.h"
#include <list>
#include <iostream>
#include <iterator>
#include <bits/stdc++.h>
using namespace std;
class Hand {
private:
    //switch to list
    list<Card> hand;
public:
    Hand();
    Hand(const Card &split);
    void add(const Card &card);
    void removeCard();
    bool bust();
    bool isInsurance(const Card &dealer);
    bool isEvenMoney(const Card &dealer);
    bool isBlackjack();
    Card splitHand(const Card& newCard);
    bool isSplit();
    int getTotal();
    void clear();
    int handSize()const{return hand.size();}
    queue<Card> getHand();

};

#endif /* HAND_H */

