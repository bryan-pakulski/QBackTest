#pragma once

#include <iomanip>
#include <ctime>
#include <algorithm>
#include <fstream>

class QLogger {

public:

	static QLogger &GetInstance() {
		static QLogger logger;
		return logger;
	}

	/*
	 * Handle a generic captured exception (C++11) using the ... operator
	 * Exception is rethrown and error is logged
	 *
	 * @param ePtr
	 */
	static void ExceptionHandler(std::exception_ptr ePtr) {
		try {
			if (ePtr) {
				std::rethrow_exception(ePtr);
			}
		} catch (const std::exception &e) {
			QLogger::GetInstance().Error(std::string("Caught Exception: ").append(e.what()));
		}
	}

	void Error(const std::string& message, ...) {
		log << std::string(getDateTime()).append(" - [ERROR]: ") << message << std::endl;
	}

	void Warning(const std::string& message, ...) {
		log << std::string(getDateTime()).append(" - [WARN]: ") << message << std::endl;
	}

	void Info(const std::string& message, ...) {
		log << std::string(getDateTime()).append(" - [INFO]: ") << message << std::endl;
	}

	// Prohibit external replication constructs
	QLogger(QLogger const&) = delete;

	// Prohibit external assignment operations
	void operator=(QLogger const&) = delete;

private:
	// Output file
	std::ofstream log;

	// Open file on instantiation
	QLogger() {
		log.open("QLog.txt", std::ios_base::app);
	}

	~QLogger() {
		log.close();
	}

	/*
	 * Gets current date time, strips new lines and returns string
	 *
	 * @return string
	 */
	static std::string getDateTime() {
		time_t _tm = time(nullptr );
		struct tm * curtime = localtime ( &_tm );
		std::string strTime = std::string(asctime(curtime));
		strTime.erase(std::remove(strTime.begin(), strTime.end(), '\n'), strTime.end());

		return strTime;
	}
};