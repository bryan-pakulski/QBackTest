#pragma once

#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include <rapidcsv.h>

class DataEngine {
public:
	DataEngine();
	~DataEngine();

	static void loadData(std::string filePath, int &fileSource);
};

