#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Game.hpp"

class CasinoManager {
public:
    CasinoManager(const std::string& name, int age, double balance);
    void start();
private:
    std::string playerName;
    int playerAge;
    double playerBalance;
    double initialBalance;
    std::vector<std::shared_ptr<Game>> games;
    void showMenu();
    void addGame(const std::shared_ptr<Game>& game);
    void printProfitLoss() const;
}; 