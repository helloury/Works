#include "estrutura.h"
#ifndef Game_h
#define Game_h

using namespace std;
class card {
public:
    int points;
    int suit;
};

class Player {
public:
    int id;
    DoublycircularList<card*> hand;
};

class Game {
public:
    int numPlayers;
    bool clockwise = true; //sentido-horario
    Stack<card*> deck, discardPile, sequence;
    DoublycircularList<Player*> players;

    //retorna quantos pontos a carta vale
    static void Points(char suit, card* card) {
        switch (suit) {
            case 'A': card->points = 1; break;
            case 'B': card->points = 2; break;
            case 'c': card->points = 3; break;
            case 'D': card->points = 4; break;
            case 'E': card->points = 5; break;
            case 'F': card->points = 6; break;
            case 'G': card->points = 7; break;
            case 'H': card->points = 8; break;
            case 'I': card->points = 9; break;
            case 'J': card->points = 10; break;
            case 'K': card->points = 11; break;
            case 'L': card->points = 12; break;
            case 'M': card->points = 13; break;
            default: card->points = 0; break;
        }
    }

//quando o Deck estiver vazio, pega da discardPile
void replenishDeck() {
        if (discardPile.isEmpty()) return;

        card* tempcard = discardPile.TOP();
        discardPile.pop();

        while (!discardPile.isEmpty()) {
            deck.push(discardPile.TOP());
            discardPile.pop();
        }

        discardPile.push(tempcard);
    } 

 /*Redistribui as cartas, removendo da mao dos jogadores
  p/ possivel nova rodada*/
 void shuffleDeck() {
        for (int i = 1; i <= numPlayers; i++) {
            players.getItValue()->hand.Delete();
        }

        while (!deck.isEmpty()) deck.pop(); //pilha do baralho
        while (!discardPile.isEmpty()) discardPile.pop();//pilha de descarte

        while (!sequence.isEmpty()) {
            discardPile.push(sequence.TOP());
            sequence.pop();
        }

        while (!discardPile.isEmpty()) {
            deck.push(discardPile.TOP());
            sequence.push(discardPile.TOP());
            discardPile.pop();
        }

        players.moveToStart();
        for (int i = 1; i <= numPlayers; i++) {
            for (int j = 0; j < 5; j++) {
                players.getItValue()->hand.insertAfter(deck.TOP());
                deck.pop();
            }
            players.Itmm();
        }
    }
    /*Ler as cartas e empilhando no deck e 
    sequence(pilha que preserva a ordem original)*/
    void Getcards() {
        for (int i = 0; i < 104; i++) {
            char suitchar;
            card* newcard = new card;
            cin >> suitchar >> newcard->suit;
            Points(suitchar, newcard);
            deck.push(newcard);
            sequence.push(newcard);
        }
    }

    //distribuiçao de cartas
    void dealcards() 
    {
            Getcards();
            for (int i = 1; i <= numPlayers; i++) {
            players.insertAfter(new Player);
            players.getItValue()->id = i;
            }
            players.moveToStart();
            for (int i = 1; i <= numPlayers; i++) {
                for (int j = 0; j < 5; j++) {
                    players.getItValue()->hand.insertAfter(deck.TOP());
                    deck.pop();
                    }
            players.Itmm();
            }
    }

    //começa a rodada com as cartas já distribuidas
    void playRound() {
        players.moveToStart();
        int i = 0;

        if (discardPile.isEmpty()) {
            discardPile.push(players.getItValue()->hand.getItValue());
            players.getItValue()->hand.Delete();
            i++;
        }

        while(i < numPlayers){
            discardPile.push(players.getItValue()->hand.getItValue());
            players.getItValue()->hand.Delete();
            players.Itmm();
            i++;
        }

        bool gameEnd = false;
        players.moveToStart();
        for (int i = 0; i < numPlayers; i++) {
            if (players.getItValue()->hand.getSize() == 0) gameEnd = true;
            players.Itmm();
        }

        if (gameEnd) {
            players.moveToStart();
            int maxScore = 0, winner = 0;

            for (int i = 0; i < numPlayers; i++) {
                int totalPoints = 0;
                players.getItValue()->hand.moveToStart();
                int handSize = players.getItValue()->hand.getSize();

                for (int j = 0; j < handSize; j++) {
                    totalPoints += players.getItValue()->hand.getItValue()->points;
                    players.getItValue()->hand.Itmm();
                }

                if (totalPoints > maxScore) {
                    maxScore = totalPoints;
                    winner = players.getItValue()->id;
                }
                players.Itmm();
            }

            players.moveToStart();
            for (int i = 0; i < numPlayers; i++) {
                if (players.getItValue()->id == winner) {
                    players.Delete();
                    numPlayers--;
                    break;
                }
                players.Itmm();
            }
            shuffleDeck();
        }
    }

    int getWinner() {
        return players.getSize() == 1 ? players.getItValue()->id : 0;
    }

    void startGame() {
        dealcards();

        while (players.getSize() > 1) {
            playRound();
        }
    }
};
#endif