#include <iostream>

#include "DataEngine.h"
#include "DataEngineEnum.h"
#include "../../QLogger.h"

/*
 * Load data with respect to the original source of the document (defined as an enum when using the file dialog)
 * Mapping is performed so that the data engine understands which columns are required for processing
 *
 * @param filePath
 * @param fileSource
 */
void DataEngine::loadData(std::string filePath, int &fileSource) {

    try {
        data = rapidcsv::Document(filePath);

        // TODO: flag document loaded successfully
        loadedFile = true;

    } catch (std::exception) {
        ErrorHandler::GetInstance().setError("Unable to open file: %s" + filePath);
		loadedFile = false;
    }
}

/*
 * Returns True/False based on the success state of loadData
 *
 * @return bool
 */
bool DataEngine::isLoaded() {
    return loadedFile;
}

/*
 * Iterator to process row by row data, passing to Bot Engine
 */
void DataEngine::processData(BotEngine &bEngine) {
    QLogger::GetInstance().Info("Processing data file with: %d rows", data.GetRowCount());

    for (int rowIndex = 0; rowIndex < data.GetRowCount(); rowIndex++) {
        std::vector<std::string> rowData = data.GetRow<std::string>(rowIndex);

		// TODO: pass data to bot engine for processing
    }
}

DataEngine::DataEngine() {

}

DataEngine::~DataEngine() {

}