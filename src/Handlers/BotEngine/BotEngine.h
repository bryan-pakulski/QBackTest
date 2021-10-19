#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <json.hpp>

class Bot;

struct trigger {
    std::string indicator;
    std::string triggerColumn;
    std::string triggerValue;
};

struct action {
    int triggerAction;
    int orderType;
    std::vector<trigger> triggers;
};

class BotEngine {
public:
    BotEngine();
    ~BotEngine();

    void loadBots();
    bool isLoaded();

	bool getValidJSON();
	void setValidJSON(bool value);

private:
    std::vector<Bot> bots;
    nlohmann::json botData;
	bool validJSON = true;

    static std::vector<action> getBotActions(nlohmann::json data);
};

class Bot {
public:
    std::string name;

private:
    std::vector<action> actions;
    friend class BotEngine;
};