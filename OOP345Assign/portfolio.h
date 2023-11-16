#pragma once
#include "StockPosition.h"
#include "TradeRecord.h"
#include <vector>
#include <memory>
#include <exception>
#include <string>
#include <iomanip>

using namespace std;

class Portfolio {
private:

    vector<StockPosition> portfolio;


public:
    //update portfolio when buying stocks
    void updatePortfolioBuy(const StockTrade& st) {
        vector<StockPosition>::iterator it;
        for (it = portfolio.begin(); it != portfolio.end(); it++) {
            if (it->getStockSymbol() != st.getStockSymbol()) {
                continue;
            }
            else {
                int newShare = it->getShare() + st.getQuantity();
                double newCost = (it->getAvgCost() * it->getShare() + st.getPrice() * st.getQuantity()) / newShare;
                it->setAvgCost(newCost);
                it->setShare(newShare);
                it->setCurPrice(st.getPrice());
                it->setGainLoss(it->calculateGainLoss());
                return;
            }
        }
        StockPosition sp;
        sp.setStockSymbol(st.getStockSymbol());
        sp.setShare(st.getQuantity());
        sp.setAvgCost(st.getPrice());
        sp.setCurPrice(st.getPrice());
        sp.setGainLoss(0.0);
        addStockPosition(sp);
        return;
    };

    //update portfolio when selling stocks
    void updatePortfolioSell(const StockTrade& st) {
        vector<StockPosition>::iterator it;
        for (it = portfolio.begin(); it != portfolio.end(); it++) {
            if (it->getStockSymbol() == st.getStockSymbol()) {
                int newShare = it->getShare() - st.getQuantity();
                double realizedGainLoss = it->calculateRealizedGainLoss(st.getQuantity(), st.getPrice());
                it->setShare(newShare);
                it->setCurPrice(st.getPrice());
                it->setRealizedGainLoss(realizedGainLoss);
                it->setGainLoss(it->calculateGainLoss());
                if (newShare == 0) {
                    portfolio.erase(it);
                }
                return;
            }
        }
    };

    //calculate the overall gain or loss of the portfolio
    double calculateOverallGainLoss() const {
        double overallGainLoss = 0.0;
        for (const auto& p : portfolio) {
            overallGainLoss += p.getGainLoss();
        }
        return overallGainLoss;
    }

    //calculate the overall realized gain or loss of the portfolio
    double calculateOverallRealizedGainLoss() const {
        double overallRealizedGainLoss = 0.0;
        for (const auto& p : portfolio) {
            overallRealizedGainLoss += p.getRealizedGainLoss();
        }
        return overallRealizedGainLoss;
    }

    //calculate the total value of the portfolio
    double calculateTotalValue() const {
        double totalValue = 0.0;
        for (const auto& p : portfolio) {
            totalValue += p.getShare() * p.getCurVal();
        }
        return totalValue;
    }

    //display portfolio
    void display() {
        cout << left << setw(15) << "Stock Symbol"
            << setw(10) << "Shares"
            << setw(15) << "Average Cost"
            << setw(15) << "Current Value"
            << setw(10) << "Gain/Loss"
            << setw(15) << "Realized Gain/Loss" << endl;
        cout << "------------------------------------------------------------------------------------" << endl;
        for (auto& p : portfolio) {
            cout << left << setw(15) << p.getStockSymbol()
                << setw(10) << p.getShare()
                << setw(15) << p.getAvgCost()
                << setw(15) << p.getCurVal()
                << setw(10) << p.getGainLoss()
                << setw(15) << p.getRealizedGainLoss() << endl;
        }
        cout << endl << "Portfolio Summary" << endl;
        cout << "--------------------" << endl;
        cout << "Total Portfolio Value: " << calculateTotalValue() << endl;
        cout << "Total Gain/Loss of Portfolio: " << calculateOverallGainLoss() << endl;
        cout << "Total Realized Gain/Loss of Portfolio: " << calculateOverallRealizedGainLoss();
    }

    void addStockPosition(StockPosition& sp) {
        portfolio.push_back(sp);
    }

    friend class TradeRecord;

};
