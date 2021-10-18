#include "DataEngine.h"

#include <iostream>

void DataEngine::loadData(std::string filePath) {

    try {
        io::CSVReader<3> in(filePath);
        in.read_header(io::ignore_extra_column, "vendor", "size", "speed");

        std::string vendor; int size; double speed;

        while(in.read_row(vendor, size, speed)){
            // do stuff with the data
        }
    } catch (io::error::can_not_open_file){
        ErrorHandler::GetInstance().setError("Unable to open file: " + filePath);
    }
}

DataEngine::DataEngine() {

}

DataEngine::~DataEngine() {

}
