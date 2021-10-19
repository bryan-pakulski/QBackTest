#include "BotEngine.h"

#include <iostream>
#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include "DataMapping.h"


BotEngine::BotEngine() {

}

BotEngine::~BotEngine() {

}

/*
 * Loads bots from bots.json file and instantiates as a bot class
 * On Error botData is reset and error flag is set on GUI side to inform user
 */
void BotEngine::loadBots() {
    QLogger::GetInstance().Info("Loading bots.json");

    std::ifstream jsFile("bots.json");
    botData = nlohmann::json::parse(jsFile);

    for (nlohmann::json::iterator it = botData.begin(); it != botData.end(); ++it) {
        Bot newBot;

        auto data = it.value();

        for (auto& element : data) {

            if (element.is_string()) {
                newBot.name = element;
            } else if (element.is_array()) {
                newBot.actions = getBotActions(element);
            } else {
                ErrorHandler::GetInstance().setError("Malformed JSON, invalid type detected");
				botData = nlohmann::json();
				bots.clear();
				setValidJSON(false);
				return;
            }
        }

        bots.push_back(newBot);
    }
}

/*
 * Retrieve action data from JSON and map it using the DataMapping.h enumerations
 *
 * @param data
 * @return std::vector<action>
 */
std::vector<action> BotEngine::getBotActions(nlohmann::json data) {

	// TODO: Remake this function
    std::vector<action> actions;

    action botAction;

	std::cout << "Working with: " << data << std::endl;

    for (nlohmann::json::iterator it = data.begin(); it != data.end(); ++it) {

        if (it.key() == "triggerAction") {
            botAction.triggerAction = triggerActionMapping[it.value()];
        }
        if (it.key() == "orderType") {
            botAction.orderType = orderTypeMapping[it.value()];
        }
        if (it.key() == "triggers") {

            for (nlohmann::json::iterator indicator_it = it.value().begin(); indicator_it != it.value().end(); ++ indicator_it) {
                trigger botTrigger;

                botTrigger.indicator = indicator_it.value()["indicator"];
                botTrigger.triggerColumn = indicator_it.value()["triggerColumn"];
                botTrigger.triggerValue = indicator_it.value()["triggerValue"];

                botAction.triggers.push_back(botTrigger);
            }
        }

        actions.push_back(botAction);
    }

    return actions;
}


/*
 * Safety check for gui to avoid multiple calls to loadBots()
 * Checks whether botData is currently empty
 */
bool BotEngine::isLoaded() {
    return !botData.empty();
}

/*
 * Safety flag for if loading JSON file fails initially
 * Won't allow reloading until the JSON is fixed
 */
bool BotEngine::getValidJSON() {
	return validJSON;
}

void BotEngine::setValidJSON(bool value) {
	validJSON = value;
}