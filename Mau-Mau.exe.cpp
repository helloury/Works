#include "estrutura.h"
#include "Game.h"

#include <iostream>

using namespace std;

int main() {
    int Match;
    cin >> Match;
    for (int i = 0; i < Match; i++) 
    {
       int numPlayers;
        cin >> numPlayers;
        //mensagem de erro pra caso for menor que < 2 e >10
        if (numPlayers < 2) {
            cout << "Não dá pra jogar com as paredes, arrume mais amigos :C" << endl;
            continue; 
        }else if(numPlayers > 10){
            cout << "Não tem baralho pra tanta gente, diminua um pouco ai :p"<< endl;
            continue;
        }
        Game game;
        game.numPlayers = numPlayers;
        game.startGame();
        cout << "Vencedor da partida " << i + 1 << ": jogador " << game.getWinner() << endl;
    }
    return 0;
}
