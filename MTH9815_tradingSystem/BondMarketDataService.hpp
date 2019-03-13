/*
 * BondMarketDataService.hpp
 * define BondMarketDataService to receive data from BondMarketDataServiceConnector
 * and pass to BondAlgoExecutionService
 */ 
#pragma once

#ifndef BONDMARKETDATASERVICE_HPP
#define BONDMARKETDATASERVICE_HPP

using namespace std; 

#include "BondMarketDataServiceConnector.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class BondMarketDataService:public MarketDataService<Bond>{
private:
	map<string, OrderBook<Bond> > orderMap;
	vector<ServiceListener<OrderBook<Bond> >*> listenerList;      
                        
public:
	// ctor
	BondMarketDataService();
	
	// override pure virtual functions in base class
	// get order book given id
    virtual OrderBook<Bond> & GetData(string id) override;   
	
	// called by BondMarketDataServiceConnector, add an orderBook to map
	virtual void OnMessage(OrderBook<Bond> &orderBook) override;  

	// add its listener, in this case, BondAlgoExecutionServiceListener
    virtual void AddListener(ServiceListener<OrderBook<Bond> > *listener) override;  
	
	// get its listener, in this case, BondAlgoExecutionServiceListener
    virtual const vector<ServiceListener<OrderBook<Bond> > *>& GetListeners() const override;  
	
	// return the highest bid and lowest ask
    virtual BidOffer GetBestBidOffer(const string &productId) override;  
	
	// if prices in the bid/ask vectors are same, merge the quantity together
    virtual OrderBook<Bond> AggregateDepth(const string &productId) override;  
};

BondMarketDataService::BondMarketDataService(){
	orderMap=map<string, OrderBook<Bond> >();
}

OrderBook<Bond> & BondMarketDataService::GetData(string id){
	return orderMap.at(id);
}

void BondMarketDataService::OnMessage(OrderBook<Bond> & orderBook){
	auto id=orderBook.GetProduct().GetProductId();
	if(orderMap.find(id)!=orderMap.end())
		orderMap.erase(id);
	orderMap.insert(pair<string,OrderBook<Bond> >(id,orderBook));
	
	auto bestOrder=GetBestBidOffer(id);
	vector<Order> bid,ask;
	bid.push_back(bestOrder.GetBidOrder());
	ask.push_back(bestOrder.GetOfferOrder());
	OrderBook<Bond> bestBook=OrderBook<Bond>(orderBook.GetProduct(),bid,ask);
	
	for(auto& listener:listenerList){
		listener->ProcessAdd(bestBook);
	}
	return;
}

void BondMarketDataService::AddListener(ServiceListener<OrderBook<Bond> > *listener) {
    listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<OrderBook<Bond> > *>& BondMarketDataService::GetListeners() const{
	return listenerList;
}

BidOffer BondMarketDataService::GetBestBidOffer(const string &productId){
	auto orderBook = orderMap.at(productId);
	auto bidStack=orderBook.GetBidStack();
	auto askStack=orderBook.GetOfferStack();
	auto bestBid=bidStack[0];
	auto bestAsk=askStack[0];
	
	for(auto& item:bidStack){
		if(item.GetPrice()>bestBid.GetPrice())
			bestBid=item;
	}
	
	for(auto& item:askStack){
		if(item.GetPrice()<bestAsk.GetPrice())
			bestAsk=item;
	}
    return BidOffer(bestBid,bestAsk);
}

OrderBook<Bond> BondMarketDataService::AggregateDepth(const string &productId){
	auto orderBook = orderMap.at(productId);
	auto bidStack=orderBook.GetBidStack();
	auto askStack=orderBook.GetOfferStack();
	
	// if price is same, merge quantity
	unordered_map<double,long> bidRecord,askRecord;
	for(auto& item:bidStack){
		if(bidRecord.find(item.GetPrice())!=bidRecord.end())
			bidRecord[item.GetPrice()]+=item.GetQuantity();
		else 
			bidRecord[item.GetPrice()]=item.GetQuantity();
	}
	for(auto& item:askStack){
		if(askRecord.find(item.GetPrice())!=askRecord.end())
			askRecord[item.GetPrice()]+=item.GetQuantity();
		else 
			askRecord[item.GetPrice()]=item.GetQuantity();
	}

	// reinsert vectors
	vector<Order> bidStack_,askStack_;
	for(auto& item:bidRecord){
		bidStack_.push_back(Order(item.first,item.second,BID));
	}
	for(auto& item:askRecord){
		askStack_.push_back(Order(item.first,item.second,OFFER));
	}

	auto b=orderBook.GetProduct();
	return OrderBook<Bond>(b,bidStack_,askStack_);
}


void BondMarketDataServiceConnector::Subscribe(){
	ifstream input;
	input.open("marketdata.txt");
	string row;
	
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		vector<Order> bidStack,askStack;
		
		getline(line, temp, ',');    
		auto bond = bondProductService->GetData(temp);
		
		for(int i=0;i<10;++i){
			getline(line, temp, ',');
			auto price = TransformStringToPrice(temp);
			getline(line, temp, ',');
			auto quantity = stol(temp);
			getline(line, temp, ',');
			auto side = temp;
			if(i<5){
				bidStack.push_back(Order(price,quantity,BID));
			}
			else{
				askStack.push_back(Order(price,quantity,OFFER));
			}
		}
		
		OrderBook<Bond> orderBook(bond, bidStack, askStack);
		bondMarketDataService -> OnMessage(orderBook);
	}
	return;
}
#endif