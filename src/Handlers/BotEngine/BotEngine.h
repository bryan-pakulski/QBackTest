#pragma once

#include <json.hpp>
#include <string>
#include <vector>
#include <fstream>

struct indicator {
    std::string indicator;
    std::string triggerColumn;
    float triggerValue;
};

struct action {
    int triggerAction;
    int orderType;
    std::vector<indicator> triggers;
};

class Bot {
public:
    std::string name;

private:
    std::vector<action> actions;
};


class BotEngine {
public:
    BotEngine();
    ~BotEngine();

    void loadBots();

    bool isLoaded();

private:
    std::vector<Bot> bots;
    nlohmann::json botData;
};
