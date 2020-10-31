#include "Login.h"

Login::Login() {
    online = false;
}
bool Login::logon() {
    getPlayers();
    loginHeader();
    cout << "Login?(Y/N): ";
    if(loginChoice()){
        clear();
        loginHeader();
        string username;
        string password;
        while(true){
            cout << "Username: ";
            getline(cin,username);
            cout << "Password: ";
            getline(cin,password);
            if(checkLogin(username,password)){
                clear();
                loginHeader();
                return true;
            }else{
                cout << "Note: Usernames are case sensitive." << endl;
                cout << "Incorrect Login Information, try again?(Y/N): ";
                if(!loginChoice()){
                    break;
                }else{
                    clear();
                    loginHeader();
                }
            }
        }
    }
    if(!online){
        clear();
        loginHeader();
        string username;
        string password;
        cout << "Create account?(Y/N): ";
        if(loginChoice()){
            cout << "Enter a username: ";
            while(true){
                getline(cin,username);
                if(validateUsername(username)){
                    break;
                }else{
                    cout << "Username is used, please try another one: ";
                }
            }
            cout << "Enter a Password: ";
            getline(cin,password);
            transform(username.begin(), username.end(), username.begin(), ::tolower);
            createUser(username,password);
            clear();
            loginHeader();
            return true;
        }
    }
    return false;   
}
bool Login::checkLogin(string username, string password) {
    map<string,Player>::iterator itr;
    string temp = username;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    itr = playerList.find(temp);
    if(itr == playerList.end()){
        return false;
    }else{
        if(itr->second.getPassword().compare(password) == 0) {
            player = itr->second;
            return true;
        }
    }
    return false;
}
void Login::createUser(string username, string password){
    Player newPlayer = Player(username,password,25000,0,0);
    player = newPlayer;
    playerList.insert(pair<string,Player>(username,newPlayer));
    updatePlayers();
}
bool Login::validateUsername(string username) {
    map<string,Player>::iterator itr;
    string temp = username;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    itr = playerList.find(temp);
    if(!(itr == playerList.end())){
        return false;
    }
    return true;
}
void Login::getPlayers(){
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
    }
    fin.close();
}
Player Login::getPlayer(){
    return this->player;
}
void Login::updatePlayer(const Player &current) {
    map<string, Player>::iterator itr;
    for (itr = playerList.begin(); itr != playerList.end(); ++itr) {
        if (itr->first == current.getUsername()) {
            itr->second = current;
            break;
        }
    }
     
}
void Login::updatePlayers() {
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
    }
}
bool Login::getOnline(){
    return online;
}
void Login::loginHeader() {
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
bool Login::loginChoice() {
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
void Login::clear(){
    for(int i = 0; i < 25; i ++){
        cout << endl;
    }
}
bool Login::caseless_match(string s1, string s2){
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
   if(s1.compare(s2) == 0)
      return true; 
   return false; 
}