# QBackTest

C++ Backtesting engine focusing on cryptocurrencies.

## Features

- Creation of bots without compilation, JSON format is used to create as many bots as required (see example below)
- Multiple indicators
- Complete GUI for data loading, pre-processing, processing & visualisation
- Support to process data from various exchanges (see currently support exchanges)


### Currently support exchanges 
- Binance: https://github.com/binance/binance-public-data/

### BOT SYNTAX

Bots are written in JSON and follow the following basic structure:
```json
[
  {
    "name": "Bot_1",
    "funds": 10000,
    "assets": 0,
    "actions": [
      {
        "actionType": "BUY",
        "orderType": "LIMIT",
        "orderPrice" : "2%",
        "orderAmount": "5%",
        "triggers": [
          {
            "indicator": "MA50",
            "triggerColumn": "Close",
            "triggerType": "GT",
            "triggerValue": "10%"
          },
          {
            "indicator": "MA100",
            "triggerColumn": "Close",
            "triggerType": "GT"
          }
        ]
      },
      {
        "actionType": "SELL",
        "orderType": "LIMIT",
        "orderPrice": "-2%",
        "orderAmount": "3%",
        "triggers": [
          {
            "indicator": "MA50",
            "triggerColumn": "Close",
            "triggerType": "LT"
          },
          {
            "indicator": "MA100",
            "triggerColumn": "Close",
            "triggerType": "LT"
          }
        ]
      }
    ]
  }
]
```

To break this example down, the bots.json file may contain multiple bots.

Each bot is encapsulated in braces {} and must contain:
- `name` string name for bot
- `funds` numerical amount of starting funds
- `assets` numerical amount of starting assets
- `actions` array of actions with the below format

Each action has the following parameters:

- `actionType` -> _"BUY" "SELL" "CANCEL"_
- `orderType` -> _"LIMIT" "MARKET"_
- `orderPrice` -> (not required for MARKET order) % price to sell order at, can be negative
- `orderAmount` -> percentage of assets to sell

Each action then allows for potentially multiple "triggers" i.e. indicators.
Once all indicators return true, the action will take place

Each trigger has the following parameters:
- `indicator` -> See supported indicators for full list
- `triggerColumn` -> Which data column the indicator should use
- `triggerType` -> _"GT" "LT" "EQ"_ Greater, less than or equal to trigger column
- `triggerValue` -> optional parameter, can be used to fine tune trigger i.e. return `True` if MA50 is Greater-Then close price + 10%

### Supported indicators
- TODO:

## Dependencies

- glad
- glfw
- Dear Imgui
- L2DFileDialog
- rapid-csv

## Building Requirements

- C++ Version 17
- CMake
- Dependencies automatically included in CMakeLists, internet connection required during initial compilation
- gcc 10.0 +

## TODO
- Implement Bot Manager
- Implement Visualisation
- Implement Data Engine
- Implement IMGUI extensions: https://github.com/ocornut/imgui/wiki/Useful-Extensions#file-browsers--file-dialog