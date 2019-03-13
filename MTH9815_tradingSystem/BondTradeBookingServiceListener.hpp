/**
 * BondTradeBookingServiceListener.hpp
 * defines BondTradeBookingServiceListener class to pass data from 
 * BondExecutionService to BondTradeBookingService
 */ 
#pragma once

#ifndef BONDTRADEBOOKINGSERVICELISTENER_HPP
#define BONDTRADEBOOKINGSERVICELISTENER_HPP

#include "BondTradeBookingService.hpp"
#include "BondExecutionService.hpp"
#include "soa.hpp"
#include <string>

using namespace std;

class BondTradeBookingServiceListener: public ServiceListener<ExecutionOrder<Bond> >{
private:
    BondTradeBookingService* bondTradeBookingService;

public:
    // ctor
    BondTradeBookingServiceListener(BondTradeBookingService* _bondTradeBookingService);

    // override pure virtual functions in ServiceListener class
	// convert ExecutionOrder to Trade and pass to BondTradeBookingServce
    virtual void ProcessAdd(ExecutionOrder<Bond>& data) override; 
	
	// in this case, do not need this method
    virtual void ProcessRemove(ExecutionOrder<Bond> &data) override{}  
	
	// in this case, do not need this method
    virtual void ProcessUpdate(ExecutionOrder<Bond> &data) override{}
};

BondTradeBookingServiceListener::BondTradeBookingServiceListener(BondTradeBookingService* _bondTradeBookingService){
	bondTradeBookingService=_bondTradeBookingService;
}

void BondTradeBookingServiceListener::ProcessAdd(ExecutionOrder<Bond>& data){
	auto bond=data.GetProduct();
	string tradeID="Execution";
	auto price=data.GetPrice();
	string book="Book";
	auto quantity=data.GetVisibleQuantity();
	Side side=BUY;
	if(data.GetSide()==BID)
		side=SELL;
	Trade<Bond> trade(bond,tradeID,price,book,quantity,side);

	bondTradeBookingService->BookTrade(trade);
	return;
}

#endif