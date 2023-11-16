#pragma once
#include "StockTrade.h"
#include "Portfolio.h"
#include <vector>
#include <memory>
#include <exception>
#include <string>


using namespace std;

class TradeRecord {
private:
	vector<StockTrade> tradeRecord;
public:
	void addTrade(StockTrade& st) {
		tradeRecord.push_back(st);
	}

	//StockTrade recordTrade() {
	//	int tid, q;
	//	string symbol, type;
	//	double p;
	//	StockTrade st;

	//	//enter and validate trade id
	//	while (true) {
	//		try {
	//			cout << "Enter trade ID: ";
	//			cin >> tid;		
	//			validateTradeID(tid);
	//			st.setTradeID(tid);
	//			break;
	//		}
	//		catch (const std::invalid_argument& e) {
	//			std::cout << "Exception caught: " << e.what() << std::endl;
	//		}
	//	}

	//	//enter symbol
	//	std::cout << "Enter stock symbol: ";
	//	cin >> symbol;
	//	st.setStockSymbol(symbol);

	//	//enter and validate type;
	//	while (true) {
	//		try {
	//			cout << "Enter trade type: ";
	//			cin >> type;
	//			validateTradeType(type, symbol);
	//			st.setTradeType(type);
	//			break;
	//		}
	//		catch (const std::invalid_argument& e) {
	//			std::cout << "Exception caught: " << e.what() << std::endl;
	//		}
	//	}

	//	//enter and validate trade quantity
	//	while (true) {
	//		try {
	//			cout << "Enter trade quantity: ";
	//			cin >> q;
	//			validateQuantity(q, type, symbol);
	//			st.setQuantity(q);
	//			break;
	//		}
	//		catch (const std::invalid_argument& e) {
	//			std::cout << "Exception caught: " << e.what() << std::endl;
	//		}
	//	}

	//	//enter and validate trade price
	//	while (true) {
	//		try {
	//			cout << "Enter trade price: ";
	//			cin >> p;
	//			validatePrice(p);
	//			st.setPrice(p);
	//			break;
	//		}
	//		catch (const std::invalid_argument& e) {
	//			std::cout << "Exception caught: " << e.what() << std::endl;
	//		}
	//	}

	//	return st;
	//};

	//validate user input of trade id
	void validateTradeID(int tid) {
		for (const auto& record : tradeRecord) {
			if (record.getTradeID() == tid) {
				throw std::invalid_argument("Trade ID already exists.");
			}
		}
	};

	//validate user input of trade type
	void validateTradeType(string t, string s, Portfolio p) {
		vector<StockPosition>::iterator it;
		if (t != "buy" && t != "sell") {
			throw std::invalid_argument("Trade type must be either buy or sell");
		}
		if (t == "sell") {
			for (auto& sp : p.portfolio) {
				if (sp.getStockSymbol() == s) {
					return;
				}

			}
			throw std::invalid_argument("Stock doesn't exist.");
		}
	};

	//validate user input of trade quantity
	void validateQuantity(int q, string t, string s, Portfolio p) {
		if (q <= 0) {
			throw std::invalid_argument("Quantity must be greater than 0.");
		}
		if (t == "sell") {
			for (const auto& sp : p.portfolio) {
				if (sp.getStockSymbol() == s && sp.getShare() >= q) {
					return;

				}

			}
			throw std::invalid_argument("Quantity exceeds quantity held");
		}
	};

	//validate user input of trade price
	void validatePrice(double p) {
		if (p <= 0) {
			throw std::invalid_argument("Price must be greater than 0.");
		}
	};


};
