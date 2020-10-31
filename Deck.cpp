#include <list>

#include "Deck.h"

Deck::Deck(){
    int k = 0;
    indx = new int[52];
    for(int i = club; i <= spade; i++){
        for(int j = ace; j <= king; j++){
            deck.insert(pair<int,Card>(k,Card(j,i)));
            indx[k] = k;
            k++;
        }
    }
    for(int i = 0; i < 3; i++){
        refreshDeck();
    }
    
}
void Deck::refreshDeck() {
    while(draw.size() != 0){
        draw.pop();
    }
    for(int i = 0; i < 10; i++){
        random_shuffle(&indx[0], &indx[51]);
    }
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 52; i++) {
            draw.push(deck.at(indx[i]));
        }
    }
}
Card Deck::drawCard(){
    Card draw = this->draw.top();
    this->draw.pop();
    return draw;
}

