# QBackTest

C++ Backtesting engine focusing on cryptocurrencies.

## Features

- Complete GUI for data loading, pre-processing, processing & visualisation
- Conversion tools to process data from various exchanges (see currently support exchanges)
- Creation of bots without compilation, JSON format is used to create as many bots as required (see example below)
- Multiple indicators supported (see below for list)

### Currently support exchanges 
- Binance

### Example Bot
```json
{
  "name": "test_bot1",
  "actions": [
    {
      "...": "..."
    }
  ]
}
```

### Supported indicators
- SMA
- BOLLINGER

## Dependencies

- glad
- glfw
- Dear Imgui
- fast-cpp-csv-parser

## Building

CmakeLists contains all dependency links via github, running cmake should automatically build the QBackTest application.
