#ifndef CARD_H
#define CARD_H
#include <string>
#include <map>
#include <iterator>
enum{club, diamond, heart, spade};
enum{ace = 1,jack = 11, queen, king};
using namespace std;
class Card {
private:
private:
    int value;
    int suit;
public:
    Card(){
        value = 0;
        suit = 0;
    }
    Card(const int value, const int suit);
    Card getCard()const{return *this;}
    int getGameValue()const{
        if(value == ace){return 11;}
        else if(value > 10){return 10;}
        else{return value;}};
    int getValue()const{
        return value;
    }
    int getSuit()const{
        return suit;
    }
    string toString();
    string suitToString();
    string faceToString();
};
#endif /* CARD_H */

