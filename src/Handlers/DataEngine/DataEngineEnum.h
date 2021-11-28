#pragma once

#include <string>
#include <unordered_map>

static const int Q_COLUMN_COUNT = 7;

enum DATA_SOURCES {BINANCE};
enum COLUMNS {OPEN_TIME, CLOSE_TIME, OPEN, CLOSE, HIGH, LOW, VOLUME};

struct Order {
	std::string openTime;
	std::string closeTime;
	std::string open;
	std::string close;
	std::string high;
	std::string low;
	std::string volume;
};

static std::unordered_map<int, std::string> BINANCE_COLUMN_MAPPING({
	{0, "openTime"},
	{1, "open"},
	{2, "high"},
	{3, "low"},
	{4, "close"},
	{5, "volume"},
	{6, "closeTime"},
	{7, "quoteAssetVolume"},
	{8, "takerBuyBaseAssetVolume"},
	{9, "takerBuyQuoteAssetVolume"},
	{10, "ignore"},
});

static std::unordered_map<int, std::string> DATA_ENGINE_COLUMN_MAPPING({
   {COLUMNS::OPEN_TIME, "openTime"},
   {COLUMNS::CLOSE_TIME, "closeTime"},
   {COLUMNS::OPEN, "open"},
   {COLUMNS::CLOSE, "close"},
   {COLUMNS::HIGH, "high"},
   {COLUMNS::LOW, "low"},
   {COLUMNS::VOLUME, "volume"}
});