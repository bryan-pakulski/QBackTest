#include <iostream>

#include "DataEngine.h"
#include "DataEngineEnum.h"
#include "../../QLogger.h"

void DataEngine::loadData(std::string filePath, int &fileSource) {

    try {
        data = rapidcsv::Document(filePath);

        // TODO: flag document loaded successfully
        loadedFile = true;

    } catch (std::exception) {
        ErrorHandler::GetInstance().setError("Unable to open file: %s" + filePath);
    }
}

DataEngine::DataEngine() {

}

DataEngine::~DataEngine() {

}

bool DataEngine::isLoaded() {
    return loadedFile;
}

void DataEngine::processData() {
    QLogger::GetInstance().Info("Processing data file with: %d rows", data.GetRowCount());

    for (int rowIndex = 0; rowIndex < data.GetRowCount(); rowIndex++) {
        std::vector<std::string> rowData = data.GetRow<std::string>(rowIndex);
    }
}
