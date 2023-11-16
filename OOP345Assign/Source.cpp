#include <iostream>
#include <memory>
#include "StockPosition.h"
#include "StockTrade.h"
#include "TradeRecord.h"
#include "Portfolio.h"

StockTrade recordTrade(TradeRecord& tr, Portfolio& pf) {
	int tid, q;
	string symbol, type;
	double p;
	StockTrade st;

	//enter and validate trade id
	while (true) {
		try {
			cout << "Enter trade ID: ";
			cin >> tid;
			tr.validateTradeID(tid);
			st.setTradeID(tid);
			break;
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	//enter symbol
	std::cout << "Enter stock symbol: ";
	cin >> symbol;
	st.setStockSymbol(symbol);

	//enter and validate type;
	while (true) {
		try {
			cout << "Enter trade type: ";
			cin >> type;
			tr.validateTradeType(type, symbol, pf);
			st.setTradeType(type);
			break;
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	//enter and validate trade quantity
	while (true) {
		try {
			cout << "Enter trade quantity: ";
			cin >> q;
			tr.validateQuantity(q, type, symbol, pf);
			st.setQuantity(q);
			break;
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	//enter and validate trade price
	while (true) {
		try {
			cout << "Enter trade price: ";
			cin >> p;
			tr.validatePrice(p);
			st.setPrice(p);
			break;
		}
		catch (const std::invalid_argument& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}

	return st;
};


int main() {
	Portfolio portfolio;

	TradeRecord tradeRecord;

	StockTrade st1(1, "asd", "buy", 30, 1.5);
	StockTrade st2(2, "qwe", "buy", 50, 7.5);
	StockTrade st3(3, "zxc", "buy", 80, 9.5);

	StockPosition sp1("asd", 30, 1.5, 1.5, 0, 0);
	StockPosition sp2("qwe", 50, 7.5, 7.5, 0, 0);
	StockPosition sp3("zxc", 80, 9.5, 9.5, 0, 0);

	tradeRecord.addTrade(st1);
	tradeRecord.addTrade(st2);
	tradeRecord.addTrade(st3);

	portfolio.addStockPosition(sp1);
	portfolio.addStockPosition(sp2);
	portfolio.addStockPosition(sp3);

	StockTrade newst = recordTrade(tradeRecord, portfolio);
	tradeRecord.addTrade(newst);

	if (newst.getTradeType() == "buy") {
		portfolio.updatePortfolioBuy(newst);
	}
	else {
		portfolio.updatePortfolioSell(newst);
	}

	portfolio.display();

	return 0;
}