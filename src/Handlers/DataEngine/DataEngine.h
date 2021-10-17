#pragma once

#include "../../QuanLogger.h"
#include "csv.h"

class DataEngine {
public:
	DataEngine();
	~DataEngine();

	static void loadData(std::string filePath);
};

