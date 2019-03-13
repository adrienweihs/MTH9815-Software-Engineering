/**
 * AlgoExecution.hpp
 * defines AlgoExecution, to be key of BondAlgoExecutionService
 */ 
#pragma once

#ifndef ALGOEXECUTION_HPP
#define ALGOEXECUTION_HPP

using namespace std;

#include "BondMarketDataService.hpp"
#include "executionservice.hpp"
#include <string>
#include <random>

class AlgoExecution {
private:
	static int order_ID;
	ExecutionOrder<Bond> executionOrder;
	
	// append c in front of v to make the length equal to width
	string FillCast(string v, int width, char c);
public:
	// ctor
	AlgoExecution(ExecutionOrder<Bond> _executionOrder);

	// run algo to update priceStream according to bond order book
	void RunAlgo(OrderBook<Bond> orderBook);

	// get the executionOrder
	ExecutionOrder<Bond> GetExecutionOrder() const;
};

int AlgoExecution::order_ID=0;

string AlgoExecution::FillCast(string v, int width, char c){
	string result;
	std::stringstream inter;
	inter << std::setw(width) << std::setfill(c) << v;
	inter >> result;
	return result;
}

AlgoExecution::AlgoExecution(ExecutionOrder<Bond> _executionOrder)
	:executionOrder(_executionOrder) {}

void AlgoExecution::RunAlgo(OrderBook<Bond> orderBook){
	auto bond=orderBook.GetProduct();
	// not this executionOrder to update
	if(bond.GetProductId() != executionOrder.GetProduct().GetProductId()) return;

    auto orderID = FillCast(to_string(order_ID),8,'0');
	
	OrderType orderType;
	int rd=rand()%5;
	switch(rd){
		case 0:orderType=FOK;break;
		case 1:orderType=IOC;break;
		case 2:orderType=MARKET;break;
		case 3:orderType=LIMIT;break;
		case 4:orderType=STOP;break;
	}
	PricingSide pricingSide=(rand()%2==0?BID:OFFER);
	
	
	auto bidOrder=orderBook.GetBidStack().begin();
	auto askOrder=orderBook.GetOfferStack().begin();
	
	double price;
	long visiableQ=0,hiddenQ;
	if(pricingSide==BID){
		price=bidOrder->GetPrice();
		if(askOrder->GetPrice()-bidOrder->GetPrice()<2.5/256.0)
			visiableQ=bidOrder->GetQuantity();
		hiddenQ=2*visiableQ;
	}
	else{
		price=askOrder->GetPrice();
		if(askOrder->GetPrice()-bidOrder->GetPrice()<2.5/256.0)
			visiableQ=askOrder->GetQuantity();
		hiddenQ=2*visiableQ;
	}
    
    string parentID = "P"+orderID ;

    executionOrder = ExecutionOrder<Bond>(bond,pricingSide,orderID,orderType,price,visiableQ,hiddenQ,parentID,true);
	
	++order_ID;
	return;
}

ExecutionOrder<Bond> AlgoExecution::GetExecutionOrder() const{
	return executionOrder;
}
#endif
