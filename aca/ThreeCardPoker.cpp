
#include "ThreeCardPoker.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

ThreeCardPoker::ThreeCardPoker(const std::string& name, double& balance)
    : playerName(name), playerBalance(balance) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::string ThreeCardPoker::getName() const {
    return "Three Card Poker";
}

void ThreeCardPoker::play(double& dummy) {
    (void)dummy;

    std::cout << "\n== Welcome to Three Card Poker, ==" << playerName << "!\n";
    std::cout << "Your current balance: $" << playerBalance << "\n";

    double betAmount;
    std::cout << "Enter your bet amount: $";
    std::cin >> betAmount;

    if (betAmount <= 0 || betAmount > playerBalance) {
        std::cout << "❌ Invalid bet amount.\n";
        return;
    }

    std::vector<int> cards(3);
    for (int& card : cards) {
        card = (std::rand() % 13) + 1; // 1 to 13
    }

    std::sort(cards.begin(), cards.end());

    std::cout << " Your cards are : ";
    for (int c : cards) std::cout << c << " ";
    std::cout << "\n";

    int payoutMultiplier = 0;

    // Check for Three of a Kind
    if (cards[0] == cards[1] && cards[1] == cards[2]) {
        std::cout << "Superbbb !  Three of a Kind!\n";
        payoutMultiplier = 10;
    }
    // Check for Straight
    else if (cards[2] == cards[1] + 1 && cards[1] == cards[0] + 1) {
        std::cout << "Awesommeee !  Straight!\n";
        payoutMultiplier = 6;
    }
    // Check for Pair + near-sequence
    else if (
        (cards[0] == cards[1] && std::abs(cards[0] - cards[2]) == 1) ||
        (cards[1] == cards[2] && std::abs(cards[2] - cards[0]) == 1)
    ) {
        std::cout << "You got ( Pair + Near Sequence!)\n";
        payoutMultiplier = 4;
    }
    // Check for Pair
    else if (cards[0] == cards[1] || cards[1] == cards[2] || cards[0] == cards[2]) {
        std::cout << "Hahhh Pair!\n";
        payoutMultiplier = 2;
    }
    else {
        std::cout << "Ooops High Card. No win.\n";
        payoutMultiplier = 0;
    }

    if (payoutMultiplier > 0) {
        double winnings = betAmount * payoutMultiplier;
        std::cout << "Congrats ,  You win $" << winnings << "!\n";
        playerBalance += (winnings - betAmount); // net profit added
    } else {
        std::cout << " Ah Try Again Dude , You lost $" << betAmount << ".\n";
        playerBalance -= betAmount;
    }

    std::cout << "Your New balance: $" << playerBalance << "\n";
}
