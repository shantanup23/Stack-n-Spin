#pragma once
#include <string>

class Game {
public:
    virtual ~Game() = default;
    virtual void play(double& playerBalance) = 0;
    virtual std::string getName() const = 0;
}; 