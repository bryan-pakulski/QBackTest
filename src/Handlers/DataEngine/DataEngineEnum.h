#pragma once

static const int Q_COLUMN_COUNT = 7;

enum DATA_SOURCES {BINANCE};
enum COLUMNS {OPEN_TIME, CLOSE_TIME, OPEN, CLOSE, HIGH, LOW, VOLUME};

static std::unordered_map<int, std::string> BINANCE_COLUMN_MAPPING({
	{0, "OpenTime"},
	{1, "Open"},
	{2, "High"},
	{3, "Low"},
	{4, "Close"},
	{5, "Volume"},
	{6, "CloseTime"},
	{7, "QuoteAssetVolume"},
	{8, "TakerBuyBaseAssetVolume"},
	{9, "TakerBuyQuoteAssetVolume"},
	{10, "Ignore"},
});

static std::unordered_map<int, std::string> DATA_ENGINE_COLUMN_MAPPING({
   {COLUMNS::OPEN_TIME, "OpenTime"},
   {COLUMNS::CLOSE_TIME, "CloseTime"},
   {COLUMNS::OPEN, "Open"},
   {COLUMNS::CLOSE, "Close"},
   {COLUMNS::HIGH, "High"},
   {COLUMNS::LOW, "Low"},
   {COLUMNS::VOLUME, "Volume"}
});