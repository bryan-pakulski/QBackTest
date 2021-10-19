#include <iostream>

#include "DataEngine.h"
#include "DataEngineEnum.h"
#include "../../QLogger.h"

void DataEngine::loadData(std::string filePath, int &fileSource) {

    try {
		rapidcsv::Document doc(filePath);


    } catch (std::exception) {
        ErrorHandler::GetInstance().setError("Unable to open file: " + filePath);
    }
}

DataEngine::DataEngine() {

}

DataEngine::~DataEngine() {

}
