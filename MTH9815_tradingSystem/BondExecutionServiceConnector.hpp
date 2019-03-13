/**
 * BondExecutionServiceConnector.hpp
 * receive data from BondExecutionService and print it out
 */ 
#pragma once

#ifndef	BONDEXECUTIONSERVICECONNECTOR_HPP
#define BONDEXECUTIONSERVICECONNECTOR_HPP

using namespace std;

#include "BondExecutionService.hpp"
#include "soa.hpp"
#include "products.hpp"
#include <string>
#include <iostream>

class BondExecutionServiceConnector:public Connector<ExecutionOrder<Bond> >{
public:
    // ctor
    BondExecutionServiceConnector();

    // override pure virtual functions in base class
	// print ExecutionOrder. called by BondExecutionService
    virtual void Publish(ExecutionOrder<Bond>& data) override;   
	
	// publish only, no subsribe
    virtual void Subscribe() override;   
};

BondExecutionServiceConnector::BondExecutionServiceConnector(){}

void BondExecutionServiceConnector::Publish(ExecutionOrder<Bond>& data){
	auto bond=data.GetProduct();
	string oderType;
	switch(data.GetOrderType()) {
		case FOK: oderType = "FOK"; break;
		case MARKET: oderType = "MARKET"; break;
		case LIMIT: oderType = "LIMIT"; break;
		case STOP: oderType = "STOP"; break;
		case IOC: oderType = "IOC"; break; 
	}
	cout<<bond.GetProductId()<<" OrderId: "<<data.GetOrderId()<< "\n"
		<<"    PricingSide: "<<(data.GetSide()==BID? "Bid":"Ask")
		<<" OrderType: "<<oderType<<" IsChildOrder: "<<(data.IsChildOrder()?"True":"False")
		<<"\n"
		<<"    Price: "<<data.GetPrice()<<" VisibleQuantity: "<<data.GetVisibleQuantity()
		<<" HiddenQuantity: "<<data.GetHiddenQuantity()<<"\n"<<endl;
		
	return;
}

void BondExecutionServiceConnector::Subscribe(){
	return;
}

void BondExecutionService::ExecuteOrder(ExecutionOrder<Bond> &order, Market market){
	bondExecutionServiceConnector->Publish(order);
} 
#endif