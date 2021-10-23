#include "BotEngine.h"

#include <iostream>
#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include "DataMapping.h"


BotEngine::BotEngine() {

}

BotEngine::~BotEngine() {

}

// Simple rollback function to capture errors
void BotEngine::rollBack() {
	ErrorHandler::GetInstance().setError("Malformed JSON..");
	setValidJSON(false);
	bots.clear();
}

/*
 * Loads bots from bots.json file and instantiates as a bot class
 * On Error botData is reset and error flag is set on GUI side to inform user
 */
void BotEngine::loadBots() {
    QLogger::GetInstance().Info("Loading bots.json");

	try {
		std::ifstream jsFile("bots.json");
		nlohmann::json botData = nlohmann::json::parse(jsFile);

		for (nlohmann::json::iterator it = botData.begin(); it != botData.end(); ++it) {
			Bot newBot;
			auto data = it.value();

			newBot.name = data["name"];
			newBot.funds = data["funds"];
			newBot.assets = data["assets"];
			newBot.actions = getBotActions(data["actions"]);

			bots.push_back(newBot);
		}
	} catch (...) {
		std::exception_ptr e = std::current_exception();
		QLogger::ExceptionHandler(e);
		rollBack();
	}
}

/*
 * Retrieve action data from JSON and map it using the DataMapping.h enumerations
 *
 * @param data
 * @return std::vector<action>
 * @throws exception_ptr
 */
std::vector<action> BotEngine::getBotActions(nlohmann::json data) {

	std::vector<action> actions;

	try {

		for (auto &botAction : data) {
			action currentAction;

			currentAction.actionType = triggerActionMapping[botAction["actionType"]];
			currentAction.orderType = orderTypeMapping[botAction["orderType"]];
			currentAction.orderPrice = botAction["orderPrice"];
			currentAction.orderAmount = botAction["orderAmount"];

			// Triggers
			for (auto &botTrigger : botAction["triggers"]) {
				trigger currentTrigger;

				currentTrigger.indicator = botTrigger["indicator"];
				currentTrigger.triggerColumn = botTrigger["triggerColumn"];
				currentTrigger.triggerType = botTrigger["triggerType"];

				// triggerValue is optional
				if (botTrigger.contains("triggerValue")) {
					currentTrigger.triggerValue = botTrigger["triggerValue"];
				}

				currentAction.triggers.push_back(currentTrigger);
			}

			actions.push_back(currentAction);
		}

		// TODO: parse data and retrieve actions
		std::cout << data << std::endl;

	} catch (...) {
		// Catch & Rethrow, to be caught in loadBots()
		std::exception_ptr e = std::current_exception();
		std::rethrow_exception(e);
	}

	return actions;
}


/*
 * Safety check for gui to avoid multiple calls to loadBots()
 * Checks whether bots vector is currently empty
 */
bool BotEngine::isLoaded() {
    return !bots.empty();
}

/*
 * Safety flag for if loading JSON file fails initially
 * Won't allow reloading until the JSON is fixed
 */
bool BotEngine::validDataSource() {
	return validJSON;
}

void BotEngine::setValidJSON(bool value) {
	validJSON = value;
}

std::string BotEngine::getBots() {
	std::string botList;

	for (Bot &b : bots) {
		botList.append(b.getName() + "\n");
	}

	return botList;
}
