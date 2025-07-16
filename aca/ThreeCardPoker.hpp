
#pragma once
#include "Game.hpp"
#include <string>

class ThreeCardPoker : public Game {
private:
    std::string playerName;
    double& playerBalance;

public:
    ThreeCardPoker(const std::string& name, double& balance);
    std::string getName() const override;
    void play(double& dummy) override;
};
