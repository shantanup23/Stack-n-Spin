#include "SlotTycoon.hpp"
#include <iostream>
#include <iomanip>

SlotTycoon::SlotTycoon(const std::string& playerName, double initialBalance)
    : playerName(playerName), machineLevel(1), totalSpins(0), totalWins(0),
      totalInvested(0), totalReturned(0), rng(std::random_device{}()) {}

std::string SlotTycoon::getName() const {
    return "Virtual Slot City Tycoon";
}

void SlotTycoon::showMenu() const {
    std::cout << "\n--- Slot Tycoon Menu ---\n";
    std::cout << "1. Spin the Slot Machine\n";
    std::cout << "2. Upgrade Machine (Cost: $" << machineLevel * 300 << ")\n";
    std::cout << "3. View Stats\n";
    std::cout << "4. Exit\n";
}

void SlotTycoon::upgradeMachine(double& balance) {
    double cost = machineLevel * 300;
    if (balance >= cost) {
        balance -= cost;
        machineLevel++;
        std::cout << "Machine upgraded to Level " << machineLevel << "!\n";
    } else {
        std::cout << "Not enough balance to upgrade.\n";
    }
}

double SlotTycoon::getWinProbability() const {
    return 0.2 + (machineLevel * 0.05); // Level 1: 25%, Level 2: 30%, etc.
}

double SlotTycoon::getPayoutMultiplier() const {
    return 2.0 + (machineLevel * 0.5); // Level 1: 2.5x, Level 2: 3.0x, etc.
}

void SlotTycoon::spinMachine(double& balance) {
    double bet;
    std::cout << "Enter bet amount: $";
    std::cin >> bet;

    if (bet <= 0 || bet > balance) {
        std::cout << "Invalid bet.\n";
        return;
    }

    std::uniform_real_distribution<> dist(0.0, 1.0);
    double roll = dist(rng);
    balance -= bet;
    totalSpins++;
    totalInvested += bet;

    if (roll < getWinProbability()) {
        double winAmount = bet * getPayoutMultiplier();
        balance += winAmount;
        totalReturned += winAmount;
        totalWins++;
        std::cout << "🎉 You WIN! Payout: $" << std::fixed << std::setprecision(2) << winAmount << "\n";
    } else {
        std::cout << "💀 No luck. You lost the bet.\n";
    }
}

void SlotTycoon::showStats() const {
    std::cout << "\n--- Tycoon Stats ---\n";
    std::cout << "Machine Level: " << machineLevel << "\n";
    std::cout << "Total Spins: " << totalSpins << "\n";
    std::cout << "Total Wins: " << totalWins << "\n";
    std::cout << "Win Rate: " << (totalSpins > 0 ? (100.0 * totalWins / totalSpins) : 0) << "%\n";
    std::cout << "Total Invested: $" << totalInvested << "\n";
    std::cout << "Total Returned: $" << totalReturned << "\n";
    std::cout << "ROI: " << (totalInvested > 0 ? (100.0 * totalReturned / totalInvested) : 0) << "%\n";
}

void SlotTycoon::play(double& balance) {
    bool keepPlaying = true;
    while (keepPlaying) {
        std::cout << "\nWelcome, " << playerName << " | Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
        showMenu();

        int choice;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                spinMachine(balance);
                break;
            case 2:
                upgradeMachine(balance);
                break;
            case 3:
                showStats();
                break;
            case 4:
                keepPlaying = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
