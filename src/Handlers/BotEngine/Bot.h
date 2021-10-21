#pragma once

#include <string>
#include <vector>

struct trigger {
	std::string indicator;
	std::string triggerColumn;
	std::string triggerType;
	std::string triggerValue;
};

struct action {
	int actionType;
	int orderType;
	std::string orderPrice;
	std::string orderAmount;
	std::vector<trigger> triggers;
};

class Bot {

public:
	Bot();
	~Bot();

	std::string getName();

private:
	std::string name;
	float funds;
	float assets;
	std::vector<action> actions;

	friend class BotEngine;
};