/**
 * BondTradingBookingServiceConnector.hpp
 * extract data from trade.txt and pass to BoondTradeBookingService
 */ 
#pragma once

#ifndef BONDTRADINGBOOKINGSERVICECONNECTOR_HPP
#define BONDTRADINGBOOKINGSERVICECONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondTradeBookingService.hpp"
#include "tradebookingservice.hpp"
#include "BondProductService.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

class BondTradeBookingService;

class BondTradingBookingServiceConnector: public Connector<Trade<Bond> > {
private:
	BondTradeBookingService* bondTradeBookingService;
	BondProductService* bondProductService;

	// transform a string to price
	float TransformStringToPrice(string& s);
public:
	// ctor
	BondTradingBookingServiceConnector(BondTradeBookingService* _bondTradeBookingService, BondProductService* _bondProductService);

	// override pure virtual functions in base class
	// Subscribe only in this case
	virtual void Publish(Trade<Bond>& data) override {};
	
	// get data from trade.txt and pass toBondTradeBookingService
	virtual void Subscribe() override;
};

float BondTradingBookingServiceConnector::TransformStringToPrice(string& s) {
	int n=s.size();
	if(s[n-1]=='+')s[n-1]='4';
	return stoi(s.substr(0, n-4))+stoi(s.substr(n-3,2))/32.0+stoi(s.substr(n-1,1))/256.0;
}

BondTradingBookingServiceConnector::BondTradingBookingServiceConnector
(BondTradeBookingService* _bondTradeBookingService, BondProductService* _bondProductService) {
	bondTradeBookingService=_bondTradeBookingService;
	bondProductService= _bondProductService;
}

// define void BondTradingBookingServiceConnector::Subscribe() in BondTradeBookingService.hpp
	


#endif
