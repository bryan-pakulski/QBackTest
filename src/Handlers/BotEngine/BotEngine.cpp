#include "BotEngine.h"

#include <iostream>
#include "../../QLogger.h"

BotEngine::BotEngine() {

}

BotEngine::~BotEngine() {

}

void BotEngine::loadBots() {
    QLogger::GetInstance().Info("Loading bots.json");

    std::ifstream jsFile("bots.json");
    botData = nlohmann::json::parse(jsFile);

    // special iterator member functions for objects
    for (nlohmann::json::iterator it = botData.begin(); it != botData.end(); ++it) {
    }
}

/*
 * Safety check for gui to avoid multiple calls to loadBots()
 */
bool BotEngine::isLoaded() {
    return !botData.empty();
}

