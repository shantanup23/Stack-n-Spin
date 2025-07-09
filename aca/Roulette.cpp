#include "Roulette.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <cctype>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

Roulette::Roulette(const std::string& name, double bal)
    : playerName(name), initialBalance(bal)
{
    setupColors();
}
      
void Roulette::setupColors() {
    redNumbers   = {1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
    blackNumbers = {2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
}

std::string Roulette::colorOf(int number) const {
    if (number == 0) return "green";
    if (std::find(redNumbers.begin(), redNumbers.end(), number) != redNumbers.end())
        return "red";
    if (std::find(blackNumbers.begin(), blackNumbers.end(), number) != blackNumbers.end())
        return "black";
    return "unknown";
}

void Roulette::printBoard() const {
    std::cout << "\n--- Roulette Board ---\n";
    std::cout << "Place any of these bet types:\n";
    std::cout << "* Single number (0-36)     e.g. number 17 5\n";
    std::cout << "* Color: red/black         e.g. red 10 or black 8\n";
    std::cout << "* Odd/Even                 e.g. even 10 or odd 7\n";
    std::cout << "* Low (1-18) / High (19-36) e.g. low 5 or high 10\n";
    std::cout << "Type 'done' to spin the wheel.\n";
}

bool Roulette::parseBet(const std::string& line, RouletteBet& bet) const {
    std::string s = trim(line);
    if (s.empty()) return false;

    // Find first space (to split command and rest)
    size_t p1 = s.find(' ');
    std::string command = (p1 == std::string::npos) ? s : s.substr(0, p1);
    std::string rest = (p1 == std::string::npos) ? "" : trim(s.substr(p1 + 1));

    if (command == "number") {
        size_t p2 = rest.find(' ');
        if (p2 == std::string::npos) return false;
        std::string numStr = trim(rest.substr(0, p2));
        std::string amtStr = trim(rest.substr(p2 + 1));
        try {
            int number = std::stoi(numStr);
            double amount = std::stod(amtStr);
            if (number < 0 || number > 36 || amount <= 0) return false;
            bet.type = "number"; bet.number = number; bet.amount = amount;
            return true;
        } catch (...) { return false; }
    } else if (command == "red" || command == "black" || command == "odd" ||
               command == "even" || command == "low" || command == "high") {
        if (rest.empty()) return false;
        try {
            double amount = std::stod(rest);
            if (amount <= 0) return false;
            bet.type = command;
            bet.number = -1;
            bet.amount = amount;
            return true;
        } catch (...) { return false; }
    }
    return false;
}

double Roulette::payoutForBet(const RouletteBet& bet, int result) const {
    if (bet.type == "number") {
        if (result == bet.number)
            return bet.amount * 35.0;
    } else if (bet.type == "red" && colorOf(result) == "red") {
        return bet.amount * 1.0;
    } else if (bet.type == "black" && colorOf(result) == "black") {
        return bet.amount * 1.0;
    } else if (bet.type == "odd" && result != 0 && result % 2 == 1) {
        return bet.amount * 1.0;
    } else if (bet.type == "even" && result != 0 && result % 2 == 0) {
        return bet.amount * 1.0;
    } else if (bet.type == "low" && 1 <= result && result <= 18) {
        return bet.amount * 1.0;
    } else if (bet.type == "high" && 19 <= result && result <= 36) {
        return bet.amount * 1.0;
    }
    return -bet.amount;
}

void Roulette::play(double& playerBalance) {
    std::cout << "\n--- Welcome to Roulette, " << playerName << "! ---\n";
    printBoard();
    std::vector<RouletteBet> bets;
    double totalBet = 0.0;
    std::string line;

    while (true) {
        std::cout << "Enter bet: ";
        std::getline(std::cin, line);
        if (trim(line) == "done") break;
        RouletteBet bet;
        if (parseBet(line, bet)) {
            if (totalBet + bet.amount > playerBalance) {
                std::cout << "Not enough balance for this bet.\n";
                continue;
            }
            bets.push_back(bet);
            totalBet += bet.amount;
            std::cout << "Added bet of $" << bet.amount
                      << (bet.type == "number" ? (" on number " + std::to_string(bet.number)) : (" on " + bet.type))
                      << ".\n";
        } else {
            std::cout << "Invalid bet format. Please try again.\n";
        }
    }
    if (bets.empty()) {
        std::cout << "No bets placed. Returning to menu.\n";
        return;
    }
    playerBalance -= totalBet;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 36);
    int result = distrib(gen);

    std::cout << "\nSpinning the wheel...\nResult: " << result << " (" << colorOf(result) << ")\n";

    double winnings = 0.0;
    for (const auto& bet : bets) {
        double payout = payoutForBet(bet, result);
        if (payout > 0) {
            std::cout << "Won $" << payout << " on ";
        } else {
            std::cout << "Lost $" << bet.amount << " on ";
        }
        if (bet.type == "number") std::cout << "number " << bet.number;
        else std::cout << bet.type;
        std::cout << " bet.\n";
        if (payout > 0) winnings += payout + bet.amount;
    }
    playerBalance += winnings;
    std::cout << "New balance: $" << playerBalance << "\n";
}