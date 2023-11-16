#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class StockTrade {
private:
    int tradeID;
    std::string stockSymbol;
    std::string tradeType;
    int quantity;
    double price;

public:
    StockTrade()
        : tradeID(0), stockSymbol(""), tradeType("BUY"), quantity(0), price(0.0) {}

    StockTrade(int id, const std::string& symbol, const std::string& type, int qty, double pr)
        : tradeID(id), stockSymbol(symbol), tradeType(type), quantity(qty), price(pr) {}

    int getTradeID() const { return tradeID; }
    std::string getStockSymbol() const { return stockSymbol; }
    std::string getTradeType() const { return tradeType; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setTradeID(int id) { tradeID = id; }
    void setStockSymbol(const std::string& symbol) { stockSymbol = symbol; }
    void setTradeType(const std::string& type) { tradeType = type; }
    void setQuantity(int qty) { quantity = qty; }
    void setPrice(double pr) { price = pr; }

    double calculateTradeValue() const {
        return static_cast<double>(quantity) * price;
    }
};
