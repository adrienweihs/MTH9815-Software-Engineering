/**
 * BondAlgoExectuionServiceListener.hpp
 * define listener to pass data from BondMarketDataService
 * to BondAlgoExecutionService
 */ 
#pragma once 

#ifndef BONDALGOEXECUTIONSERVICELISTENER_HPP
#define BONDALGOEXECUTIONSERVICELISTENER_HPP

using namespace std;

#include "BondAlgoExecutionService.hpp"
#include "soa.hpp"

class BondAlgoExecutionServiceListener: public ServiceListener<OrderBook<Bond> >{
private:
    BondAlgoExecutionService* bondAlgoExecutionService;
public:
    //ctor
    BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionService);

    // override the pure virtual functions in base class
	// called by BondMarketDataService and call AddOrderBook in BondAlgoExecutionService
    virtual void ProcessAdd(OrderBook<Bond> &data) override; 
	
	// no use in this case
    virtual void ProcessRemove(OrderBook<Bond> &data) override{};  
	
	// no use in this case
    virtual void ProcessUpdate(OrderBook<Bond> &data) override{};  
};

BondAlgoExecutionServiceListener::BondAlgoExecutionServiceListener(BondAlgoExecutionService* _bondAlgoExecutionService){
	bondAlgoExecutionService=_bondAlgoExecutionService;
}

void BondAlgoExecutionServiceListener::ProcessAdd(OrderBook<Bond> &data){
	bondAlgoExecutionService -> AddOrderBook(data);
	return;
}

#endif