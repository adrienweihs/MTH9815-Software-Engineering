/**
 * BondPricingService.hpp
 * Defines BondPricingService to receive data from BondPricingConnector
 * and pass to BondAlgoStreamingService
 */ 
#pragma once

#ifndef BONDPRICINGSERVICE_HPP
#define BONDPRICINGSERVICE_HPP
#include "pricingservice.hpp"
#include "BondPricingServiceConnector.hpp"
#include "products.hpp"
#include "soa.hpp"
#include <map>
#include <vector>


using namespace std;

class BondPricingService: public PricingService<Bond>{
private:
	map<string, Price<Bond> > priceMap;
	vector<ServiceListener<Price<Bond> >* > listenerList;
public:
	// ctor
	BondPricingService();
	
	// override pure virtual functions in Service class
	// given id return bond price
	virtual Price<Bond>& GetData(string id) override;
	
	// add a bond price to priceMap, called by connector
	virtual void OnMessage(Price<Bond> &data) override;
	
	// add a listener, in this case, listener is BondAlgoStreamingServiceListener
	virtual void AddListener(ServiceListener<Price<Bond> > *listener) override;
	
	// get listeners, in this case, listener is BondAlgoStreamingServiceListener
	virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const override;
	
};

BondPricingService::BondPricingService(){
	priceMap=map<string, Price<Bond> >();
}

Price<Bond>& BondPricingService::GetData(string id){
	return priceMap.at(id);
}

void BondPricingService::OnMessage(Price<Bond>& data){
	auto id=data.GetProduct().GetProductId();
	
	if(priceMap.find(id)!=priceMap.end())
		priceMap.erase(id);
	priceMap.insert(pair<string,Price<Bond> >(id,data));
	
	// notify the listener this Service has added a data
	for(auto& listener:listenerList){
		listener->ProcessAdd(data);
	}

	return;
}

void BondPricingService::AddListener(ServiceListener<Price<Bond> > *listener){
	listenerList.push_back(listener);
	return;
}

const vector< ServiceListener<Price<Bond> >* >& BondPricingService::GetListeners() const{
	return listenerList;
}


void BondPricingServiceConnector::Subscribe() {
	ifstream input;
	input.open("prices.txt");

	string row;
	while (getline(input, row)) {
		stringstream line(row);
		string temp;
		getline(line, temp, ',');    
		auto bond = bondProductService->GetData(temp);
		getline(line, temp, ',');
		auto price = TransformStringToPrice(temp);
		getline(line, temp, ',');
		auto spread = TransformStringToPrice(temp);

		Price<Bond> bondPrice(bond, price, spread);

		bondPricingService -> OnMessage(bondPrice);
	}
	return;
}
#endif
