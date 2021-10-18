#pragma once

static const int Q_COLUMN_COUNT = 7;
enum COLUMNS {OPEN_TIME, CLOSE_TIME, OPEN, CLOSE, HIGH, LOW, VOLUME};

static std::unordered_map<int, std::string> COLUMN_MAPPING({
   {COLUMNS::OPEN_TIME, "OpenTime"},
   {COLUMNS::CLOSE_TIME, "CloseTime"},
   {COLUMNS::OPEN, "Open"},
   {COLUMNS::CLOSE, "Close"},
   {COLUMNS::HIGH, "High"},
   {COLUMNS::LOW, "Low"},
   {COLUMNS::VOLUME, "Volume"}
});

std::string Q_openTime;
std::string Q_closeTime;
double Q_open;
double Q_close;
double Q_high;
double Q_low;
double Q_volume;