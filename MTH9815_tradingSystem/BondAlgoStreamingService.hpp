/**
 * BondAlgoStreamingService.hpp
 * Defines BondAlgoStreamingService class. Receive data from BondPricingService
 * and send data tp BondStreamingService
 * 
 */ 
#pragma once

#ifndef BONDALGOSTREAMINGSERVICE_HPP
#define BONDALGOSTREAMINGSERVICE_HPP

#include "AlgoStream.hpp"
#include "products.hpp"
#include <map>
#include <vector>
#include <string>
#include "soa.hpp"

using namespace std;

class BondAlgoStreamingService: public Service<string, AlgoStream>{
private:
	map<string, AlgoStream > algoMap; 
	vector<ServiceListener<AlgoStream>* > listenerList;  
public:
	// ctor
    BondAlgoStreamingService();

    // override pure virual functions in Service
	// get AlgoStream given id 
    virtual AlgoStream& GetData(string id) override;              
	
	// in this case, no connector call OnMessage method
    virtual void OnMessage(AlgoStream &) override;                   
	
	// add a listener. In this case, listener is BondStreamingServiceListener
    virtual void AddListener(ServiceListener<AlgoStream> *listener) override;  
	
	// get listeners. In this case, listener is BondStreamingServiceListener
    virtual const vector<ServiceListener<AlgoStream> *>& GetListeners() const override;  
	
	// add price to update/initialize a new AlgoStream in algomap
	// called by BondAlgoStreamingServiceListener to pass a new price from BondPricingService
    void AddPrice(const Price<Bond>& price);       
		
};

BondAlgoStreamingService::BondAlgoStreamingService(){
	algoMap=map<string, AlgoStream>();
}

AlgoStream& BondAlgoStreamingService::GetData(string id){
	return algoMap.at(id);
}

void BondAlgoStreamingService::OnMessage(AlgoStream & algo){
}

void BondAlgoStreamingService::AddListener(ServiceListener<AlgoStream> *listener){
	listenerList.push_back(listener);
}

const vector<ServiceListener<AlgoStream> *>& BondAlgoStreamingService::GetListeners() const{
	return listenerList;
}

void BondAlgoStreamingService::AddPrice(const Price<Bond>& price){
	auto id=price.GetProduct().GetProductId();
	auto it=algoMap.find(id);
	// if already exist, update price by RunAlgo
	if(it!=algoMap.end()){
		(it->second).RunAlgo(price);
	}
	// add an empty AlgoStream as value. now as id already in map,
	// call AddPrice again to update price by RunAlgo
	else{
		PriceStreamOrder p1(0, 0, 0, BID);
		PriceStreamOrder p2(0, 0, 0, OFFER);
		PriceStream<Bond> ps(price.GetProduct(), p1, p2);
		algoMap.insert(pair<string,PriceStream<Bond> >(id,ps));
		AddPrice(price);
		return;
	}
	
	// notify the listeners
	for(auto& listener:listenerList){
		listener->ProcessAdd(it->second);
	}

	return;
}
#endif