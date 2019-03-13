/*
 * BondAlgoExecutionService.hpp
 * defines BondAlgoExecutionService to received datafrom BondMarketDataService
 * and pass to BondExecutionService
 */ 
#pragma once

#ifndef BONDALGOEXECUTIONSERVICE_HPP
#define BONDALGOEXECUTIONSERVICE_HPP

using namespace std;

#include "AlgoExecution.hpp"

class BondAlgoExecutionService: public Service<string, AlgoExecution>{
private:
	map<string,AlgoExecution> algoMap;
	vector<ServiceListener<AlgoExecution >*> listenerList;      
	
public:
    // ctor
    BondAlgoExecutionService();

    // override pure virtual functions in base class 
	// get algoExecution by id 
    AlgoExecution & GetData(string id);       
	
	// called by conector, in this case, no connector
    void OnMessage(AlgoExecution &);                
	
	// add a listener. in this case, BondExecutionServiceListener
    void AddListener(ServiceListener<AlgoExecution> *listener);  
	
	// get listeners. in this case, BondExecutionServiceListener
    const vector<ServiceListener<AlgoExecution> *>& GetListeners() const;  
	
	// add a order book and call RunAlgo in corresponding AlgoExecution
	// called by BondAlgoExecutionServiceListener
    void AddOrderBook(OrderBook<Bond>& orderBook);        
};

BondAlgoExecutionService::BondAlgoExecutionService(){
	algoMap=map<string, AlgoExecution>();
}

AlgoExecution& BondAlgoExecutionService::GetData(string id){
	return algoMap.at(id);
}

void BondAlgoExecutionService::OnMessage(AlgoExecution & a){
	return;
}

void BondAlgoExecutionService::AddListener(ServiceListener<AlgoExecution> *listener){
	listenerList.push_back(listener);
	return;
}

const vector<ServiceListener<AlgoExecution> *>& BondAlgoExecutionService::GetListeners() const{
	return listenerList;
}

void BondAlgoExecutionService::AddOrderBook(OrderBook<Bond>& orderBook){
	auto id=orderBook.GetProduct().GetProductId();
	auto it=algoMap.find(id);
	// if already exist, update price by RunAlgo
	if(it!=algoMap.end()){
		(it->second).RunAlgo(orderBook);
	}
	
	// add an empty AlgoStream as value. now as id already in map,
	// call AddPrice again to update price by RunAlgo
	else{
		auto eo=ExecutionOrder<Bond>(orderBook.GetProduct(),BID,"0",FOK,0,0,0,"0",true);	
		algoMap.insert(pair<string,AlgoExecution >(id,AlgoExecution(eo)));
		AddOrderBook(orderBook);
		return;
	}
	
	// notify the listeners
	for(auto& listener:listenerList){
		listener->ProcessAdd(it->second);
	}

	return;
}
#endif 