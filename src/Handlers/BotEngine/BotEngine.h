#pragma once

#include <string>
#include <vector>
#include <fstream>

#include <json.hpp>
#include "Bot.h"

class Bot;


class BotEngine {
public:
    BotEngine();
    ~BotEngine();

    void loadBots();
	std::string getBots();
    bool isLoaded();

	bool validDataSource();
	void setValidJSON(bool value);

private:
    std::vector<Bot> bots;
	bool validJSON = true;

	void rollBack();
    std::vector<action> getBotActions(nlohmann::json data);
};
