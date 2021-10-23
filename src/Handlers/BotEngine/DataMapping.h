#pragma once

#include <unordered_map>
#include <string>


enum orderType {
    MARKET,
    LIMIT
};

enum actionType {
    BUY,
    SELL,
    CANCEL
};

enum indicators {
    MA20,
    MA50,
    MA100,
};

std::unordered_map<std::string, int> orderTypeMapping({
    {"MARKET", orderType::MARKET},
    {"LIMIT",  orderType::LIMIT}
});

std::unordered_map<std::string, int> triggerActionMapping({
    {"BUY",    actionType::BUY},
    {"SELL",   actionType::SELL},
    {"CANCEL", actionType::CANCEL}
});

std::unordered_map<std::string, int> indicatorMapping({
    {"MA20",  indicators::MA20},
    {"MA50",  indicators::MA50},
    {"MA100", indicators::MA100}
});