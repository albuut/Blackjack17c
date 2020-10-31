#include "Hand.h"
Hand::Hand(){
    
}
Hand::Hand(const Card& split){
    hand.push_back(split);
}
void Hand::add(const Card &card){
    hand.push_back(card);
}
bool Hand::bust(){
    if(getTotal() > 21){
        return true;
    }
    return false;
}
bool Hand::isInsurance(const Card& dealer){
    if(dealer.getValue() == ace && !isBlackjack()){
        return true;
    }
    return false;
}

bool Hand::isEvenMoney(const Card& dealer) {
    if (dealer.getValue() == ace && isBlackjack()) {
        return true;
    }
    return false;
}
bool Hand::isBlackjack(){
    if(hand.size() == 2){
        if(getTotal() == 21){
            return true;
        }
    }
    return false;
}
Card Hand::splitHand(const Card& newCard){
    Card temp = hand.back();
    hand.pop_back();
    hand.push_back(newCard);
    return temp;
}
bool Hand::isSplit(){
    if(hand.size() == 2){
        if(hand.front().getValue() == hand.back().getValue()){
            return true;
        }
    }
    return false;
}
int Hand::getTotal(){
    int sum = 0;
    int ace = 0;
    for(auto itr = hand.begin(); itr != hand.end(); ++itr){
        Card temp = *itr;
        sum += temp.getGameValue();
        if(temp.getGameValue() == 11){
            ace++;
        }
    }
    if(sum > 21){
        if(ace > 0){
            sum -= 10;
        }
    }
    return sum;
}
void Hand::clear(){
    hand.clear();
}
queue<Card> Hand::getHand(){
    queue<Card> hand;
    for(auto itr = this->hand.begin(); itr != this->hand.end(); ++itr){
        Card temp = *itr;
        hand.push(temp);
    }
    return hand;
}
