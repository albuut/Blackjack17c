#include <valarray>

#include "Bet.h"

Bet::Bet(float amount, int betType, int indx) {
    this->betAmount = amount;
    this->betType = betType;
    this->indx = indx;
    this->won = false;
    this->isTie = false;
}

float Bet::getWinnings(bool blackjack) {
    if (blackjack) {
        won = true;
        amountWon = 3 * betAmount / 2 + betAmount;
        return amountWon;
    } else {
        won = true;
        amountWon = betAmount * 2;
        return amountWon;
    }
    return 0;
}
void Bet::tie(){
    this->isTie = true;
}
string Bet::getStringBet(){
    if(isTie){
        return "You tied in Hand " + to_string(indx + 1) + ". Returning your " + toStringType(betType) + " bet of $" + toStringBet(betAmount) + ".";
    }else{
        return "You won $" + toStringBet(betAmount) + " from Hand " + to_string(indx + 1) + " from " + toStringType(betType) + ".";
    }
    return "Error in Tie";    
}
string Bet::toStringBet(float betAmount){
    stringstream s;
    s << fixed << setprecision(2) << betAmount;
    return s.str();
}
string Bet::toStringType(int type){
    switch(type){
        case anteType:return "ante";break;
        case insuranceType:return"insurance";break;
        case splitType:return"split";break;
        case doubleDownType:return"double down";break;
        default:return"Error in bet toStringType";break;
    }
}