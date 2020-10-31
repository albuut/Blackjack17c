/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Deck.h
 * Author: Albuu
 *
 * Created on September 29, 2020, 12:59 PM
 */

#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <time.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <queue>
#include <bits/stdc++.h>
class Deck {
protected:
    int numDecks = 3;
private:
    map<int, Card> deck;
    int* indx;
    stack <Card> draw;
public:
    Deck();
    void refreshDeck();
    int getNumCards(){return draw.size();}
    Card drawCard();
};

#endif /* DECK_H */

