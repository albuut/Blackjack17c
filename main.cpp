#include <cstdlib>
#include "Login.h"
#include "Table.h"
#include "Player.h"
#include <iterator> 
#include <map>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(NULL));

    Login login;
    Player player = Player("Guest","Password",25000,0,0);
    if(login.logon()){
        player = login.getPlayer();
    }    
    Table table = Table(player);
    while(true){
        cout << "Would you like to play a game?(Y/N): ";
        if(table.choice()){
            table.play();
            player.update(table.getCurrentPlayer());
        }else{
            cout << "Exiting Game!";
            break;
        }
    }
    return 0;
}

