#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

struct Card {
    string color; // Red, Green, Blue, Yellow
    string value; // 0-9, Skip, Reverse, Draw Two
};

class UNOGame {
private:
    vector<Card> deck;
    vector<vector<Card>> players;
    vector<Card> discard;
    int currentPlayer;
    bool clockwise;
    int numPlayers;

    // Utility: create deck
    void createDeck() {
        string colors[] = {"Red", "Green", "Blue", "Yellow"};
        // Numbers
        for (string c : colors) {
            deck.push_back({c, "0"}); // one zero
            for (int i = 1; i <= 9; i++) {
                deck.push_back({c, to_string(i)});
                deck.push_back({c, to_string(i)});
            }
            // Action cards
            for (int k = 0; k < 2; k++) {
                deck.push_back({c, "Skip"});
                deck.push_back({c, "Reverse"});
                deck.push_back({c, "Draw Two"});
            }
        }
    }

    // Utility: check playable
    bool isPlayable(Card card, Card top) {
        return (card.color == top.color || card.value == top.value);
    }

public:
    UNOGame(int n) {
        numPlayers = n;
        players.resize(n);
        clockwise = true;
        currentPlayer = 0;
    }

    void initialize() {
        createDeck();
        // Shuffle with fixed seed 1234
        std::mt19937 rng(1234);
        shuffle(deck.begin(), deck.end(), rng);

        // Deal 7 cards
        for (int i = 0; i < numPlayers; i++) {
            for (int j = 0; j < 7; j++) {
                players[i].push_back(deck.back());
                deck.pop_back();
            }
        }

        // Start discard
        discard.push_back(deck.back());
        deck.pop_back();
    }

    string getState() {
        string state = "Player " + to_string(currentPlayer) + "'s turn, Direction: ";
        state += (clockwise ? "Clockwise" : "Counter-clockwise");
        state += ", Top: " + discard.back().color + " " + discard.back().value;
        state += ", Players cards: ";
        for (int i = 0; i < numPlayers; i++) {
            state += "P" + to_string(i) + ":" + to_string(players[i].size());
            if (i < numPlayers - 1) state += ", ";
        }
        return state;
    }

    bool isGameOver() {
        for (int i = 0; i < numPlayers; i++) {
            if (players[i].empty()) return true;
        }
        return false;
    }

    void playTurn() {
        Card top = discard.back();
        bool played = false;

        // Try to play first matching card
        for (int i = 0; i < players[currentPlayer].size(); i++) {
            if (isPlayable(players[currentPlayer][i], top)) {
                Card chosen = players[currentPlayer][i];
                discard.push_back(chosen);
                players[currentPlayer].erase(players[currentPlayer].begin() + i);
                played = true;

                // Action effects
                if (chosen.value == "Skip") {
                    advanceTurn();
                } else if (chosen.value == "Reverse") {
                    clockwise = !clockwise;
                } else if (chosen.value == "Draw Two") {
                    int next = getNextPlayer();
                    for (int k = 0; k < 2 && !deck.empty(); k++) {
                        players[next].push_back(deck.back());
                        deck.pop_back();
                    }
                    advanceTurn();
                }
                break;
            }
        }

        // If not played → draw
        if (!played) {
            if (!deck.empty()) {
                Card newCard = deck.back();
                deck.pop_back();
                if (isPlayable(newCard, top)) {
                    discard.push_back(newCard);
                } else {
                    players[currentPlayer].push_back(newCard);
                }
            }
        }

        // Advance to next player
        advanceTurn();
    }

private:
    int getNextPlayer() {
        if (clockwise) return (currentPlayer + 1) % numPlayers;
        else return (currentPlayer - 1 + numPlayers) % numPlayers;
    }

    void advanceTurn() {
        currentPlayer = getNextPlayer();
    }
};
