#pragma once 

#ifndef HISTORICALEXECUTIONCONNECTOR_HPP
#define HISTORICALEXECUTIONCONNECTOR_HPP

using namespace std;

#include "soa.hpp"
#include "BondHistoricalDataService.hpp"
#include "GUIServiceConnector.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class HistoricalExecutionConnector: public Connector<ExecutionOrder<Bond> >{
public:
    // ctor
    HistoricalExecutionConnector(){};

    // do nothing, publish only
	virtual void Subscribe() override{}
	
	// print position
	virtual void Publish(ExecutionOrder<Bond>& data) override;
};


void HistoricalExecutionConnector::Publish(ExecutionOrder<Bond>& data) {
	auto bond=data.GetProduct();
	string oderType;
	switch(data.GetOrderType()) {
		case FOK: oderType = "FOK"; break;
		case MARKET: oderType = "MARKET"; break;
		case LIMIT: oderType = "LIMIT"; break;
		case STOP: oderType = "STOP"; break;
		case IOC: oderType = "IOC"; break; 
	}
	
    ofstream out;
    out.open("executions.txt",ios::app);
	out<<bond.GetProductId()<<","<<data.GetOrderId()
		<<","<<(data.GetSide()==BID? "Bid":"Ask")
		<<","<<oderType<<","<<(data.IsChildOrder()?"True":"False")
		<<","<<data.GetPrice()
		<<","<<data.GetVisibleQuantity()
		<<","<<data.GetHiddenQuantity()<<endl;

    return;
}

void BondHistoricalExecutionService::PersistData(string persistKey, ExecutionOrder<Bond>& data){
	auto id=data.GetOrderId();
	if(dataMap.find(id)!=dataMap.end())
		dataMap.erase(id);
	dataMap.insert(pair<string,ExecutionOrder<Bond> >(id,data));
	connector->Publish(data);
	return;
}



#endif