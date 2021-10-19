#pragma once

#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include <rapidcsv.h>

class DataEngine {
public:
	DataEngine();
	~DataEngine();

    void loadData(std::string filePath, int &fileSource);
    void processData();
    bool isLoaded();

private:
    bool loadedFile = false;
    rapidcsv::Document data;
};

