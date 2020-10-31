#include "Card.h"

Card::Card(const int value, const int suit) {
    this->value = value;
    this->suit = suit;
}
string Card::toString(){
    if(suit >= club && suit <= spade){
        if(value >= ace && suit <= king){
            return faceToString() + " of " + suitToString();
        }else{return "";}
    }else{return "";}
}
string Card::suitToString(){
    switch(suit){
        case club: return "Clubs";break;
        case diamond: return "Diamonds"; break;
        case heart: return "Hearts";break;
        case spade: return "Spades";break;
        default: return "Magic in suitToString()";break;
    }
}
string Card::faceToString(){
    switch(value){
        case ace: return "Ace"; break;
        case jack: return "Jack"; break;
        case queen: return "Queen"; break;
        case king: return "King"; break;
        default: return to_string(value); break;
    }
}