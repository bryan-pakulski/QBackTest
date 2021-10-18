#pragma once

#include "../../QLogger.h"
#include "../../Display/ErrorHandler.h"
#include <csv.h>

class DataEngine {
public:
	DataEngine();
	~DataEngine();

	static void loadData(std::string filePath);
};

