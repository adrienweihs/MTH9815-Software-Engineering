/**
 * BondProductService.hpp 
 * defines bond product service
 * 
 */
#pragma once

#ifndef BONDPRODUCTSERVICE_HPP
#define BONDPRODUCTSERVICE_HPP

#include <iostream>
#include <map>
#include "products.hpp"
#include "soa.hpp"

using namespace std;

/**
 * Bond Product Service to own reference data over a set of bond securities.
 * Key is the productId string, value is a Bond.
 */
class BondProductService : public Service<string,Bond> {

public:
	// BondProductService ctor
	BondProductService();

	// Return the bond data for a particular bond product identifier
	Bond& GetData(string productId);

	// Add a bond to the service (convenience method)
	void Add(Bond &bond);

	// Get all Bonds with the specified ticker
	vector<Bond> GetBonds(string& _ticker);

	// override other pure virtual functions 
	// no implementation
	virtual void OnMessage(Bond &data) override{}

	// no implementation
	virtual void AddListener(ServiceListener<Bond > *listener) override{}
	
	// no implementation
	virtual const vector< ServiceListener<Bond >* >& GetListeners() const override{}


private:
	map<string,Bond> bondMap; // cache of bond products

};

BondProductService::BondProductService() {
	bondMap = map<string,Bond>();
}

Bond& BondProductService::GetData(string productId) {
	return bondMap[productId];
}

void BondProductService::Add(Bond &bond) {
	bondMap.insert(pair<string,Bond>(bond.GetProductId(), bond));
}

vector<Bond> BondProductService::GetBonds(string& _ticker){
	vector<Bond> res;
	for(auto it=bondMap.begin();it!=bondMap.end();++it){
		if((it->second).GetTicker()==_ticker)
			res.push_back(it->second);
	}
	return res;
}

#endif