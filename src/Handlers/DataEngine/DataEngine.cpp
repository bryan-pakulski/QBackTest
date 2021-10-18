#include <iostream>

#include "DataEngine.h"
#include "DataEngineEnum.h"

void DataEngine::loadData(std::string filePath) {

    try {
        io::CSVReader<Q_COLUMN_COUNT> in(filePath);
        in.read_header(
			io::ignore_extra_column,
			COLUMN_MAPPING[COLUMNS::OPEN_TIME],
			COLUMN_MAPPING[COLUMNS::CLOSE_TIME],
			COLUMN_MAPPING[COLUMNS::OPEN],
			COLUMN_MAPPING[COLUMNS::CLOSE],
			COLUMN_MAPPING[COLUMNS::HIGH],
			COLUMN_MAPPING[COLUMNS::LOW],
			COLUMN_MAPPING[COLUMNS::VOLUME]
		);

        while(in.read_row(Q_openTime, Q_closeTime, Q_open, Q_close, Q_high, Q_low, Q_volume)){
            QLogger::GetInstance().Info("Loading file: " + filePath);
			// do stuff with the data
        }
    } catch (io::error::can_not_open_file) {
        ErrorHandler::GetInstance().setError("Unable to open file: " + filePath);
    } catch (io::error::missing_column_in_header) {
		ErrorHandler::GetInstance().setError("Missing columns in selected file, please make sure that the formatting is correct!");
	}
}

DataEngine::DataEngine() {

}

DataEngine::~DataEngine() {

}
