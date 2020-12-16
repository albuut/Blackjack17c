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
#include "Hand.h"
#include "BST.h"
#include <time.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <queue>
#include <bits/stdc++.h>
#include <iomanip>
#include <string>
class Deck {
protected:
    int numDecks = 3;
private:
    map<int, Card> deck;
    int* indx;
    Card* copy;
    stack <Card> draw;
    stack <Card> dupe;
    BST tree;
public:
    Deck();
    void refreshDeck();
    int getNumCards(){return draw.size();}
    Card drawCard();
    
    void printDeck();
    void copyDeck();
    void recurCopy();
    void merge(int l, int m, int r);
    void mergeSort(int l,int r);
    int getDeckSize(){
        return draw.size();
    }
    void fillTree();
    void getCardList(){
        copyDeck();
        for(int i = 0; i < draw.size(); i++){
            cout << i + 1 << " " << copy[i].toString() << endl;
        }
    }
    void getWinChance(Hand hand);
    bool choice();
    bool isNumber(string s);
    Card cheat();
};

#endif /* DECK_H */

