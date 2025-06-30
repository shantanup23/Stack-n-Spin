#include "Blackjack.hpp"
#include <iostream>
#include <random>
#include <algorithm>

Blackjack::Blackjack(const std::string& name, double balance)
    : playerName(name), initialBalance(balance) {}

std::string Blackjack::getName() const {
    return "Blackjack";
}

void Blackjack::initializeDeck() {
    static const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    static const std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    deck.clear();
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            deck.push_back({rank, suit});
        }
    }
}

void Blackjack::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

Card Blackjack::dealCard() {
    Card card = deck.back();
    deck.pop_back();
    return card;
}

int Blackjack::calculateHandValue(const std::vector<Card>& hand) const {
    int value = 0;
    int aces = 0;
    for (const auto& card : hand) {
        if (card.rank == "A") {
            value += 11;
            ++aces;
        } else if (card.rank == "K" || card.rank == "Q" || card.rank == "J") {
            value += 10;
        } else {
            value += std::stoi(card.rank);
        }
    }
    // Handle aces
    while (value > 21 && aces > 0) {
        value -= 10;
        --aces;
    }
    return value;
}

void Blackjack::printHand(const std::vector<Card>& hand, bool hideFirstCard) const {
    for (size_t i = 0; i < hand.size(); ++i) {
        if (i == 0 && hideFirstCard) {
            std::cout << "[Hidden], ";
        } else {
            std::cout << hand[i].rank << " of " << hand[i].suit;
            if (i != hand.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Blackjack::play(double& playerBalance) {
    std::cout << "\n--- Welcome to Blackjack, " << playerName << "! ---" << std::endl;
    double bet;
    std::cout << "Your current balance: $" << playerBalance << std::endl;
    std::cout << "Enter your bet: $";
    std::cin >> bet;
    if (bet > playerBalance || bet <= 0) {
        std::cout << "Dealer: Trying to rob the casino, eh? Place a valid bet!" << std::endl;
        return;
    }

    initializeDeck();
    shuffleDeck();

    std::vector<Card> playerHand, dealerHand;
    playerHand.push_back(dealCard());
    dealerHand.push_back(dealCard());
    playerHand.push_back(dealCard());
    dealerHand.push_back(dealCard());

    // Show hands
    std::cout << "Dealer's hand: ";
    printHand(dealerHand, true);
    std::cout << "Your hand: ";
    printHand(playerHand);

    // Player turn
    while (true) {
        int playerValue = calculateHandValue(playerHand);
        if (playerValue > 21) {
            std::cout << "Dealer: Busted! Did you think you were playing Go Fish?" << std::endl;
            playerBalance -= bet;
            return;
        }
        std::cout << "Your hand value: " << playerValue << std::endl;
        std::cout << "Hit or stand? (h/s): ";
        char choice;
        std::cin >> choice;
        if (choice == 'h' || choice == 'H') {
            playerHand.push_back(dealCard());
            std::cout << "Dealer: Bold move! You drew: " << playerHand.back().rank << " of " << playerHand.back().suit << std::endl;
        } else if (choice == 's' || choice == 'S') {
            std::cout << "Dealer: Standing already? Let's see what I've got..." << std::endl;
            break;
        } else {
            std::cout << "Dealer: I don't speak Martian. Please enter 'h' or 's'." << std::endl;
        }
    }

    // Dealer turn
    std::cout << "Dealer's hand: ";
    printHand(dealerHand);
    int dealerValue = calculateHandValue(dealerHand);
    while (dealerValue < 17) {
        dealerHand.push_back(dealCard());
        std::cout << "Dealer: Hitting myself... I drew: " << dealerHand.back().rank << " of " << dealerHand.back().suit << std::endl;
        dealerValue = calculateHandValue(dealerHand);
    }
    std::cout << "Dealer's final hand value: " << dealerValue << std::endl;

    int playerValue = calculateHandValue(playerHand);
    std::cout << "Your final hand value: " << playerValue << std::endl;

    // Determine winner
    if (playerValue > 21) {
        std::cout << "Dealer: You bust! The house thanks you for your donation." << std::endl;
        playerBalance -= bet;
    } else if (dealerValue > 21 || playerValue > dealerValue) {
        std::cout << "Dealer: You win! Did you bring a rabbit's foot?" << std::endl;
        playerBalance += bet;
    } else if (playerValue < dealerValue) {
        std::cout << "Dealer: I win! Don't worry, luck is just a state of mind." << std::endl;
        playerBalance -= bet;
    } else {
        std::cout << "Dealer: Push! It's a tie. Even I can't win every time." << std::endl;
    }
    std::cout << "New balance: $" << playerBalance << std::endl;
} 