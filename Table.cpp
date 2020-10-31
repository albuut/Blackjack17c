#include <valarray>

#include "Table.h"

Table::Table(const Player& player) {
    this->player = player;
}

void Table::play() {
    cls();
    header();
    if (deck.getNumCards() < 30) {
        deck.refreshDeck();
    }
    bet = getBetValue();
    numHands = getNumHands(bet);
    for (int i = 0; i < numHands; i++) {
        dealCards(bet);
        handOrder.insert(i);
    }
    dealerHand.push_back(deck.drawCard());
    dealerHand.push_back(deck.drawCard());
    printHand();       
    for(auto itr = handOrder.begin(); itr != handOrder.end(); ++itr){        
        evenMoney(*itr);
        insurance(*itr);
        split(*itr);
        if (!doubleDown(*itr)) {
            while (hit(*itr)) {
                playerHand[*itr].add(deck.drawCard());
                printHand();
            }
        }
    }
    dealerPlay();
    player.handPlayed(playerHand.size());
    win();
    displayWinning();
    reset();

}

void Table::dealCards(float amount) {
    if (this->player.getMoney() > amount) {
        Hand hand;
        hand.add(deck.drawCard());
        hand.add(deck.drawCard());
        playerHand.insert(pair<int, Hand>(playerHand.size(), hand));
        player.modBal(-amount);
        playerBet.push(Bet(amount, anteType, playerHand.size() - 1));
    }
}

bool Table::hit(int i) {
    printHand();
    if (playerHand[i].getTotal() < 21) {
        cout << "Hit Hand " << i + 1 << "?(Y/N): ";
        if (choice()) {
            return true;
        }
        return false;
    }
    return false;
}

bool Table::doubleDown(int i) {
    printHand();
    if (playerHand[i].handSize() == 2) {
        if (player.getMoney() > bet) {
            cout << "Double Down Hand " << i + 1 << "?(Y/N): ";
            if (choice()) {
                player.modBal(-bet);
                playerBet.push(Bet(bet, doubleDownType, i));
                playerHand[i].add(deck.drawCard());
                printHand();
                return true;
            }
        }
    }
    return false;
}

void Table::insurance(int i) {
    if (player.getMoney() > bet) {
        if (playerHand[0].isInsurance(dealerHand.front())) {
            cout << "Insurance?(Y/N): ";
            if (choice()) {
                player.modBal(-bet);
                playerBet.push(Bet(bet, insuranceType, i));
                printHand();
            }
        }
    }
}

void Table::evenMoney(int i) {
    if (player.getMoney() > bet) {
        if (playerHand[0].isEvenMoney(dealerHand.front())) {
            cout << "Even Money?(Y/N): ";
            if (choice()) {
                player.modBal(-bet);
                playerBet.push(Bet(bet / 2, evenMoneyType, i));
                printHand();
            }
        }
    }
}

void Table::split(int i) {
    if (player.getMoney() > bet) {
        if (playerHand[i].isSplit()) {
            cout << "Split?(Y/N): ";
            if (choice()) {
                player.modBal(-bet);
                Hand newHand = playerHand[i].splitHand(deck.drawCard());
                newHand.add(deck.drawCard());
                playerHand.insert(pair<int, Hand>(playerHand.size(), newHand));
                playerBet.push(Bet(bet, splitType, playerHand.size() - 1));
                printHand();
            }
        }
    }
}

bool Table::choice() {
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

void Table::win() {
    int totalBets = playerBet.size();
    for (int i = 0; i < totalBets; i++) {
        if (!playerHand[playerBet.front().getIndx()].bust()) {
            if (playerBet.front().getBetType() == insuranceType || playerBet.front().getBetType() == evenMoneyType) {
                if (dealerHand.size() == 2 && dealerValue() == 21) {
                    player.modBal(playerBet.front().getWinnings(false));
                }
            } else if (playerBet.front().getBetType() == splitType || playerBet.front().getBetType() == anteType || playerBet.front().getBetType() == doubleDownType) {
                if (playerHand[playerBet.front().getIndx()].isBlackjack() && dealerValue() == 21 && dealerHand.size() == 2) {
                    player.modBal(playerBet.front().getBetAmount());
                    playerBet.front().tie();
                } else if (playerHand[playerBet.front().getIndx()].isBlackjack() && dealerValue() == 21 && dealerHand.size() > 2) {
                    player.modBal(playerBet.front().getWinnings(true));
                } else if (playerHand[playerBet.front().getIndx()].getTotal() > dealerValue()) {
                    player.modBal(playerBet.front().getWinnings(false));
                } else if (dealerValue() > 21) {
                    player.modBal(playerBet.front().getWinnings(false));
                } else if (playerHand[playerBet.front().getIndx()].getTotal() == dealerValue()) {
                    player.modBal(playerBet.front().getBetAmount());
                    playerBet.front().tie();
                }
            }
        }
        playerBet.push(playerBet.front());
        playerBet.pop();
    }
    printHand();
}

Player Table::getPlayer() {
    return this->player;
}

void Table::header() {
    string title = "|Blackjack Table|";
    string user = "|User:";
    string balance = "|Balance:$";
    string end = "|";
    stringstream s;
    s << fixed << setprecision(2) << player.getMoney();
    string balVal = s.str();
    cout << left << setw(72) << title << user << player.getUsername() << balance << balVal << end << endl;
    string header = title + user + player.getUsername() + balance + balVal + end;
    int length = 72 - title.length() + header.length();
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << endl;
}

void Table::cls() {
    for (int i = 0; i < 25; i++) {
        cout << endl;
    }
}

void Table::printHand() {
    cls();
    header();
    int numRow = 0;
    if (playerHand.size() <= 4) {
        numRow = 1;
    } else if (playerHand.size() > 4) {
        numRow = playerHand.size() / 4;
        if (playerHand.size() % 4 > 0) {
            numRow++;
        }
    }

    queue<Card> *hand = new queue<Card>[playerHand.size()];
    int handIndx = 0;
    for (auto itr = playerHand.begin(); itr != playerHand.end(); ++itr) {
        hand[handIndx] = itr->second.getHand();
        handIndx++;
    }
    queue<Card> dealerHand;
    for(auto itr = this->dealerHand.begin(); itr != this->dealerHand.end(); ++itr){
        Card temp = *itr;
        dealerHand.push(temp);
    }
    int dealerHandSize = dealerHand.size();
    for (int i = 0; i < numRow; i++) {
        for (int j = i * 4; j < 4 * (i + 1); j++) {
            if (j < playerHand.size()) {
                cout << "Hand " << j + 1 << left << setw(15) << ":";
            } else {
                cout << left << setw(21) << "";
            }
        }
        if (i == 0) {
            cout << left << setw(15) << "Dealer's Hand: ";
        }
        cout << endl;
        for (int j = i * 4; j < 4 * (i + 1); j++) {
            if (j < playerHand.size()) {
                cout << left << setw(21) << "-------";
            } else {
                cout << left << setw(21) << "";
            }
        }
        if (i == 0) {
            cout << left << setw(21) << "--------------";
        }
        cout << endl;
        int handSize = dealerHand.size();
        for (int j = i * 4; j < 4 * (i + 1); j++) {
            if (j < playerHand.size()) {
                if (handSize < playerHand[j].handSize()) {
                    handSize = playerHand[j].handSize();
                }
            }
        }
        for (int j = 0; j < handSize; j++) {
            for (int k = 4 * i; k < 4 * (i + 1); k++) {
                if (k < playerHand.size() && j < playerHand[k].handSize()) {
                    cout << left << setw(21) << hand[k].front().toString();
                    hand[k].pop();
                } else {
                    cout << left << setw(21) << "";
                }
            }

            if (i == 0) {
                if (j < dealerHandSize) {
                    if (j == 0) {
                        cout << left << setw(21) << dealerHand.front().toString();
                        dealerHand.pop();
                    } else if (!dealerTurn) {
                        cout << left << setw(21) << "?????";
                    } else {
                        cout << left << setw(21) << dealerHand.front().toString();
                        dealerHand.pop();
                    }
                } else {
                    cout << left << setw(21) << "";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

}

bool Table::isNumber(string s) {
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

int Table::getNumHands(int bet) {
    string numHands;
    if (player.getMoney() > bet * 2) {
        if (player.getMoney() > bet * 5) {
            cout << "How many hands would you like to play?(1-5): ";
        } else {
            cout << "How many hands would you like to play?(1-" << player.getMoney() / (bet) << "): ";
        }
        while (true) {
            getline(cin, numHands);
            if (isNumber(numHands)) {
                if (stoi(numHands) >= 1 && stoi(numHands) <= 5) {
                    return stoi(numHands);
                } else {
                    if (player.getMoney() > bet * 5) {
                        cout << "Invalid option, please choose a value between (1-5): ";
                    } else {
                        cout << "Invalid option, please choose a value between (1-" << player.getMoney() / (bet) << "): ";
                    }
                }
            } else {
                if (player.getMoney() > bet * 5) {
                    cout << "Invalid Input, please choose a value between (1-5): ";
                } else {
                    cout << "Invalid option, please choose a value between (1-" << player.getMoney() / (bet) << "): ";
                }
            }
        }
    }
    return -1;
}

int Table::getBetValue() {
    string bet;
    string money = to_string(player.getMoney());
    if (player.getMoney() > 100) {
        if (player.getMoney() < 1000) {
            cout << "How much would you like to bet?($100-$" << player.getMoney() << "): $";
        } else {
            cout << "How much would you like to bet?($100-$1000): $";
        }
        while (true) {
            getline(cin, bet);
            if (isNumber(bet)) {
                if (stoi(bet) >= 100 && stoi(bet) <= 1000) {
                    return stoi(bet);
                } else {
                    if (player.getMoney() < 1000) {
                        cout << "Invalid Bet, please choose a value ($100-$" << player.getMoney() << "): $";
                    }
                    cout << "Invalid Bet, please choose a value ($100-$1000): $";

                }
            } else {
                if (player.getMoney() < 1000) {
                    cout << "Invalid input, please choose a value from ($100-$" << player.getMoney() << "): $";
                } else {
                    cout << "Invalid input, please choose a value from ($100-$1000): $";
                }
            }
        }
    } else {
        cout << "Please recharge your account at the front desk, exiting game!";
        return -1;
    }
}
int Table::dealerValue() {
    int sum = 0;
    int ace = 0;
    for (auto itr = dealerHand.begin(); itr != dealerHand.end(); ++itr) {
        Card temp = *itr;
        sum += temp.getGameValue();
        if(temp.getValue() == ace){
            ace++;
        }
    }
    if (sum > 21) {
        if (ace > 0) {
            sum -= 10;
        }
    }
    return sum;
}
void Table::dealerPlay() {
    dealerTurn = true;
    int bust = 0;
    for (int i = 0; i < playerHand.size(); i++) {
        if (playerHand[i].bust()) {
            bust++;
        }
    }
    while (dealerValue() < 17 && bust != playerHand.size()) {
        dealerHand.push_back(deck.drawCard());
    }
    printHand();
}

void Table::displayWinning() {
    bool won = false;
    Bet *betWon = new Bet[playerBet.size()];
    int countWon = 0;
    int totalBet = playerBet.size();
    for (int i = 0; i < totalBet; i++) {
        if (playerBet.front().getWon() || playerBet.front().getTie()) {
            betWon[countWon] = playerBet.front();
            countWon++;
            if (playerBet.front().getWon()) {
                if (playerBet.front().getBetType() == anteType || playerBet.front().getBetType() == splitType)
                    player.handWon();
            }
        }
        playerBet.pop();
    }
    if (countWon > 0) {
        pair<int, int> indx[countWon];
        for (int j = 0; j < countWon; j++) {
            indx[j] = make_pair(betWon[j].getIndx(), j);
        }

        sort(&indx[0], &indx[countWon]);
        for (int j = 0; j < countWon; j++) {
            cout << betWon[indx[j].second].getStringBet() << endl;
        }
    }else {
        if (playerHand.size() == 1) {
            cout << "Your hand lost!";
        } else {
            cout << "Your hands lost!";
        }
        cout << endl;
    }
}

Player Table::getCurrentPlayer() {
    return player;
}

void Table::reset() {
    playerHand.clear();
    dealerHand.clear();
    handOrder.clear();
    dealerTurn = false;
    bet = 0;
    numHands = 0;
}