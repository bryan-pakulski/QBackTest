#pragma once

#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include "../BotEngine/BotEngine.h"
#include <rapidcsv.h>

class DataEngine {
public:
	DataEngine();
	~DataEngine();

    void loadData(std::string filePath, int &fileSource);
    void processData(BotEngine &bEngine);
    bool isLoaded();

private:
    bool loadedFile = false;
    rapidcsv::Document data;
};

