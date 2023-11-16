#pragma once
#include <iostream>
#include <vector>


class StockPosition {
private:
    //int stockID;
    std::string stockSymbol;
    int share;
    double avgCost;
    double curPrice;
    double gainLoss;
    double realizedGainLoss;

public:
    StockPosition()
        : stockSymbol(""), share(0), avgCost(0), curPrice(0.0), gainLoss(0.0), realizedGainLoss(0.0) {
    }

    StockPosition(const std::string& symbol, int s, double ac, double cv, double gl, double rgl)
        : stockSymbol(symbol), share(s), avgCost(ac), curPrice(cv), gainLoss(gl), realizedGainLoss(rgl) {
    }

    //int getStockID() const { return stockID; }
    std::string getStockSymbol() const { return stockSymbol; }
    int getShare() const { return share; }
    double getAvgCost() const { return avgCost; }
    double getCurVal() const { return curPrice; }
    double getGainLoss() const { return gainLoss; }
    double getRealizedGainLoss() const { return realizedGainLoss; }

    //void setStockID(int sid) { stockID = sid; }
    void setStockSymbol(const std::string& symbol) { stockSymbol = symbol; }
    void setShare(int s) { share = s; }
    void setAvgCost(double ac) { avgCost = ac; }
    void setCurPrice(double cv) { curPrice = cv; }
    void setGainLoss(double gl) { gainLoss = gl; }
    void setRealizedGainLoss(double rgl) { realizedGainLoss = rgl; }

    double calculateGainLoss() const {
        return static_cast<double>(share) * (curPrice - avgCost);
    }

    double calculateRealizedGainLoss(int soldShares, double salePrice) const {
        return static_cast<double>(soldShares) * (salePrice - avgCost);
    }
};

