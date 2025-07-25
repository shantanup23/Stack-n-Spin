#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "dicerollduel.hpp"
#include <string>

dicerollduel :: dicerollduel(const std::string &name,double balance)
    : playerName(name), initialBalance(balance) ,gen(std::random_device{}()) {}

std::string dicerollduel::getName() const {
    return "Dice Roll Duel";
}

int dicerollduel::rolldice() {
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}

void dicerollduel :: play(double& playerBalance){
    std::cout << "\n--- Welcome to Dice Roll Duel, " << playerName << "! ---\n";
    std::cout << "Your current balance: $" << playerBalance << std::endl;
    double bet;
    std::cout << "Enter your bet: $";
    std::cin >> bet;

    if (bet > playerBalance || bet <= 0) {
        std::cout << "Dealer: Nice try! Place a valid bet.\n";
        return;
    }
    int playerDie1 = rolldice();
    int playerDie2 = rolldice();
    int dealerDie1 = rolldice();
    int dealerDie2 = rolldice();

    int playerTotal = playerDie1 + playerDie2;
    int dealerTotal = dealerDie1 + dealerDie2;

    std::cout << "You rolled: " << playerDie1 << " and " << playerDie2 << " (Total: " << playerTotal << ")\n";
    std::cout << "Dealer rolled: " << dealerDie1 << " and " << dealerDie2 << " (Total: " << dealerTotal << ")\n";

    if (playerTotal > dealerTotal) {
        std::cout << "Dealer: You win! Beginner’s luck or skill?\n";
        playerBalance += bet;
    } else if (playerTotal < dealerTotal) {
        std::cout << "Dealer: I win! Lady Luck is on my side today.\n";
        playerBalance -= bet;
    } else {
        std::cout << "Dealer: It's a tie! Guess we both have lucky hands.\n";
    }
    std::cout << "New balance: $" << playerBalance << std::endl;
}