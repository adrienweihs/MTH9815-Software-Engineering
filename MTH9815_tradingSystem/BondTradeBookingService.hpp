/**
 * BondTradeBookingService.hpp
 * receive data from BondTradeBookingServiceConnector
 * and pass to BondPositionService 
 */ 
#pragma once

#ifndef BONDTRADEBOOKINGSERVICE_HPP
#define BONDTRADEBOOKINGSERVICE_HPP

using namespace std;

#include "BondTradingBookingServiceConnector.hpp"
#include "tradebookingservice.hpp"
#include <map>
#include <vector>
#include <string>

class BondTradeBookingService: public TradeBookingService<Bond>{
private:
	map<string, Trade<Bond> > tradeMap;
	vector<ServiceListener<Trade<Bond> >*> listenerList;     
public:
	// ctor
	BondTradeBookingService();

	// override pure virtual functions in base class
	// get Trade from tradeMap given id
	virtual Trade<Bond> & GetData(string id) override;              
	
	// called by BondTradingBookingServiceConnector, call BookTrade
	virtual void OnMessage(Trade<Bond> &trade) override;                  
	
	// add a listener, in this case, BondPositionServiceListener
	virtual void AddListener(ServiceListener<Trade<Bond> > *listener) override;  
	
	// get listeners, in this case, BondPositionServiceListener
	virtual const vector<ServiceListener<Trade<Bond> > *>& GetListeners() const override; 
	
	// called by OnMessage, add a trade to tradeMap
	virtual void BookTrade(Trade<Bond> trade) override;            
};


BondTradeBookingService::BondTradeBookingService(){
	tradeMap=map<string, Trade<Bond> >();
}

Trade<Bond> & BondTradeBookingService::GetData(string id){
	return tradeMap.at(id);
}             

void BondTradeBookingService::OnMessage(Trade<Bond> &trade){
	BookTrade(trade);
	return;
}                  

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond> > *listener){
	listenerList.push_back(listener);
	return;
} 

const vector<ServiceListener<Trade<Bond> > *>& BondTradeBookingService::GetListeners() const{
	return listenerList;
}

void BondTradeBookingService::BookTrade(Trade<Bond> trade){
	auto id=trade.GetProduct().GetProductId();
	if(tradeMap.find(id)!=tradeMap.end())
		tradeMap.erase(id);
	tradeMap.insert(pair<string,Trade<Bond> >(id,trade));
	
	for(auto& listener:listenerList){
		listener->ProcessAdd(trade);
	}
	return;
}           


void BondTradingBookingServiceConnector::Subscribe(){
	ifstream input;
	input.open("trades.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		getline(line, temp, ',');    
		auto bond = bondProductService->GetData(temp);
		
		getline(line, temp, ',');
		auto tradeID = temp;
		getline(line, temp, ',');
		auto price = TransformStringToPrice(temp);
		getline(line, temp, ',');
		auto book = temp;
		getline(line, temp, ',');
		long quantity = stol(temp);
		getline(line, temp, ',');
		Side side=(temp=="BUY"?BUY:SELL);		
		
		Trade<Bond> bondNew(bond,tradeID,price,book,quantity,side);
		bondTradeBookingService -> OnMessage(bondNew);
	}
	return;	
}


#endif