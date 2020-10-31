#include "Player.h"
Player::Player(string username, string password, float money, int handsPlayed, int handsWon){
    this->username = username;
    this->password = password;
    this->money = money;
    this->handsPlayed = handsPlayed;
    this->handsWon = handsWon;
}
Player::Player(const Player &player){
    this->username = player.getUsername();
    this->password = player.getPassword();
    this->money = player.getMoney();
    this->handsPlayed = player.getHandsPlayed();
    this->handsWon = player.getHandsWon();            
}
void Player::modBal(float money){
    this->money += money;
}
//Using Map
void Player::getPlayerList(){
    fstream fin;
    fin.open(this->fileNamePlayer, ios::in);
    if (fin) {
        string *data = new string[5];
        string line;
        while (getline(fin, line)) {
            stringstream s(line);
            for (int i = 0; i < 5; i++) {
                getline(s, data[i], ',');
            }
            Player temp = Player(data[0], data[1], stol(data[2]), stoi(data[3]), stoi(data[4]));
            playerList.insert(pair<string,Player>(data[0],temp));
        }
    }else{cout << "Error in getPlayerList";}
    fin.close();
}
//Using Forward Iterator
//could of used .find() I guess.
void Player::update(const Player &current){
    map<string,Player>::iterator itr;
    for(itr = playerList.begin(); itr != playerList.end(); ++itr){
        if(itr->first == current.getUsername()){
            itr->second = current;
            break;
        }
    }
}
//Using Input Iterator
void Player::updateList() {
    fstream fout;
    fout.open(this->fileNamePlayer, ios::out | ios::trunc);
    if (fout) {
        for (auto itr = playerList.begin(); itr != playerList.end(); ++itr) {
            fout << itr->second.getUsername() << ','
                    << itr->second.getPassword() << ','
                    << itr->second.getMoney() << ','
                    << itr->second.getHandsPlayed() << ','
                    << itr->second.getHandsWon() << ',' << endl;
        }
        fout.close();
    }else{cout << "Error in updatePlayerList";}
}
