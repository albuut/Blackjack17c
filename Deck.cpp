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
    refreshDeck();
    
}
void Deck::refreshDeck() {
    while(draw.size() != 0){
        draw.pop();
    }
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 10; j++){
            random_shuffle(&indx[0], &indx[51]);
        }
        for (int j = 0; j < 52; j++) {
            draw.push(deck.at(indx[j]));
        }
    }
}
void Deck::copyDeck(){
    copy = new Card[draw.size()];
    tree.empty();
    dupe = draw;
    recurCopy();    
}
void Deck::printDeck(){
    copyDeck();
    mergeSort(0,draw.size()-1);
    for(int i = 0; i < draw.size(); i++){
        cout << i + 1 << " " << copy[i].toString() << endl;
    }
}
//Recursively copying the draws
void Deck::recurCopy(){
    if(dupe.size() == 0){
        return;
    }
    copy[dupe.size()-1] = dupe.top();
    tree.insert(dupe.top());
    dupe.pop();
    recurCopy();
}

Card Deck::drawCard(){
    copyDeck();
    mergeSort(0,draw.size());
    Card draw = this->draw.top();
    this->draw.pop();
    return draw;
}

void Deck::merge(int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    Card L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = copy[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = copy[m + 1 + j];
    int i = 0;
    // Initial index of second subarray
    int j = 0;
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i].getValue() <= R[j].getValue()) {
            copy[k] = L[i];
            i++;
        }
        else {
            copy[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        copy[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        copy[k] = R[j];
        j++;
        k++;
    }
}

void Deck::mergeSort(int l,int r)Ge{
    if(l>=r){
        return;//returns recursively
    }
    int m = (l+r-1)/2;
    mergeSort(l,m);
    mergeSort(m+1,r);
    merge(l,m,r);
}

void Deck::getWinChance(Hand hand) {
    copyDeck();
    queue<Card> cards = hand.getHand();
    int noBust = 0;
    int twentyOne = 0;        
    int sum_total = 0;
    int sum_hand = 0;
    int sum_ace = 0;
    int two_one_ace = 0;
    int num_ace = 0;
    int* card_remain = tree.getData();
    while(!cards.empty()){
        Card temp = cards.front();
        sum_hand += temp.getGameValue();
        if(temp.getValue() == ace){
            num_ace++;
        }
        cards.pop();
    }
    for(int i = 1; i <= 13; i++){        
        int value = sum_hand;
        if(i == ace){
            value += 11;
            if(value <= 21){
                noBust += card_remain[i-1];                
            }
            if(value == 21){
                twentyOne += card_remain[i-1];
            }
            if(value > 21 && num_ace > 0){
                if(value - 10 <= 21){
                    sum_ace += card_remain[i-1];
                }
                if(value - 10 == 21){
                    two_one_ace += card_remain[i-1];
                }
            }
        }else if(i >= 10){
            value += 10;
            if (value <= 21) {
                noBust += card_remain[i-1];
            }
            if (value == 21) {
                twentyOne += card_remain[i-1];
            }
            if(value > 21 && num_ace > 0){
                if(value - 10 <= 21){
                    sum_ace += card_remain[i-1];
                }
                if(value - 10 == 21){
                    two_one_ace += card_remain[i-1];
                }
            }
        }else{
            value += i;
            if (value <= 21) {
                noBust += card_remain[i-1];
            }
            if (value == 21) {
                twentyOne += card_remain[i-1];
            }
            if(value > 21 && num_ace > 0){
                if(value - 10 <= 21){
                    sum_ace += card_remain[i-1];
                }
                if(value - 10 == 21){
                    two_one_ace += card_remain[i-1];
                }
            }
        }
        sum_total += card_remain[i-1];
    }
    if(sum_hand == 20){
        noBust += card_remain[0];
        twentyOne += card_remain[0];
        sum_ace += card_remain[0];
    }
    float safe = noBust/(float)sum_total * 100;
    float bust = (1 - noBust/(float)sum_total)* 100;
    float max = twentyOne/(float)sum_total * 100;
    
    
    cout << "% Next Hit Safe: " << fixed << setprecision(2) << safe << "%" << endl;
    cout << "% Next Hit Bust: " << fixed << setprecision(2) << bust << "%" << endl;
    cout << "% Next Hit 21: " << fixed << setprecision(2) << max << "%" << endl << endl;
    
    if(num_ace > 0) {
        cout << "If an ace is soft" << endl;
        cout << "% Next Hit Safe: " << fixed << setprecision(2) << sum_ace/(float)sum_total * 100 << "%" << endl;
        cout << "% Next Hit Bust: " << fixed << setprecision(2) << (1 - sum_ace/(float)sum_total) * 100<< "%" << endl;
        cout << "% Next Hit 21: " << fixed << setprecision(2) << two_one_ace/(float)sum_total * 100 << "%" << endl << endl;
    }

}

Card Deck::cheat(){
    string answer;
    cout << "Cheat? (Y/N): ";
    if(choice()){        
        printDeck();
        cout << "Pick a card (1-" << draw.size() << "): ";
        while(true){
            getline(cin, answer);
            if(isNumber(answer)){
                if(stoi(answer) >= 1 && stoi(answer) <= draw.size()){
                    break;
                }else{
                    cout << "Invalid Option choose a card in list from (1-" << draw.size() <<"): ";
                }
            }else{
                cout << "Invalid Option choose a card in list from (1-" << draw.size() <<"): ";
            }
        }
        int index = stoi(answer);
        stack<Card> trash;        
        return copy[index - 1];
    }
    return Card(-1,0);
}
bool Deck::choice() {
    string answer;
    while (true) {
        getline(cin, answer);
        if (answer == "Y" || answer == "y") {
            return true;
        } else if (answer == "N" || answer == "n") {
            break;
        } else {
            cout << "Invalid Option, please use Y or N: ";
        }
    }
    return false;
}
bool Deck::isNumber(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]) == false) {
            return false;
        }
    }
    if (s.length() == 0) {
        return false;
    }
    return true;
}