#include <iostream>

#include "DataEngine.h"
#include "DataEngineEnum.h"

void DataEngine::loadData(std::string filePath) {

    try {
        io::CSVReader<3> in(filePath);
        in.read_header(io::ignore_extra_column, "volume", "size", "speed");

        std::string vendor; int size; double speed;

        while(in.read_row(vendor, size, speed)){
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
