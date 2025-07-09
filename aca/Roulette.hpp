#pragma once
#include "Game.hpp"
#include <string>
#include <vector>

struct RouletteBet {
    std::string type;
    int number;
    double amount;
};

class Roulette : public Game {
public:
    Roulette(const std::string& playerName, double initialBalance);

    void play(double& playerBalance) override;
    std::string getName() const override { return "Roulette"; }

    // For testing
    double payoutForBet(const RouletteBet& bet, int result) const;
    std::string colorOf(int number) const;

private:
    std::string playerName;
    double initialBalance;
    std::vector<int> redNumbers;
    std::vector<int> blackNumbers;
    void setupColors();
    void printBoard() const;
    bool parseBet(const std::string& line, RouletteBet& bet) const;
};